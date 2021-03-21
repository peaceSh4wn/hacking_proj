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
		//printf("[-] %s\n", argv[i]);
		
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

		if (0 == strncmp(cmd, "get", 3)) {
			write(sock_fd, (char *)cmd, strlen(cmd));
			read(sock_fd, (char *)res, GET_DATA_LEN);
			
			// resGet
			// printf("%s\n", res);

			FILE *lfp = NULL;
			unsigned char rfile[INPUT_LEN] = {0};
			unsigned char lfile[INPUT_LEN] = {0};
			printf("(file) ");
			scanf("%[^\n]%*c", rfile);
			printf("(local) ");
			scanf("%[^\n]%*c", lfile);
			
			/* Send file name and get result, if result is fail, 
			 * then print err info. If result is success, then we 
			 * will start trasfer file.*/
			
			write(sock_fd, (char *)rfile, strlen(rfile));
			read(sock_fd, (char *)res, GET_DATA_LEN);
			
			// okk
			// printf("res is %s\n", res);

			if (0 != strncmp(res, "okk", 3)) {
				printf("err occured\n");
				goto next;
			}
			
			write(sock_fd, "fine", strlen("fine"));
			lfp = fopen(lfile, "wb+");
		
			int rf_sz = 0;	
			/* get file */
			while (0 < (rf_sz = read(sock_fd, (char *)res, GET_DATA_LEN))) {
				if (0 == strncmp(res, "0v3r7", 5)) break;
				fputs(res, lfp);
				int write_sz = fwrite(res, sizeof(char), rf_sz, lfp);
				if (write_sz < rf_sz) {
					printf("File write failed\n");
					break;
				} else if (rf_sz == -1) {
					printf("Finished\n");
					break;
				}
			}

			fclose(lfp);
			lfp = NULL;
			PRINT_FONT_GRE
			printf("[+] file trans done\n");
			PRINT_CLEAR
next:
			PRINT_FONT_PUR
			printf("Cli3nt> ");
			continue;
		}

		if (0 == strncmp(cmd, "put", 3)) {
			write(sock_fd, cmd, strlen(cmd));
			read(sock_fd, res, GET_DATA_LEN);
#if 0 
			printf("%s\n", res);
#endif
			FILE *lfp = NULL;
			unsigned char rfile[INPUT_LEN] = {0};
			unsigned char lfile[INPUT_LEN] = {0};
			unsigned char sendBuf[GET_DATA_LEN] = {0};

			printf("(file) ");
			scanf("%[^\n]%*c", lfile);
			printf("(remote) ");
			scanf("%[^\n]%*c", rfile);
			
			if (0 != access(lfile, F_OK)) {
				printf("no such file or lack of priviledge\n");
				write(sock_fd, "err", strlen("err"));
				goto next1;
			}
				
			write(sock_fd, rfile, strlen(rfile));
			read(sock_fd, (char *)res, GET_DATA_LEN);

			lfp = fopen(lfile, "rb");
			
			if (0 != strncmp(res, "okk", 3)) {
				// printf("%s\n", res);
				write(sock_fd, "err", strlen("err"));
				goto next1;
			}
			
			if (NULL == lfp) {
				printf("can't open local file\n");
				write(sock_fd, "err", strlen("err"));
				goto next1;
			}

			write(sock_fd, "action", 6);
			read(sock_fd, (char *)res, GET_DATA_LEN);

			if (0 == strncmp(res, "okk", 3)) {
				int fp_block_sz = 0;
				while(0 < (fp_block_sz = fread(sendBuf, sizeof(char), GET_DATA_LEN, lfp))) {
					//printf("send %d\n", strlen(sendBuf));
					write(sock_fd, sendBuf, fp_block_sz);
					bzero(sendBuf, GET_DATA_LEN);
				}
				//printf("send tag\n");
				sleep(1);
				SendOverTag();
				//printf("send tag over\n");
			} else {
				printf("some err occured\n");
				SendOverTag();
			}
next1:	
			if (NULL != lfp) {
				fclose(lfp);
				lfp = NULL;
			}
			PRINT_FONT_PUR
			printf("Cli3nt> ");
			continue;
		}

		if (0 == strncmp(cmd, "quit", 4)) {
			write(sock_fd, (char *)cmd, strlen(cmd));
			break;
		}

		// send commands
		write(sock_fd, (char *)cmd, strlen(cmd));
		
		// read responses
		PRINT_FONT_YEL
		while (read(sock_fd, (char *)res, GET_DATA_LEN)) {
			if (0 == strncmp(res, "0v3r7", 5)) break;
			printf("%s", res); 
		}
		PRINT_CLEAR
		PRINT_FONT_PUR
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
