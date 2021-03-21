#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define USAGE "\
Usage:\n\
\tclient ip port\n\n\
have fun!\n"

int sock_fd;
struct sockaddr_in src_adr;

int main(int argc, char *argv[])
{
	int errno = 0;
	if (argc != 3) {
		printf(USAGE);
		errno = -2;
		goto err;
	}

	if (0 == (sock_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		printf("[!] can't get a socket fd");
		errno = -1;
		goto err;
	}
	bzero((void *)&src_adr, sizeof(src_adr));

	/* 为了方便观看，这没有做容错处理 */
	src_adr.sin_family = AF_INET;
	src_adr.sin_port = htonl(atoi(argv[2]));
	src_adr.sin_addr.s_addr = inet_addr(argv[1]);

	int ret = connect(sock_fd, 
		(struct sockaddr *)&src_adr, sizeof(struct sockaddr));

	if (ret < 0) {
		perror("[!] error: socket error\n");
		errno = -3;
		goto err;
	}

	char data[20] = "hello shawn!\n";
	ssize_t send_num = write(sock_fd, (void *)data, strlen(data));
	printf("[+] Send data finished\n");

err:
	close(sock_fd);
	return errno;
}
