#ifndef GXX_AUXILIARY_
#define GXX_AUXILIARY_

#include <stdio.h>

#define endl "\n"

int selfcmp(const char *a, const char *b){
    int i=0;
    while(a[i]!='\0'&& b[i]!='\0'){
        if((a[i]!=b[i])) return 0;
        i++;
    }
    return 1;
}

void error(const char *message){
    printf("Error: %s" endl, message);
}

void help(){
    printf(
        "Usage: gxx <flags> <filename>" endl
        "-v : Verbose output" endl
        "-o \"filename\" : Output file name" endl
        "-h : Help" endl
    );
}

#endif
