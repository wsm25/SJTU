#include <iostream>

int main(){
    int len;
    std::cin>>len;
    std::cin.get(); // flush \n
    char *s=new char[len+1];
    char *st=new char[len], *p=st; // inline stack
    std::cin.getline(s,len+1);
    for(;*s!=0;s++){
        if (p>st && *s==*(p-1)) p--; // pop
        else *(p++)=*s; // push *s
    }
    *p=0; // \0
    std::cout<<st;
    return 0;
}
