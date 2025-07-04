#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define ARGS_LEN 3
#define MAX_PATH 4096
#define BOTH -1
#define NOTFOUND 0
#define CLANG 1
#define CPP 2

#ifdef _WIN32
	#include <direct.h>
    char* currDir(char *buf){
        if(_getcwd(buf, MAX_PATH) == NULL) return NULL;
        return buf;
	}
#elif __linux__
    #include <unistd.h>	
    char* currDir(char *buf){
        if(getcwd(buf, MAX_PATH) == NULL) return NULL;
        return buf;
	}
#endif

typedef enum boolean { 
	FALSE = 0, 
	TRUE = 1 
} boolean;

boolean 
	VFLG = FALSE, 
	OFLG = FALSE,
	OSFLG = FALSE;

const char *ARGS[] = { "-v", "-o", "-O3" };

int isClang(const char *file){
	char fileName[MAX_PATH];
	sprintf(fileName, "%s.c", file);
	FILE *f = fopen(fileName, "r");

	if(f == NULL) return 0;
	fclose(f);
	return 1;
}

int isCpp(const char *file){
	char fileName[MAX_PATH];
	sprintf(fileName, "%s.cpp", file);
	FILE *f = fopen(fileName, "r");

	if(f == NULL) return 0;
	fclose(f);
	return 1;
}

int doesFileExist(const char *file){
	int c = isClang(file), cpp = isCpp(file);

	if(c && cpp) return BOTH;
	if(c && !cpp) return CLANG;
	if(!c && cpp) return CPP;
	return NOTFOUND;
}

void compile(const char *file){
	int type = doesFileExist(file);
	char cmd[128];

	printf("Compiling...\n");
	if(type == CLANG){
		printf("C-Lang File Detected!\n");
		sprintf(cmd, "gcc -o %s %s.c", file, file);
		system(cmd);
	}
	else if(type == CPP){
		printf("C++ File Detected!\n");
		sprintf(cmd, "g++ -o %s %s.cpp", file, file);
		system(cmd);
	}
	else{
		printf("File %s does not exist\n", file);
	}
	printf("Done!\n");
}

#endif 
