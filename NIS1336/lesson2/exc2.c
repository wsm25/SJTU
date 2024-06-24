#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef long long unsigned input_t;

bool atoi(const char* s, input_t* n) {
    input_t x=0;
    while((*s)!=0){
        if(x>0xffffffff/10) return false; // too long
        if(*s>='0' && *s<='9')
            x=x*10+*s-'0';
        else return false;
        s++;
    }
    *n=x;
    return true;
}

int main(int argc, char* argv[]) {
    input_t input;
    bool help=false, invnum=false;
    if(argc==2){
        help = strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")==0;
        invnum = !atoi(argv[1], &input) || input>0xffffffff;
        if(help) puts("Gets an positive integer number `n` and prints sum of 1..n");
        else if(invnum) printf("Error: Invalid input number `%s`!\n", argv[1]);
    }
    if(argc!=2 || help || invnum) {
        if(argc>2) printf("Error: Require 1 argument, got %d\n", argc-1);
        printf("Usage: %s [number]\n", argv[0]);
        if(help) return 0;
        else return -1;
    }
    printf("%llu\n", input*(input+1)/2);
    return 0;
}