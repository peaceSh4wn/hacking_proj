#ifndef _MASTER_H_
#define _MASTER_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define DATA_LEN 2048

// get local ip automatically in next version
#define LOCAL_IP "192.168.204.146"

typedef enum {
	FAILURE = -1,
	SUCCESS
} STAT;

typedef struct _sockTag {
	int sock_fd;
	struct sockaddr_in sk_addr;
}SockTag;

typdef struct _sockData {
	char readData[DATA_LEN];
	char sendData[DATA_LEN];
	Sock_Tag sock_t;
}SockData;

/* global socket desciptor */
SockTag *Gst = NULL;

/* global socket data */
SockData *Gsd = NULL;

/* initilize global socket and prepare 
 * tcp connection. we'll use multithreading
 * in future */
int init_server();

/* get data, process instruction then send data */
void loop();

/* close server */
int close_server();

#endif
