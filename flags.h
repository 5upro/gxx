#ifndef GXX_FLAGS_H
#define GXX_FLAGS_H

#include <stdlib.h>

#define ARGS_LEN 3
#define MAX_PATH 4096
#define BOTH -1
#define NOTFOUND 0
#define CLANG 1
#define CPP 2

typedef enum boolean { 
	FALSE = 0, 
	TRUE = 1 
} boolean;

boolean 
	VFLG = FALSE, 
	OFLG = FALSE,
	OSFLG = FALSE;

const char *ARGS[] = { "-v", "-o", "-O3" };

typedef struct funcNode{
	struct funcNode *next;
	char flag[8];
	void (*flagFunc) (const char *);
}funcNode;

funcNode funcMap[10] = {
    { //funcMap[0]
		NULL, 
		"-V", 
		NULL
	}, 
    { //funcMap[1]
		NULL, 
		"--", 
		NULL
	}, 
    { //funcMap[2]
		NULL, 
		"-v", 
		NULL
	}, 
    { //funcMap[3]
		NULL, 
		"-O", 
		NULL
	}, 
    { //funcMap[4]
		NULL, 
		"--", 
		NULL
	}, 
    { //funcMap[5]
		NULL, 
		"-o", 
		NULL
	}, 
    { //funcMap[6]
		NULL, 
		"--", 
		NULL
	}, 
    { //funcMap[7]
		NULL, 
		"--", 
		NULL
	}, 
    { //funcMap[8]
		NULL, 
		"-h", 
		NULL
	}, 
    { //funcMap[9]
		NULL, 
		"-O2", 
		NULL
	}, 
};

#endif
