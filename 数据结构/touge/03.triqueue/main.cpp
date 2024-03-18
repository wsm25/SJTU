#include <iostream>
#include <string>
#include "queue.h"
using std::cin;
using std::cout;
using std::string;

int main(){
    string op; int x;
    NewQueue q;
    for(;;){
        cin>>op>>x;
        if (cin.fail()) break;
        if (op=="EnFront"){
            q.EnFront(x);
        } else if (op=="EnMiddle"){
            q.EnMiddle(x);
        } else if (op=="EnRear"){
            q.EnRear(x);
        } else if (op=="DeFront"){
            q.DeFront();
        } else if (op=="DeMiddle"){
            q.DeMiddle();
        } else if (op=="DeRear"){
            q.DeRear();
        } else {
            break;
        }
        cout<<q<<'\n';
    }
    cout<<q;
    return 0;
}