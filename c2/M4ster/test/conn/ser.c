#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define LISTEN_NUM 3

/* 套接字描述符 */
int sock_fd;

/* 全局网络地址结构体 */
struct sockaddr_in g_adr;

int main(int argc, char *argv[]) 
{
  int errno = 0;
  
	/* 获取套接字 */
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("[-] Get socket failed\n");
        errno = -1;
        goto err;
  }
	printf("[+] Get socket descriptor %d successfully\n", sock_fd); 
	bzero((void *)&g_adr, sizeof(g_adr));
	
	/* 填充网络地址结构体 */
	g_adr.sin_family = AF_INET; 
	g_adr.sin_port = htons(atoi(argv[1]));
	g_adr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock_fd, (struct sockaddr*)(&g_adr), 
		sizeof(g_adr)) == -1) {
		printf("[-] Bind failed\n");
		errno = -2;
		goto err;
	}
     
	printf("[+] Bind successfully\n");

	/* 开始监听，设置监听数量 */
	if (listen(sock_fd, LISTEN_NUM) < 0) {
		printf("[-] Listen failed\n");
		errno = -3;
		goto err;
	}

	printf("[+] Listen successfully\n");

	/* 在这个无限循环中， 我们会使用accept接受来自客户端的请求 */
	char buffer[1024];
	while (1) {
		memset(buffer, 0, sizeof(buffer));

		int req_fd;

		struct sockaddr_in req_adr;
		socklen_t len = sizeof(struct sockaddr_in);
		bzero(&req_adr, sizeof(struct sockaddr_in));
		
		/* 用req_fd作为本次连接的socket标识符，req_adr来获取请求网络地址端口等 */
		req_fd = accept(sock_fd, (struct sockaddr*)(&req_adr), &len);

		if (req_fd < 0) {
			printf("[-] Accept failed\n");
			errno = -4;
			goto err;
		}
		printf("[+] Accept successfully\n\n");
		printf("[+] Ip: %s\n[+] Port: %u\n\n", inet_ntoa(req_adr.sin_addr), ntohs(req_adr.sin_port));
		
		/* 接收数据 */
		recv(req_fd, buffer, sizeof(buffer), 0);
		printf("[!] DATA: %s\n", buffer);

		/* 发送数据 */
		send(req_fd, buffer, sizeof(buffer), 0);
		close(req_fd);
	}

err:
    close(sock_fd);
    return errno;
}
