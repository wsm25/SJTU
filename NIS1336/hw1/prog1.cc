#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "helps"
#include "utils.h"

template<typename T>
static std::fstream& operator<<(std::fstream& is, T& n){
    is.write((char*)&n, sizeof(T));
    return is;
}

int main(int argc, char* argv[]){
    if(parse_arg(argc, argv, help1)!=0){
        return 0;
    }
    if(argc!=3){
        std::cout<<"错误：非法参数个数\n"<<help1<<std::endl;
        return 0;
    }
    int n=atoi(argv[1]);
    if(n<=0){
        std::cout<<"错误：非法随机数个数\n"<<help1<<std::endl;
        return 0;
    }
    std::fstream f;
    f.open(argv[2], std::ios::binary | std::ios::out );
    if(!f.is_open()){
        std::cout<<"错误：文件无法打开"<<std::endl;
        return -1;
    }
    std::srand(std::time(0));
    f<<n;
    std::cout<<"生成随机数\t";
    for(int i=0; i<n; i++){
        int x = std::rand();
        std::cout<<x<<'\t';
        f<<x;
    }
    f.close();
    return 0;
}