#include <iostream>
#define swap(x,y) do{auto t=x; x=y; y=t;}while(0)
int main(){
    int a,b,c;
    std::cin>>a>>b>>c;
    // expanded pop sorting
    if(a>b) swap(a,b);
    if(b>c) swap(b,c);
    if(a>b) swap(a,b);
    std::cout<<(c>a+b ? a+b : c+(a+b-c)/2)*10;
    return 0;
}