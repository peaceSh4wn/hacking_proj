#include "config.h"

extern void sendpacket(char *, char *, int);

int main(int argc, char **argv) {

	int afds, shell, maxFd, null = 0, auth = 0, cliseq = CLISEQ, srvseq = SRVSEQ;
	char host[256], *payload, pbuf[CHAR], sbuf[CHAR];
	pid_t pid;
	u_char buf[1024];
	fd_set rset;



	return 0;
}
