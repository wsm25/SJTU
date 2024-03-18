#include <iostream>

enum Status {
    Pending,
    Queue,
    Stack,
    Error
};

// assume no error
int main(){
    int s,n;
    int op,x;
    int stack[2000], queue[2000];
    std::cin>>s;
    while(s--){ // main loop
        std::cin>>n;
        // variables
        Status status=Pending;
        int *st=stack, *qh=queue, *qt=queue;
        while(n--){
            std::cin>>op>>x;
            if (status==Error) continue; // bypass error status
            if(op==1){ // push
                *(st++)=*(qt++)=x;
            }else{ // pop
                if (*(--st)!=x) // not a stack
                    if (status==Stack) status=Error;
                    else status=Queue;
                if (status==Error) continue; // prevent error covered
                if (*(qh++)!=x) // not a queue
                    if (status==Queue) status=Error;
                    else status=Stack;
            }
        }
        switch (status){
        case Queue:   std::cout<<"Queue\n";break;
        case Stack:   std::cout<<"Stack\n";break;
        case Error:   std::cout<<"Error\n";break;
        case Pending: std::cout<<"Both\n"; break;
        }
    }
}
