#include "module_register.h"
#include "cmd_exec.h"
#include <unistd.h>

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
			while(NULL != fgets(GetSDsdata(Gsd), DATA_LEN, fp)) {
				send(GetSDfd(Gsd), GetSDsdata(Gsd), DATA_LEN, 0);
			}
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
	} else {
		/* command execute */
		cmd_exec(Gsd);	
	}

	return SUCCESS;
err:
	return FAILURE;
}
