#include <iostream>
#include <iomanip>
#include "stack.h"

int main(){
    MyStack st;
    float n=0;
    char ch;
    std::cin.get(ch);
    for(;;){
        std::cout<<"get char "<<(ch)<<'\n';
        if(std::cin.fail()) { // end
            if(st.size()<1) {
                std::cout<<"Error";
                return -1;
            }
            st.pop(n);
            std::cout<<std::fixed<<std::setprecision(1)<<n;
            break;
        } else if (ch=='+' || ch=='-' || ch=='*' || ch=='/'){
            if(st.size()<2){
                std::cout<<"Error";
                return -1;
            }
            float a,b;
            st.pop(b); st.pop(a);
            switch (ch) {
            case '+': a+=b; break;
            case '-': a-=b; break;
            case '*': a*=b; break;
            case '/': a/=b; break;
            }
            st.push(a);
            std::cin.get(ch);
        } else if (ch>='0' || ch<='9' ){ // numbers
            do{
                n=n*10+ch-'0';
                std::cin.get(ch);
            } while(ch>='0' && ch<='9');
            std::cout<<"get number"<<n<<'\n';
            st.push(n);
            n=0;
        } else {
            std::cin.get(ch);
        }
    }
}
 