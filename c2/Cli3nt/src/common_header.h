#ifndef  _COMMON_H_
#define  _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define INPUT_LEN		1024
#define GET_DATA_LEN	2048

typedef enum {
	FAILURE = -1,
	SUCCESS
}RetVal;

#define SendOverTag()       \
    do {                    \
        write(sock_fd,  	\
        "0v3r7",            \
        strlen("0v3r7"));   \
    } while(0)

struct list_head {
	struct list_head *prev;
	struct list_head *next;
};


#endif
