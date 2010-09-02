/**
 * @file    configfile.h
 * @brief   handle configuration file
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
 
#ifndef GUMMI_CONFIGFILE
#define GUMMI_CONFIGFILE

#include <glib.h>

#define CONFIG_MAX 64
#define BUF_MAX BUFSIZ / 8

typedef struct _finfo {
    gchar** pbuf;
    int len;
} finfo;

/**
 * @brief initialize config file
 * @param filename filename of the configuration file
 */
void config_init(const gchar* filename);

/**
 * @brief reset settings to default
 */
void config_set_default(void);

/**
 * @brief get value of a setting
 * @param term the name of the setting
 * @return a pointer that points to the static gchar* of the setting value. If
 * the value type is boolean, config_get_value will return NULL for False
 * and non-NULL for True
 */
const gchar* config_get_value(const gchar* term);

/**
 * @brief set value of a setting
 * @param term the name of the setting
 * @param value the value of the setting
 */
void config_set_value(const gchar* term, const gchar* value);

/* [Internal] */
finfo config_load(void); 
void config_save(finfo fin);
int config_find_index_of(gchar** pbuf, const gchar* term);

#endif /* GUMMI_CONFIGFILE */
