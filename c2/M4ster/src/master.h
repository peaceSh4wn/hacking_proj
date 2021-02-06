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
#define LOCAL_PORT 6666

typedef enum {
	FAILURE = -1,
	SUCCESS
} STAT;

typedef struct _sockTag {
	int sock_fd;
	struct sockaddr_in sk_addr;
}SockTag;

typedef struct _sockData {
	char readData[DATA_LEN];
	char sendData[DATA_LEN];
	SockTag sock_t;
}SockData;

/* global socket desciptor */
SockTag *Gst = NULL;

/* global socket data */
SockData *Gsd = NULL;

/* global data file pointer */
FILE *g_dfp = NULL;

/* global task counter */
int g_tcnt = 0;

#define GetSDfd(sd)\
	sd->sock_t.sock_fd

#define GetSDaddr(sd)\
	sd->sock_t.sk_addr

#define GetSDrdata(sd)\
	sd->readData

#define GetSDsdata(sd)\
	sd->sendData

#define XFREE(fp)			\
	do {					\
		if (fp != NULL)	{	\
			free(fp);		\
			fp = NULL;		\
		}					\
	} while(0)

/* initilize global socket and prepare 
 * tcp connection. we'll use multithreading
 * in future */
int init_server();

/* get data, process instruction then send data */
void loop();

/* close server */
int close_server();

#endif
