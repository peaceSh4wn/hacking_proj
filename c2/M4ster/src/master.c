#include "master.h"
#include "usage.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (SUCCESS != init_server()) {
		printf("init server error\n");
		goto err;
	}
	
	if (SUCCESS != loop()) {
		printf("loop error\n");	
		goto err;
	}

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

	Gst->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == Gst->sock_fd) {
		// failed	
		goto err;
	}

	memset(&(Gst->sk_addr), 0, sizeof(sockaddr_in));
	Gst->sk_addr->sin_family = AF_IPV4;
	Gst->sk_addr->sin_

	
	return SUCCESS;
err:
	// XFREE();
	return FAILURE;
}

void loop()
{

}

int close_server()
{

}
