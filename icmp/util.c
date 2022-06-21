#include "config.h"

struct hostent* GetHostByName(char *host) {
	
	struct hostent *temp;

	temp = Malloc(sizeof(struct hostent));
	temp = gethostbyname(host);

	if (!temp) {
		perror("hostname");
		exit(0);
	}

	return temp;
}

int GetRawSock(void) {
	int sock, null = 0;
	if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		perror("socket");
		exit(-1);
	}	

	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &null, sizeof(null)) < 0) {
		perror("SetSockOpt");
		exit(-1);
	}

	return sock;
}

int Select(int max, fd_set *fds) {
	int afds = select(max, fds, NULL, NULL, NULL);
	if (afds < 0) {
		perror("select");
		exit(0);
	}

	return afds;
}

void *Malloc(int size) {
	void *buff;
	buff = malloc(size);

	if (!buff) {
		perror("malloc");
		exit(0);
	}
	
	return buff;
}
