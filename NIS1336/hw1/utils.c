#include <stdio.h>
#include <string.h>
#include "name" // hidden

int parse_arg(const int argc, const char* argv[], const char* help){
    if(argc==1) {
        puts(help);
        return -1;
    } 
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            puts(help);
            return -1;
        }
        if(strcmp(argv[i], "-u") == 0){
            puts(NAME);
            return -1;
        }
    }
    return 0;
}

int atoi(const char* s){
    int x=0;
    while((*s)>='0' && (*s)<='9'){
        x=x*10+(*s++)-'0';
        if(x>16777216) return -1;
    }
    if(*s!=0) return -1;
    return x;
}