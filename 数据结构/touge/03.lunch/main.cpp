#include <iostream>
#include <string>
#define QUEUE_LEN 65536
int main(){
    std::string s;
    // count
    std::getline(std::cin, s);
    int student[10]; char ch;
    for(int i=0; i<10; i++) student[i]=0;
    for(char ch : s){
        if (ch>='0' && ch<='9') 
            student[ch-'0']++;
    }
    // queue
    std::getline(std::cin, s);
    for(char ch : s){
        if (ch>='0' && ch<='9'){
            if (student[ch-'0']>0) 
                student[ch-'0']--;
            else break;
        }
    }
    for(int i=1; i<10; i++) student[0]+=student[i];
    std::cout<<student[0];
    return 0;
}