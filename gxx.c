#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

#define MAX_PATH_LENGTH 260

enum { 
	BOTH=-1,
	NOTFOUND=0,
    CLANG=1,
    CPP=2
};

int isClang(const char *file){
	char fileName[MAX_PATH_LENGTH];
	sprintf(fileName, "%s.c", file);
	FILE *f = fopen(fileName, "r");

	if(f == NULL) return 0;
	fclose(f);
    return 1;
}

int isCpp(const char *file){
    char fileName[MAX_PATH_LENGTH];
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
    char path[MAX_PATH_LENGTH], 
		filePath[MAX_PATH_LENGTH],
        buf[MAX_PATH_LENGTH];

	if(_getcwd(path, sizeof(path)) != NULL){
		if(argc >= 2){
			sprintf(filePath, "%s\\%s", path, argv[1]);
            compile(filePath);
		}
	}
	else{
        perror("getcwd() error");
        return 1;
	}
	return 0;
}
