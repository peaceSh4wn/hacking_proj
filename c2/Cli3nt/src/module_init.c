#include "module_init.h"

int get_ip(const char *IpPort, char **dstIp)
{
	if (IpPort == NULL || *dstIp == NULL) {
		goto err;
	}
	
	char *tmp = strchr(IpPort, ':');
	if (tmp == NULL) {
		goto err;
	}

	int ip_len = tmp - IpPort;
	strncpy(*dstIp, IpPort, ip_len);
	
	return SUCCESS;
err:
	return FAILURE;
}

int get_port(const char *IpPort, int *dstPort)
{
	if (IpPort == NULL || dstPort == NULL) {
		goto err;
	}
	
	char *tmp = strchr(IpPort, ':');
	if (tmp == NULL) {
		goto err;
	}

	sscanf(tmp + 1, "%d", dstPort);

	return SUCCESS;
err:
	return FAILURE;
}

int socket_module_init(const char *ip, int port)
{
	extern int sock_fd;
	int len;
	extern int default_port;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr, "[!] Get socket file descriptor failed\n");
		exit(0);
	}

	extern struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);
	len = sizeof(server_addr);

	if (0 > connect(sock_fd, 
		(const struct sockaddr *)&server_addr, len)) {
		fprintf(stderr, "[!] Connect server failed\n");
		exit(0);
	}
	
	printf("[+] Connect successfully\n > ");
#if 0	
	char cmd[1024] = {0};
	printf(">Connect successfully\n>");
	while(1) {
		scanf("%s", cmd);
		if (strncmp(cmd, "quit", 4) == 0) break;
		write(sock_fd, (char *)cmd, strlen(cmd));
		read(sock_fd, (char *)cmd, 1024);
		printf("> %s\n>", cmd);
	}
	
	close(sock_fd);
#endif

	return SUCCESS;

}

int module_init(const char *module_name, int *index, char **argv)
{	
	if (SUCCESS == strcmp(module_name, "--addr")) {
		// ip:port
		const char *IpPort = argv[*index + 1];
		
		char *ip = (char *)malloc(sizeof(char) * 18);
		int port = -1;

		if (FAILURE == get_ip(IpPort, &ip)) {
			printf("[!] Get ip failed\n");
			free(ip);
			exit(0);
		}
		
		if (FAILURE == get_port(IpPort, &port)) {
			printf("[!] Get port failed\n");
			free(ip);
			exit(0);
		}
		
		socket_module_init(ip, port);
		// printf("[+] Ip port is %s\n", IpPort);
		free(ip);

	} else if (SUCCESS == strcmp(module_name, "--proxy")) {
		

	} else if (SUCCESS == strcmp(module_name, "--times")) {
		

	} else {
		

	}
	
	return SUCCESS;
}
