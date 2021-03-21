#include <stdlib.h>
#include "master.h"
#include "utils/usage.h"
#include "modules/module_register.h"

// STAT opt_parse();

SockTag *Gst = NULL;
SockData *Gsd = NULL;
FILE *g_dfp = NULL;
int g_tcnt;

int main(int argc, char **argv)
{
	if (SUCCESS != init_server()) {
		printf("[-] init server error\n");
		goto err;
	}
	
	loop();

	if (SUCCESS != close_server()) {
		printf("[-] close server error\n");
		goto err;
	}
	
	return 0;
err:
	printf("[*] fatal error, quitting...\n");
	return -1;
}

int init_server()
{
	printf(usage);
	Gst = (SockTag *)calloc(1, sizeof(SockTag));			
	if (NULL == Gst) {
		printf("[-] malloc to Gst failed\n");
		goto err;
	}

	// get Socket file descriptor
	Gst->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (FAILURE == Gst->sock_fd) {
		printf("[-] get base socket fd failed\n");
		goto err;
	}
	
	// set socket addr
	memset(&(Gst->sk_addr), 0, sizeof(struct sockaddr_in));
	Gst->sk_addr.sin_family = AF_INET;
	Gst->sk_addr.sin_port = htons(LOCAL_PORT);
	Gst->sk_addr.sin_addr.s_addr = INADDR_ANY;
	//inet_addr(LOCAL_IP);

	// bind with ip port
	if (FAILURE == bind(Gst->sock_fd, 
		(struct sockaddr *)&(Gst->sk_addr), sizeof(struct sockaddr_in))) {
		printf("[-] bind with err\n");
		goto err;
	}

	// listen max = 10
	if (FAILURE == listen(Gst->sock_fd, 10)) {
		printf("[-] listen with err\n");
		goto err;
	}

	Gsd = (SockData *)calloc(1, sizeof(SockData));
	if (NULL == Gsd) {
		printf("[-] malloc to Gsd failed \n");
		goto err;
	}

	socklen_t len = sizeof(struct sockaddr_in);
	// accept
	GetSDfd(Gsd) = accept(Gst->sock_fd, 
		(struct sockaddr *)&(GetSDaddr(Gsd)), &len);
	
	return SUCCESS;
err:
	XFREE(Gst);
	return FAILURE;
}

void loop()
{
	while (FAILURE != recv(GetSDfd(Gsd), 
		(void *)&(GetSDrdata(Gsd)), DATA_LEN, 0)) {
		
		printf("[>] \"%s\"\n", GetSDrdata(Gsd));

		if (0 == strncmp(GetSDrdata(Gsd), "quit", 4)) {
			break;
		}

		printf("[+] Task [%d] started\n", ++g_tcnt);
		
		/* operation parse */
		opt_parse(Gsd);

		printf("[+] Task [%d] finished\n\n", g_tcnt);
		memset(GetSDrdata(Gsd), 0, DATA_LEN); 
	}
}

int close_server()
{
	close(Gst->sock_fd);
	close(GetSDfd(Gsd));
	
	// XFREE	
	XFREE(Gst);
	XFREE(Gsd);
	g_dfp = NULL;

	printf("[-] closed M4ster successfully\n");

	return SUCCESS;
}
