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
	/* file transfer */
	if (0 == strncmp(GetSDrdata(Gsd), "get", 3)) {
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
		
		fp = fopen(GetSDrdata(Gsd), "w+");
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

	} else {
		cmd_exec(Gsd);	
	}
	return SUCCESS;
err:
	return FAILURE;
}
