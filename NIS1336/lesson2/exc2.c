#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool atoi(const char* s, int* n){
    int x=0;
    while((*s)!=0){
        if(*s>='0' && *s<='9')
            x=x*10+*s-'0';
        else return false;
        s++;
    }
    *n=x;
    return true;
}

int main(int argc, char* argv[]){
    int input;
    bool invargc = argc!=2, help, invnum;
    if(invargc) {
        puts("Error: Invalid argument number!");
    } else {
        help = strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")==0;
        invnum = !atoi(argv[1], &input);
        if(invnum) puts("Error: Invalid input number!");
    }
    if(invargc || help || invnum) {
        printf(
            "Exercise2: gets an positive integer number `n` and prints sum of 1..n\n"
            "Usage: %s [number]\n", 
            argv[0]);
        return -1;
    }
    printf("%d", input*(input+1)/2);
    return 0;
}