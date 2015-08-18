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
#ifndef __JAC_UTILS_H__
#define __JAC_UTILS_H__

#include <jlib/jtypes.h>


/*
 * path是一个文件路径，该函数创建该文件所需要的目录
 * 路径存在或者创建成功，返回TRUE，否则返回FALSE
 */
jboolean make_dir(const jchar *path);


/* 以O_APPPEND打开文件 */
jint append_file(const jchar *path);


#endif