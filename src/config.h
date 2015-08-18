/*
 * Copyright (C) 2015 Wiky L
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.";
 */
#ifndef __JAC_CONFIG_H__
#define __JAC_CONFIG_H__

#include <jconf/jconf.h>


#ifndef LISTEN_PORT
#define LISTEN_PORT 1601
#endif

#define CONFIG_FILENAME CONFIG_DIR "/" PACKAGE ".conf"

JConfLoader *create_config_loader(void);


/* 命令行参数 */
typedef struct {
    jboolean help;      /* --help */
    jboolean test;      /* --test */
    jboolean verbose;   /* --verbose */
    jchar *config;      /* --config filename*/
} CLOption;



#endif
