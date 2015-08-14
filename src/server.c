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
#include "server.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* 一个服务相关的信息 */
typedef struct {
    JObject parent;
    jchar *name;
    jushort port;
    pid_t pid;
} Server;

/* 创建服务器，失败返回NULL */
static inline Server *start_server(const jchar *name, JConfObject *obj, CLOption *option);
/* 关闭服务器 */
static void stop_server(Server *server);

static JList *servers=NULL;

void start_all(CLOption *option) {
    JConfObject *root=(JConfObject*)config_load(option->config);
    if(root==NULL) {
        j_printf("%s\n", config_message());
        exit(-1);
    }
    JList *keys=j_conf_object_lookup(root, "^server-[[:alpha:]][[:alnum:]]*", J_CONF_NODE_TYPE_OBJECT);
    if(keys==NULL) {
        j_printf("no server found in configuration!\n");
        exit(-1);
    }
    JList *ptr=keys;
    while(ptr) {
        const jchar *key=(const jchar*)j_list_data(ptr);
        Server *server=start_server(key+7, j_conf_object_get(root, key), option);
        if(server) {
            servers=j_list_append(servers, server);
        }
        ptr=j_list_next(ptr);
    }
    j_list_free(keys);

    atexit(stop_all);
}

static inline Server *start_server(const jchar *name, JConfObject *obj, CLOption *option) {
    jint64 port = j_conf_object_get_integer(obj, "port", 0);
    if(port<=0||port>65536) {
        j_fprintf(stderr, "invalid port in server %s\n", name);
        return NULL;
    }
    Server *server=(Server*)j_malloc(sizeof(Server));
    J_OBJECT_INIT(server, stop_server);
    server->name=j_strdup(name);
    server->port=port;
    server->pid=-1;
    return server;
}

static void stop_server(Server *server) {
    j_free(server->name);
    if(server->pid>0) {
        kill(server->pid, SIGINT);
    }
}

void stop_all(void) {
    JList *ptr=servers;
    while(ptr) {
        Server *server=(Server*)j_list_data(ptr);
        J_OBJECT_UNREF(server);
        ptr=j_list_next(ptr);
    }
    j_list_free(servers);
}
