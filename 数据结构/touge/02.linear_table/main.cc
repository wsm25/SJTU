#include <iostream>
#include "table.h"

using std::cin;
using std::cout;

int main(){
    NodeList l;
    cin>>l;
    int arg1, arg2;
    // insert
    cin>>arg1>>arg2;
    l.insert(arg1, arg2);
    // erase
    cin>>arg1>>arg2;
    l.erase(arg1, arg2);
    cout<<l.len()<<'\n';
    cout<<l;
}
