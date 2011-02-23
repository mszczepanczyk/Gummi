/**
 * @file    utils.c
 * @brief   
 *
 * Copyright (C) 2010 Gummi-Dev Team <alexvandermey@gmail.com>
 * All Rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>

#ifdef HAVE_SYS_WAIT_H
# include <sys/wait.h>
#endif
#ifndef WEXITSTATUS
# define WEXITSTATUS(stat_val) ((unsigned int) (stat_val) >> 8)
#endif

#include <glib.h>
#include <gtk/gtk.h>

#include "environment.h"
#include "utils.h"

static gint slog_debug = 0;
static GtkWindow* parent = 0;

void slog_init(gint debug) {
    slog_debug = debug;
}

void slog_set_gui_parent(GtkWidget* p) {
    parent = GTK_WINDOW(p);
}

void slog(gint level, const gchar *fmt, ...) {
    gchar message[BUFSIZ];
    gchar* out;
    va_list vap;

    if (L_IS_TYPE(level, L_DEBUG) && !slog_debug) return;

    if (L_IS_TYPE(level, L_DEBUG))
        fprintf(stderr, "\e[1;32m[Debug]\e[0m ");
    else if (L_IS_TYPE(level, L_FATAL) || L_IS_TYPE(level, L_G_FATAL))
        fprintf(stderr, "\e[1;37;41m[Fatal]\e[0m ");
    else if (L_IS_TYPE(level, L_ERROR) || L_IS_TYPE(level, L_G_ERROR))
        fprintf(stderr, "\e[1;31m[Error]\e[0m ");
    else if (L_IS_TYPE(level, L_WARNING))
        fprintf(stderr, "\e[1;33m[Warning]\e[0m ");
    else
        fprintf(stderr, "\e[1;34m[Info]\e[0m ");
    
    va_start(vap, fmt);
    vsnprintf(message, BUFSIZ, fmt, vap);
    va_end(vap);
    fprintf(stderr, "%s", message);

    if (L_IS_GUI(level)) {
        GtkWidget* dialog;

        if (L_IS_TYPE(level, L_G_FATAL))
            out = g_strdup_printf(_("%s has encountered a serious error and "
                        "will require a restart. Your working data will be "
                        "restored when you reload your document. Please "
                        "report bugs at: http://dev.midnightcoding.org"),
                        PACKAGE_NAME);
        else
            out = g_strdup(message);

        dialog = gtk_message_dialog_new (parent, 
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                L_IS_TYPE(level,L_G_INFO)? GTK_MESSAGE_INFO: GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "%s", message);
        g_free(out);

        if (L_IS_TYPE(level, L_G_ERROR))
            gtk_window_set_title(GTK_WINDOW(dialog), "Error!");
        else if (L_IS_TYPE(level, L_G_FATAL))
            gtk_window_set_title(GTK_WINDOW(dialog), "Fatal Error!");
        else if (L_IS_TYPE(level, L_G_INFO))
            gtk_window_set_title(GTK_WINDOW(dialog), "Info");

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    if (!L_IS_TYPE(level, L_INFO) &&
        !L_IS_TYPE(level, L_DEBUG) && 
        !L_IS_TYPE(level, L_ERROR) && 
        !L_IS_TYPE(level, L_G_INFO) &&
        !L_IS_TYPE(level, L_G_ERROR))
        exit(1);
}

gint utils_yes_no_dialog(const gchar* message) {
    GtkWidget* dialog;
    gint ret = 0;

    g_return_val_if_fail(message != NULL, 0);

    dialog = gtk_message_dialog_new (parent, 
                 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                 GTK_MESSAGE_QUESTION,
                 GTK_BUTTONS_YES_NO,
                 "%s", message);

    gtk_window_set_title(GTK_WINDOW(dialog), _("Confirmation"));
    ret = gtk_dialog_run(GTK_DIALOG(dialog));      
    gtk_widget_destroy(dialog);

    return ret;
}

gboolean utils_path_exists(const gchar* path) {
    if (NULL == path) return FALSE;
    gboolean result = FALSE;
    GFile* file = g_file_new_for_path(path);
    result = g_file_query_exists(file, NULL);
    g_object_unref(file);
    return result;
}

/*
 * Platform independent file copy operation
 */
gboolean utils_copy_file(const gchar* source, const gchar* dest, GError** err) {
    gchar* contents;
    gsize length;

    g_return_val_if_fail(source != NULL, FALSE);
    g_return_val_if_fail(dest != NULL, FALSE);
    g_return_val_if_fail(err == NULL || *err == NULL, FALSE);

    if (!g_file_get_contents(source, &contents, &length, err))
        return FALSE;

    if (!g_file_set_contents(dest, contents, length, err))
        return FALSE;

    g_free(contents);

    return TRUE;
}

/**
 * @brief  Platform independent interface for calling popen() and returns a
 * newly allocated pointer
 * @return Tuple2
 */
Tuple2 utils_popen_r(const gchar* cmd) {
    FILE* fp = popen(cmd, "r");
    gchar buf[BUFSIZ];
    gchar* ret = NULL;
    gchar* rot = NULL;
    gint status = 0, len = 0;

    g_assert(cmd != NULL);

    if (!fp) slog(L_FATAL, "popen() error\n");

    while ((len = fread(buf, 1, BUFSIZ, fp))) {
        buf[len - (len == BUFSIZ)] = 0;
        rot = g_strdup(ret);
        g_free(ret);
        if (ret)
            ret = g_strconcat(rot, buf, NULL);
        else
            ret = g_strdup(buf);
        g_free(rot);
    }
    status = WEXITSTATUS(pclose(fp));
    return (Tuple2){NULL, (gpointer)status, (gpointer)ret};
}

/**
 * @brief Transforms target to path relative to root.
 * @return a newly allocated pointer to gchar* to the relative path, if target
 * isn't relative to root, target is simply duplicated and returned.
 */
gchar* utils_path_to_relative(const gchar* root, const gchar* target) {
    gchar* tstr = NULL;
    if ((root != NULL) && (0 == strncmp(target, root, strlen(root))))
        tstr = g_strdup(target + strlen(root) + 1);
    else
        tstr = g_strdup(target);
    return tstr;
}

slist* slist_find_index_of(slist* head, const gchar* term,
        gboolean create_if_not_exists) {
    slist* current = head;
    slist* prev = 0;

    while (current) {
        if (0 == strcmp(current->first, term))
            return current;
        prev = current;
        current = current->next;
    }
    if (create_if_not_exists) {
        slog(L_WARNING, "can't find `%s', creating new field for it...\n",
                term);
        prev->next = g_new0(slist, 1);
        current = prev->next;
        current->first = g_strdup(term);
        current->second = g_strdup("");
    } else
        current = NULL;
    return current;
}
