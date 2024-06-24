#include <algorithm>
#include <vector>
#include <iostream>

int main(){
    std::vector<int> x{3,2,3};
    auto end=std::unique(x.begin(), x.end());
    for(auto p=x.begin(); p<end; p++)
        std::cout<<*p<<' ';
}