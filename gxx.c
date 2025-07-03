#include <stdio.h>
#include "auxl.h"
#include "utils.h"

int main(int argc, char *argv[]){
	char path[PATH_MAX], filePath[PATH_MAX], buf[PATH_MAX];
	currDir(path);

	if(argc >= 2){
		sprintf(filePath, "%s/%s", path, argv[1]);
		compile(filePath);
	}
	else{
        help();
	}
	return 0;
}
