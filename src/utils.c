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
#include "utils.h"
#include <jlib/jlib.h>
#include <jio/jio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


jboolean make_dir(const jchar *path) {
    jchar *dir=j_path_dirname(path);
    jint ret=j_mkdir_with_parents(dir, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
    j_free(dir);
    return ret==0;
}


jint append_file(const jchar *path) {
    jint fd=open(path, O_WRONLY|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP);
    return fd;
}

void log_internal(const jchar *domain,const jchar *message, jint level, jint fd, jint errfd) {
    jchar buf[4096];
    time_t t=time(NULL);
    ctime_r(&t, buf);
    jint len=strlen(buf)-1;
    if(level&J_LOG_LEVEL_ERROR) {
        if(errfd<0) {
            return;
        }
        j_snprintf(buf+len, sizeof(buf)-len, " [%s]: %s\n", domain, message);
        j_write(errfd, buf, strlen(buf));
        return;
    } else if(fd<0) {
        return;
    }

    const jchar *flag="";
    if(level & J_LOG_LEVEL_DEBUG) {
        flag="DEBUG";
    } else if(level & J_LOG_LEVEL_INFO) {
        flag="INFO";
    } else if(level & J_LOG_LEVEL_WARNING) {
        flag="WARNING";
    }
    j_snprintf(buf+len, sizeof(buf)-len, " [%s] [%s]: %s\n", domain,flag, message);
    j_write(fd, buf, strlen(buf));
}
