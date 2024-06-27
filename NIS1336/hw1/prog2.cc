#include <iostream>
#include <fstream>
#include "helps"
#include "utils.h"

template<typename T>
static std::fstream& operator>>(std::fstream& is, T& n){
    is.read((char*)&n, sizeof(T));
    return is;
}

int main(int argc, char* argv[]){
    if(parse_arg(argc, argv, help1)!=0){
        return 0;
    }
    if(argc!=2){
        std::cout<<"错误：非法参数个数\n"<<help1<<std::endl;
        return 0;
    }
    std::fstream f;
    f.open(argv[1], std::ios::binary | std::ios::in );
    if(!f.is_open()){
        std::cout<<"错误：文件无法打开\n"<<std::endl;
        return -1;
    }
    int n;
    f>>n;
    int x;
    long long sum=0;
    for(int i=0; i<n; i++){
        f>>x;
        sum+=x;
    }
    f.close();
    std::cout<<"和："<<sum;
    return 0;
}