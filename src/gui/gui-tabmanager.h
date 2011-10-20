/**
 * @file   gui-tabmanager.h
 * @brief
 *
 * Copyright (C) 2010-2011 Gummi-Dev Team <alexvandermey@gmail.com>
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

#ifndef __GUMMI_GUI_TABMANAGER_H__
#define __GUMMI_GUI_TABMANAGER_H__

#include <glib.h>
#include <gtk/gtk.h>

#include "editor.h"

#define g_tabnotebook gui->tabmanagergui->notebook
#define g_unsavednr gui->tabmanagergui->unsavednr


#define GU_TAB_PAGE(x) ((GuTabPage*)x)
typedef struct _GuTabPage GuTabPage;

struct _GuTabPage {
    GtkWidget* scroll;
    GtkWidget* labelbox;
    GtkLabel* label;
    gint position;
    GtkButton* button;
    
    gboolean bold;
};


#define GU_TAB_CONTEXT(x) ((GuTabContext*)x)
typedef struct _GuTabContext GuTabContext;

struct _GuTabContext {
    GuEditor* editor;
    GuTabPage* page;
};

#define GU_TABMANAGER_GUI(x) ((GuTabmanagerGui*)x)
typedef struct _GuTabmanagerGui GuTabmanagerGui;

struct _GuTabmanagerGui {
    GtkNotebook* notebook;
    int unsavednr;

};

GuTabmanagerGui* tabmanagergui_init (GtkBuilder* builder);
int tabmanagergui_create_page (GuTabContext* tc, GuEditor* editor);
void tabmanagergui_create_label (GuTabPage* tp, gchar* labeltext);

gchar* tabmanagergui_get_labeltext (GuTabPage* tp);
gint tabmanagergui_replace_page (GuTabContext* tc, GuEditor* newec);
void tabmanagergui_set_current_page (gint position);
gint tabmanagergui_get_current_page (void);
void tabmanagergui_update_label (GuTabPage* tp, const gchar* text);
void tablabel_set_bold_text (GuTabPage* tp);


#endif /* __GUMMI_GUI_TABMANAGER_H__ */
