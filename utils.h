/**
 * @file    utils.h
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


#ifndef GUMMI_UTILS
#define GUMMI_UTILS

#include <glib.h>

#define L_IS_TYPE(level, type) ((level & type) == type)
#define L_IS_GUI(level) (level & 0xf0)
#define L_INFO     0x01    /* for informative messages */
#define L_DEBUG    0x02    /* debug messages, only print if -d flags is used */
#define L_ERROR    0x04    /* reconverable error */
#define L_FATAL    0x08    /* inrecoverable error */
#define L_G_INFO   0x10    /* GUI info */
#define L_G_ERROR  0x20    /* recoverable error */
#define L_G_FATAL  0x40    /* inrecoverable error */

typedef struct _pdata {
    gint ret;
    gchar* data;
} pdata;

/**
 * @brief slog initlization
 * @param debug boolean value for whether output debug message or not
 */
void slog_init(gint debug);

/**
 * @brief debug interface for gummi
 * @param level levels or listed above
 * @param fmt just like the printf function
 * @param ... parameters for fmt
 */
void slog(gint level, const gchar *fmt, ...);

gboolean utils_yes_no_dialog(const gchar* message);
gboolean utils_validate_path(const gchar* path);
pdata utils_popen(gchar* const argv[]);

#endif /* GUMMI_UTILS */
