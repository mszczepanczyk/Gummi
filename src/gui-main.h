/**
 * @file    gui-main.h
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


#ifndef GUMMI_GUI_MAIN_H
#define GUMMI_GUI_MAIN_H

#include <glib.h>
#include <gtk/gtk.h>

#include "gui-import.h"
#include "gui-prefs.h"
#include "gui-search.h"

#define RECENT_FILES_NUM 5
#define TEXCOUNT_OUTPUT_LINES 7
#define g_e_buffer GTK_TEXT_BUFFER(gummi->editor->sourcebuffer)
#define g_e_view GTK_TEXT_VIEW(gummi->editor->sourceview)

typedef struct _GummiGui {
    GuPrefsGui* prefsgui;
    GuSearchGui* searchgui;
    GuImportGui* importgui;

    GtkWidget *mainwindow;
    GtkTextBuffer *errorbuff;
    GtkVBox* rightpane;
    GtkHBox* toolbar;
    GtkStatusbar *statusbar;
    GtkToggleToolButton* previewoff;
    GtkCheckMenuItem* menu_spelling;
    GtkCheckMenuItem* menu_toolbar;
    GtkCheckMenuItem* menu_statusbar;
    GtkCheckMenuItem* menu_rightpane;
    GtkMenuItem* recent[5];
    
    guint statusid;
    gchar* recent_list[5];
} GummiGui;

typedef enum _GuFilterType {
    TYPE_LATEX = 0,
    TYPE_LATEX_SAVEAS,
    TYPE_PDF,
    TYPE_IMAGE,
    TYPE_BIBLIO
} GuFilterType;

/* Main GUI */
GummiGui* gui_init(GtkBuilder* builder);
void gui_main(GtkBuilder* builder);
gboolean gui_quit(void);
void gui_update_title(void);
void on_menu_new_activate(GtkWidget* widget, void* user);
void on_menu_open_activate(GtkWidget* widget, void* user);
void on_menu_save_activate(GtkWidget* widget, void* user);
void on_menu_saveas_activate(GtkWidget* widget, void* user);
void on_menu_find_activate(GtkWidget* widget, void* user);
void on_menu_cut_activate(GtkWidget* widget, void* user);
void on_menu_copy_activate(GtkWidget* widget, void* user);
void on_menu_paste_activate(GtkWidget* widget, void* user);
void on_menu_undo_activate(GtkWidget* widget, void* user);
void on_menu_redo_activate(GtkWidget* widget, void* user);
void on_menu_delete_activate(GtkWidget *widget, void * user);
void on_menu_selectall_activate(GtkWidget *widget, void * user);
void on_menu_preferences_activate(GtkWidget *widget, void * user);
void on_menu_statusbar_toggled(GtkWidget *widget, void * user);
void on_menu_toolbar_toggled(GtkWidget *widget, void * user);
void on_menu_rightpane_toggled(GtkWidget *widget, void * user);
void on_menu_fullscreen_toggled(GtkWidget *widget, void * user);
void on_menu_find_activate(GtkWidget *widget, void* user);
void on_menu_findnext_activate(GtkWidget *widget, void * user);
void on_menu_findprev_activate(GtkWidget *widget, void * user);
void on_menu_bibload_activate(GtkWidget *widget, void * user);
void on_menu_bibupdate_activate(GtkWidget *widget, void * user);
void on_menu_docstat_activate(GtkWidget *widget, void * user);
void on_menu_spelling_toggled(GtkWidget *widget, void * user);
void on_menu_update_activate(GtkWidget *widget, void * user);
void on_menu_about_activate(GtkWidget *widget, void * user);
void on_tool_previewoff_toggled(GtkWidget *widget, void * user);
void on_tool_textstyle_bold_activate(GtkWidget* widget, void* user);
void on_tool_textstyle_italic_activate(GtkWidget* widget, void* user);
void on_tool_textstyle_underline_activate(GtkWidget* widget, void* user);
void on_tool_textstyle_left_activate(GtkWidget* widget, void* user);
void on_tool_textstyle_center_activate(GtkWidget* widget, void* user);
void on_tool_textstyle_right_activate(GtkWidget* widget, void* user);
void on_button_template_add_clicked(GtkWidget* widget, void* user);
void on_button_template_remove_clicked(GtkWidget* widget, void* user);
void on_button_template_open_clicked(GtkWidget* widget, void* user);
void on_button_template_close_clicked(GtkWidget* widget, void* user);
void on_template_rowitem_editted(GtkWidget* widget, gchar *path, gchar* filenm,
        void* user);
gboolean on_button_searchwindow_close_clicked(GtkWidget* widget, void* user);
void on_button_searchwindow_find_clicked(GtkWidget* widget, void* user);
void on_button_searchwindow_replace_next_clicked(GtkWidget* widget, void* user);
void on_button_searchwindow_replace_all_clicked(GtkWidget* widget, void* user);

void on_button_biblio_compile_clicked(GtkWidget* widget, void* user);
void on_button_biblio_refresh_clicked(GtkWidget* widget, void* user);
void on_bibreference_clicked(GtkTreeView* view, GtkTreePath* Path,
        GtkTreeViewColumn* column, void* user);
gboolean on_bibprogressbar_update(void* user);

void preview_page_input_changed(GtkEntry* entry, void* user);
void preview_next_page(GtkWidget* widget, void* user);
void preview_prev_page(GtkWidget* widget, void* user);
void preview_zoom_change(GtkWidget* widget, void* user);

/* misc functions */
gchar* get_open_filename(GuFilterType type);
gchar* get_save_filename(GuFilterType type);
void file_dialog_set_filter(GtkFileChooser* dialog, GuFilterType type);
gint check_for_save(void);

void add_to_recent_list(gchar* filename);
void display_recent_files(GummiGui* gui);

void errorbuffer_set_text(gchar *message);
void statusbar_set_message(gchar* message);
gboolean statusbar_del_message(void* user);

void check_motion_timer(void);

#endif /* GUMMI_GUI_MAIN_H */
