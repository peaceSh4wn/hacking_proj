#include "file_trans.h"

/* show file info */
STAT finfo(const char *pfile)
{
	// cmd : finfo path/filename	
	if (access(pfile, F_OK)) {
								
	}
	
	return SUCCESS;

err:
	return FAILURE;
}

/* get file from remote M4ster */
STAT getFile()
{
	// cmd : get
	// (file) filename
	// (local) save-filename
	
	printf("(file) ");
	scanf("%s", );
	if (FAILURE == finfo()) {
		
	}
	
	return SUCCESS;
}

/* put file to remote M4ster */
STAT sendFile()
{
	// cmd : put
	// (file) filename
	// (remote) save-filename
	
	
	return SUCCESS;
}

