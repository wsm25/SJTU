#ifndef STACK_H
#define STACK_H
#include <vector>
using std::vector;
class MyStack{
    std::vector<float> arr;
public:
    void push(float n){
        arr.push_back(n);
    }

    bool pop(float &n){
        if (arr.empty()) return false;
        n=arr.back();
        arr.pop_back();
        return true;
    }

    size_t size(){
        return arr.size();
    }
};
#endif