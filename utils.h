#ifndef UTILS_H
#define UTILS_H

#define ARGS_LEN 3

enum boolean { FALSE = 0, TRUE = 1 };

boolean VFLG = FALSE, OFLG = FALSE;

const char *ARGS[] = { "-v", "-o", "-O3" };

void verbose(void){
	VFLG = TRUE;
}

void outputName(void){
    OFLG = TRUE;
}

void (*getFlag[])(void) = { verbose, outputName };

#endif 
