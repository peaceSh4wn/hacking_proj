#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define SID "icmp_sid"
#define SRVSEQ 9
#define CLISEQ 14

#define VERSION "1"
#define CHARS 256
#define PING
#define PONG 

struct sockaddr_in saddr;
struct ip *ip
struct icmp *icmp;
int rawsock, icmpcode;

void *Malloc(int);
struct hostent *GetHostByName(char *host);
int get_raw_sock(void);
int Select(int max, fd_set *fds);
struct hostent *temp;