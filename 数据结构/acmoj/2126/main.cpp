#include <iostream>

int main(){
    int len, input, height=0, max=0;
    std::cin>>len;
    while(len-->0){
        std::cin>>input;
        height+=input;
        if (height>max) max=height;
    }
    std::cout<<max;
}