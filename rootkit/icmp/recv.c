#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 256
#define SID "icmp_sid"

int in_cksum (u_short *addr, int len) {
	register int nleft = len;
	register u_short *w = addr;
	register int sum = 0;
	u_short answer = 0;
	while (nleft > 1) 
		sum += *w++, nleft -= 2;

	if (nleft == 1)
		*(u_char *)(&answer) = *(u_char *)w; sum += answer;
		
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}

int main(int argc, char **argv) {
	int sk;
	int pktsize;
	struct sockaddr_in sa;
	unsigned char *packet = NULL;
	struct ip *ip;
	struct icmp *icmp;
	char text[SIZE + strlen(SID)], *data;

	if (argc < 2) {
		printf("usage: si ip\n");
		return 0;
	}

	if (0> (sk = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP))) {
		perror("socket");
		return -1;
	}

	int null = 0;
	if (0 > setsockopt(sk, IPPROTO_IP, IP_HDRINCL, &null, sizeof(null))) {
			perror("setsockopt");
			return -1;
	}

	pktsize = sizeof(struct icmp) + sizeof(text);
	packet = malloc(pktsize);

	icmp = (struct icmp *)packet;
	data = packet + sizeof(struct icmp);
	memset(packet, 0, sizeof(pktsize));

	bzero((void *)&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(argv[1]);
	icmp->icmp_type = 666;
	icmp->icmp_seq = 10;
	icmp->icmp_cksum = 0;
	strncat(data, text, sizeof(text));

	icmp->icmp_cksum = in_cksum((u_short *)icmp, pktsize);

	if (0 > sendto(sk, packet, pktsize, 0, (struct sockaddr*)&sa, sizeof(sa))) {
		perror("sendto");
		return -1;
	}

	close(sk);

	return 0;
}