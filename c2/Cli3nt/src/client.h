#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "common_header.h"
#include "usage.h"

typedef struct _file {

}file;


/* global socket file descriptor */
int sock_fd;

/* global socket addr */
struct sockaddr_in server_addr;

/* Initiliza modules including socket, command, proxy, 
 * shellcode, encrypt and etc. due to argv */
int init_client();

/* command and control */
int do_it();

/* release modules and free memory */
int close_client();

#endif
