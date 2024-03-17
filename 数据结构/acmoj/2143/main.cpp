#include <iostream>
#include <string>
int main(){
    std::string s;
    std::cin>>s;
    std::cin.get(); // flush \n
    // count
    int a=0, p=0; char ch;
    for(;;){
        std::cin.get(ch);
        if (std::cin.fail()) break;
        if (ch=='a') a++;
        else if (ch=='p') p++;
        else break;
    }
    for(char c : s){
        if (c=='a'){
            if (a>0) a--;
            else break;
        } else {
            if (p>0) p--;
            else break;
        }
    }
    std::cout<<a+p;
    return 0;
}