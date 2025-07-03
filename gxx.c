#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "auxl.h"

#define PATH_MAX 4096
#define BOTH -1
#define NOTFOUND 0
#define CLANG 1
#define CPP 2
const char *ARGS[] = {"-v", "-o"};
int VFLG = 0;
int OFLG = 0;
int OSFLG = 0;

#ifdef _WIN32
	#include <direct.h>
    char *currDir(char *buf){
        if(_getcwd(buf, sizeof(buf)) == NULL) return NULL;
        return buf;
	}
#elif __linux__
    #include <unistd.h>	
    char *currDir(char *buf){
        if(getcwd(buf, sizeof(buf)) == NULL) return NULL;
        return buf;
	}
#endif

void filter(char *str[], int len){
	for(int i = 1; i < len; i++){
		if(str[i][0] == '-') continue;
    	selfcmp(str[i], ARGS[i]);
	}
}

int isClang(const char *file){
	char fileName[PATH_MAX];
	sprintf(fileName, "%s.c", file);
	FILE *f = fopen(fileName, "r");

	if(f == NULL) return 0;
	fclose(f);
	return 1;
}

int isCpp(const char *file){
	char fileName[PATH_MAX];
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

int main(int argc, char *argv[]){
	char path[PATH_MAX], filePath[PATH_MAX], buf[PATH_MAX];
	currDir(path);

	if(argc >= 2){
		sprintf(filePath, "%s\\%s", path, argv[1]);
		compile(filePath);
	}
	else{
        help();
	}
	return 0;
}
