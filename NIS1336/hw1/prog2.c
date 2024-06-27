#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "helps"
#include "utils.h"

int main(int argc, char* argv[]){
    if(parse_arg(argc, argv, help2)!=0){
        return 0;
    }
    if(argc!=2){
        puts("错误：非法参数个数");
        puts(help2);
        return 0;
    }
    FILE* f = fopen(argv[1], "rb");
    if(f==0){
        puts("错误：文件打开失败");
        puts(strerror(errno));
        return -1;
    }
    int n;
    fread(&n, sizeof(int), 1, f);
    int x;
    long long sum=0;
    for(int i=0; i<n; i++){
        fread(&x, sizeof(int), 1, f);
        sum+=x;
    }
    printf("和: %lld\n", sum);
    fclose(f);
    return 0;
}