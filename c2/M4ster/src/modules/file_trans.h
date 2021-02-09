#ifndef _FILE_TRANS_H_
#define _FILE_TRANS_H_

#include "../master.h"

#define FILE_OPT_LEN 20

typedef struct _FileOpt {
	char opt[FILE_OPT_LEN];

}FileOpt;

typedef struct _FileInfo {
	
}FileInfo;

typedef struct _File{
	
}File;

File *global_file;

// file info
STAT finfo();

// get file
STAT getFile();

// send file
STAT sendFile();

#endif
