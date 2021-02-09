#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include "usage.h"


#define INPUT_LEN		1024
#define GET_DATA_LEN	2048

typedef enum {
	FAILURE = -1,
	SUCCESS
}RetVal;

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
