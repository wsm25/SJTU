#include <iostream>

int main(){
    int len, used=0, input;
    std::cin>>len;
    while(len-->0){
        std::cin>>input;
        if(input>13) {
            std::cout<<"you died";
            return 0;
        }
        int today=used%20;
        if (today+input>13) used=used-today+20+input;
        else used+=input;
    }
    std::cout<<used;
}