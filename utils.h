#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "flags.h"
#include "auxl.h"

#ifdef _WIN32
#include <direct.h>

#define SEP "\\"

char* currDir(char *buf){
	if(_getcwd(buf, MAX_PATH) == NULL) return NULL;
	return buf;
}
#elif __linux__
#include <unistd.h>

#define SEP "/"

char* currDir(char *buf){
	if(getcwd(buf, MAX_PATH) == NULL) return NULL;
	return buf;
}
#endif


unsigned long hash(const char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) hash = ((hash << 5) + hash) + c; // hash * 33 + c
	
    return hash;
}

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

	if(type == CLANG){
		compileMsg(type);
		sprintf(cmd, "gcc -o %s %s.c", file, file);
		compileStatus(system(cmd));
	}
	else if(type == CPP){
		compileMsg(type);
		sprintf(cmd, "g++ -o %s %s.cpp", file, file);
		compileStatus(system(cmd));
	}
	else{
		printf("File %s does not exist\n", file);
	}
}

#endif 
