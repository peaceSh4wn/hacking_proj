#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
//#include <sys/types.h>
int sock_fd;


int main(int argc, char *argv[])
{
	in_addr_t x = inet_addr("172.18.60.151");
	struct in_addr test;
	test.s_addr = x;

	/* get network address in host byte order */
	in_addr_t net = inet_netof(test);
	printf("%u\n", net);
	struct in_addr test1;
	test1.s_addr = htonl(net);
	printf("network addr: %s\n", inet_ntoa(test1));
	
	/* get host address in host byte order */
	in_addr_t host = inet_lnaof(test);
	struct in_addr test2;
	test2.s_addr = htonl(host);
	printf("host addr: %s\n", inet_ntoa(test2));

	/* connect host and network address */
	struct in_addr test3 = inet_makeaddr(net, host);
	printf("whole addr: %s\n", inet_ntoa(test3));

	return 0;
}
