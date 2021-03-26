/**
 *	This header file is regarded as a common header
 *	which will be included by other files in module
 *	directory. In this file, some global variables
 *	will be decleared, and some macro func will be 
 *	set.
 */

#ifndef _MASTER_H_
#define _MASTER_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* lengths */
#define DATA_LEN 2048

// get local ip automatically in next version
#define LOCAL_IP "192.168.204.150"
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
	unsigned char readData[DATA_LEN];
	unsigned char sendData[DATA_LEN];
	SockTag sock_t;
}SockData;

/* global socket desciptor */
SockTag *Gst;

/* global socket data */
SockData *Gsd;

/* global data file pointer */
FILE *g_dfp;

/* global task counter */
int g_tcnt;

/* Compile Opetimize */
#define likely(expr) __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)

/* Data Getter in SockTag*/
#define Getfd(st)\
	st->sock_fd\

#define Getadr(st)\
	st->sk_addr

/* Data Getter in SockData*/
#define GetSDfd(sd)\
	sd->sock_t.sock_fd

#define GetSDaddr(sd)\
	sd->sock_t.sk_addr

#define GetSDrdata(sd)\
	sd->readData

#define GetSDsdata(sd)\
	sd->sendData

#define OVER_TAG "0v3r7"

/* macro func */
#define SendOverTag()		\
	do {					\
		send(GetSDfd(Gsd),	\
		"0v3r7",			\
		strlen("0v3r7"),	\
		0);					\
	} while(0)

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
