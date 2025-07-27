#include <stdio.h>
#include "auxl.h"
#include "utils.h"

int main(int argc, char *argv[]){
	char path[MAX_PATH], filePath[MAX_PATH];
	currDir(path);

	if(argc >= 2){
		sprintf(filePath, "%s" SEP "%s", path, argv[argc-1]);
		compile(filePath);
	}
	else help();
	return 0;
}
