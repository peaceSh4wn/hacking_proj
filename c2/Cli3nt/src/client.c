#include "client.h"
#include "module_init.h"
#include "cmd_color.h"

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
		printf("[-] %s\n", argv[i]);
		
		/* initilize modules with opts */
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
		
		if (0 == strlen(cmd)) {
			printf("Cli3nt> ");
			setbuf(stdin, NULL);
			continue;
		}

		if (0 == strncmp(cmd, "quit", 4)) {
			write(sock_fd, (char *)cmd, strlen(cmd));
			break;
		}

		// send commands
		write(sock_fd, (char *)cmd, strlen(cmd));
		
		// read responses
		PRINT_FONT_GRE
		while (read(sock_fd, (char *)res, GET_DATA_LEN)) {
			if (0 == strncmp(res, "0v3r7", 5)) break;
			printf("%s", res); 
		}
		PRINT_CLEAR
		PRINT_FONT_BLU
		printf("\nCli3nt> ");
		memset(cmd, 0, sizeof(cmd));
	}
	PRINT_CLEAR
	
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
