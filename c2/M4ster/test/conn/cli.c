#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>


#define USAGE "\
Usage:\n\
\tclient ip port isBlock\n\n\
have fun!\n"

int sock_fd;
struct sockaddr_in src_adr;
int flags;

int setBlock(int isblock) 
{
	flags = fcntl(sock_fd, F_GETFL, 0);
	if (0 > flags) {
		printf("[!] set fcntl failed\n");
		return -1;
	}
	if (isblock) {
		flags = flags & ~O_NONBLOCK;
	} else {
		flags = flags | O_NONBLOCK;
	}
	if (fcntl(sock_fd, F_SETFL, flags) != 0) {
		printf("[!] set fcntl failed\n");
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int errno = 0;
   	/* 参数数量检查 */
	if (argc != 4) {
		printf(USAGE);
		errno = -1;
		goto err;
	}

	int isblock;
	printf("%d", isblock= atoi(argv[3]));
	
    /* 获取socket标识符 */
	if (0 == (sock_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		printf("[!] can't get a socket fd");
		errno = -2;
		goto err;
	}
	bzero((void *)&src_adr, sizeof(src_adr));

	/* 为了方便观看，这没有做容错处理 */
  /* 填充sockaddr_in结构体，即：设置协议、ip、端口 */
	src_adr.sin_family = AF_INET;
	src_adr.sin_port = htons(atoi(argv[2])); // 这里注意端口是short int，如果误用htonl，则可能被转换为网络序时连不上
	src_adr.sin_addr.s_addr = inet_addr(argv[1]);

	if (setBlock(isblock) != 0) {
		printf("set block failed\n");
		errno = -7;
		goto err;
	}

	fd_set set;
    /* 发送请求，尝试建立连接*/
	int ret = connect(sock_fd, 
		(struct sockaddr *)&src_adr, sizeof(struct sockaddr));

	int time = 100;
	if (ret != 0) {
		struct timeval tm;
		tm.tv_sec = 0;
		tm.tv_usec = time * 1000;

		FD_ZERO(&set);
		FD_SET(sock_fd, &set);

		// 0 为超时, -1创建失败
		if (select(sock_fd + 1, 0, &set, 0, &tm) <= 0) {
			printf("connect failed\n");
			errno = -6;
			goto err;
		}
#if 0
		perror("[!] error: socket error\n");
		errno = -3;
		goto err;
#endif
	}

    setBlock(1);
	/* 发送数据 */
	char data[20] = "hello shawn!\n";
	ssize_t write_num = write(sock_fd, (void *)data, strlen(data));
	printf("[+] Send data finished\n");
    
err:
	close(sock_fd);
	return errno;
}
