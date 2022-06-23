#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SID "icmp_sid"
#define SRVSEQ 9
#define CLISEQ 14

#define VERSION "1"
#define CHAR 256
#define PING "ping"
#define PONG "pong"

struct sockaddr_in saddr;
struct ip *ip;
struct icmp *icmp;
int rawsock, icmpcode;
struct hostent *temp;

void *Malloc(int);
struct hostent *GetHostByName(char *host);
int GetRawSock(void);
int Select(int max, fd_set *fds);
