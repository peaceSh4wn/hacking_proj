#include "module_register.h"
#include "cmd_exec.h"

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
	cmd_exec(Gsd);		
	return SUCCESS;
}
