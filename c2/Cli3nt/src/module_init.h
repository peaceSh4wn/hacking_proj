#ifndef _MODULE_INIT_H_
#define _MODULE_INIT_H_

#include "client.h"

#define MODULE_NAME_LEN 50
#define MODULE_PARAM_LEN 60

/* not in use now */
typedef struct global_module_ {
	char name[MODULE_NAME_LEN];
	union {
		char param[MODULE_PARAM_LEN];
		int param_int;
	};
	int type;
}Modules;

/* */
int socket_module_init(const char *ip, int port);

/* */
int module_init(const char *module_name, int *index, char **argv);


#endif
