#include "module_register.h"
#include "cmd_exec.h"
#include <unistd.h>
#include <stdlib.h>

STAT module_ini()
{
	// may be a for loop
	printf("this is module ini\n");

	return SUCCESS;
}

/* reservation */
STAT module_reg()
{	
	printf("this is module reg\n");

	return SUCCESS;
}

STAT module_close()
{
	// may be a for loop
	printf("this is module close\n");	

	return SUCCESS;
}

/* Active Mode C->S */
SockTag* GetFileATag() {
	SockTag *st = NULL;
	st = (SockTag *)malloc(sizeof(SockTag));

	if (st == NULL)
		goto err;

	if ((st->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		goto err;
	}

	bzero((void *)&(st->sk_addr), sizeof(struct sockaddr_in));
	st->sk_addr.sin_family = AF_INET;
	st->sk_addr.sin_port = htons(4779);
	st->sk_addr.sin_addr.s_addr = INADDR_ANY;

	return st;
err:
	if (st) {
		free(st);
		st = NULL;
	}
	return NULL;
}

/* Passive Mode S->C */
SockTag* GetFilePTag(const char *ip, const short port) {
	SockTag *st = NULL;
	st = (SockTag *)malloc(sizeof(SockTag));

	if (st == NULL)
		goto err;
	
	if ((st->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		goto err;
	}
	
	bzero((void *)&(st->sk_addr), sizeof(struct sockaddr_in));
	st->sk_addr.sin_family = AF_INET;
	st->sk_addr.sin_port = htons(port);
	st->sk_addr.sin_addr.s_addr = inet_addr(ip);

	return st;
err:
	if (st) {
		free(st);
		st = NULL;
	}
	return NULL;
}

STAT DelFileTag(SockTag *st) {
	if (st == NULL)
		goto err;
	free(st);
	st = NULL;
	return SUCCESS;
err:
	return FAILURE;
}

STAT opt_parse(SockData *Gsd)
{
	if (0 == strncmp(GetSDrdata(Gsd), "get", 3)) {
		/* get file */
		FILE *fp = NULL;
		send(GetSDfd(Gsd), "revGet", 20, 0);
		recv(GetSDfd(Gsd), (void *)&(GetSDrdata(Gsd)), DATA_LEN, 0);
		if (0 == strlen(GetSDrdata(Gsd))) {
			send(GetSDfd(Gsd), "err", 20, 0);
			goto err;
		}	
		if (0 != access(GetSDrdata(Gsd), F_OK)) {
			send(GetSDfd(Gsd), "no such file", 20, 0);
			goto err;
		}
		
		// file name
		fp = fopen(GetSDrdata(Gsd), "rb");
		if (NULL == fp) {
			goto err;
		}
		send(GetSDfd(Gsd), "okk", 30, 0);

		recv(GetSDfd(Gsd), (void *)&(GetSDrdata(Gsd)), DATA_LEN, 0);
		
		if (0 == strncmp(GetSDrdata(Gsd), "fine", 4)) {
			/* start transfering file */
			int rf_sz = 0;
			while(0 < (rf_sz = fread(GetSDsdata(Gsd), sizeof(char), DATA_LEN, fp))) {
				if (0 > send(GetSDfd(Gsd), GetSDsdata(Gsd), rf_sz, 0)) {
					printf("[!] err: failed to send file\n");
					exit(0);
				}
				bzero(GetSDsdata(Gsd), DATA_LEN);
			}
			sleep(1);
			SendOverTag();
			fclose(fp);
		} else {
			fclose(fp);
		}

	} else if (0 == strncmp(GetSDrdata(Gsd), "put", 3)) {
		/* put file */
		FILE *fp = NULL;
		send(GetSDfd(Gsd), "revPut", 30, 0); 
		recv(GetSDfd(Gsd), (void *)&(GetSDrdata(Gsd)), DATA_LEN, 0);
		
		if (0 == strncmp(GetSDrdata(Gsd), "err", 3)) {
#if 1
			printf("err occured\n");
#endif
			goto err;	
		}
		
		fp = fopen(GetSDrdata(Gsd), "wb+");
		if (NULL == fp) {
			send(GetSDfd(Gsd), "err", 30, 0);
			goto err;
		}
		
		send(GetSDfd(Gsd), "okk", 30, 0);
		recv(GetSDfd(Gsd), (void *)&(GetSDrdata(Gsd)), DATA_LEN, 0);

		if (0 == strncmp(GetSDrdata(Gsd), "err", 3)) {
#if 1
			printf("err occured\n");
#endif
			goto err;
		}
		
		if (0 != strncmp(GetSDrdata(Gsd), "action", 6)) {
			goto err;
		}
		send(GetSDfd(Gsd), "okk", 30, 0);

		// printf("%s %d\n", OVER_TAG, strlen(OVER_TAG));
		int fp_block_sz = 0;
		while (fp_block_sz = recv(GetSDfd(Gsd), (void *)&(GetSDrdata(Gsd)), DATA_LEN, 0)) {
			// printf("%s\n", GetSDrdata(Gsd));
			if (0 > fp_block_sz) {
				printf("[!] Error receiving file from client to server\n");
			}
			if (0 == strncmp(GetSDrdata(Gsd), OVER_TAG, 5)) {
				break;
			}
			fputs(GetSDrdata(Gsd), fp);
			int write_sz = fwrite(GetSDrdata(Gsd), sizeof(unsigned char), fp_block_sz, fp);
			if (write_sz < fp_block_sz) {
				printf("[!] error File write failed on server\n");
			} else if (-1 == fp_block_sz) {
				break;
			}
			bzero(GetSDrdata(Gsd), DATA_LEN);
		}
		fclose(fp);
		fp = NULL;
	} else if (0 == strncmp(GetSDrdata(Gsd), "sock", 4)) {
		char ip[20] = "192.168.204.1";
		SockTag *st = GetFilePTag(ip, 4558);
		if (NULL == st) {
			send(GetSDfd(Gsd), "[-] get socket data File tag failed\n", 50, 0);
			goto err;
		}

		if (0 > connect(Getfd(st), (struct sockaddr *)&(Getadr(st)), sizeof(struct sockaddr))) {
			send(GetSDfd(Gsd), "[-] connect failed\n", 30, 0);
			goto err;
		}
		char buffer[100] = "hello shawn! This is a msg for you\n";
		write(Getfd(st), buffer, strlen(buffer));
		memset(buffer, 0, sizeof(buffer));
		close(Getfd(st));
		free(st);
		send(GetSDfd(Gsd), "Send msg successfully\n", 40, 0);
		sleep(1);
		SendOverTag();
	} else {
		/* command execute */
		cmd_exec(Gsd);	
	}

	return SUCCESS;
err:
	return FAILURE;
}
