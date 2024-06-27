#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "helps"
#include "utils.h"

int main(int argc, char* argv[]){
    if(parse_arg(argc, argv, help1)!=0){
        return 0;
    }
    if(argc!=3){
        puts("错误：非法参数个数");
        puts(help1);
        return 0;
    }
    int n=atoi(argv[1]);
    if(n<=0){
        puts("错误：非法随机数个数");
        puts(help1);
        return 0;
    }
    FILE* f = fopen(argv[2], "wb");
    if(f==0){
        puts("错误：文件打开失败");
        puts(strerror(errno));
        return -1;
    }
    srand(time(0));
    fwrite(&n, sizeof(int), 1, f);
    int x;
    printf("生成随机数\t");
    for(int i=0; i<n; i++){
        x=rand();
        fwrite(&x, sizeof(int), 1, f);
    }
    fclose(f);
    puts("生成成功！");
    return 0;
}