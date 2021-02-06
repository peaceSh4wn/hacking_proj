#include "client.h"
#include "module_init.h"

void usage() {
	printf(USAGE_STR);	
}

static inline int input_gardian(int argc, char **argv)
{
	if (argc != 3) {
		usage();
		exit(0);
	}	
}

int init_client(int argc, char **argv)
{
	int i;
	for(i = 1; i < argc; i++) {
		// printf("[-] %s\n", argv[i]);
		
		/* module initilize in */
		module_init(argv[i], &i, argv);
	}
}

int do_it()
{
	
	char cmd[INPUT_LEN] = {0};
	char res[GET_DATA_LEN] = {0};

	while(1) {
		scanf("%[^\n]%*c", cmd);
		if (strlen(cmd) > INPUT_LEN) {
			printf("[!] Your input is to long,\
			please input data less than %d\n", INPUT_LEN);
			cmd[INPUT_LEN - 1] = '\0';
		}
		if (strncmp(cmd, "quit", 4) == 0) break;
		
		// send commands
		write(sock_fd, (char *)cmd, strlen(cmd));
		
		// read responses
		while (read(sock_fd, (char *)res, GET_DATA_LEN)) {
			printf("%s", res); 
		}
		printf("\n> ");
	}
	
}

int close_client()
{
	close(sock_fd);	
	printf("[-] close client successfully\n");
}

int main(int argc, char **argv)
{
	int sock_fd, sock_len;
	
	input_gardian(argc, argv);
	
	// init client
	init_client(argc, argv);

	// send commands and print responses
	do_it();

	// close client
	close_client();

	return 0;
}
