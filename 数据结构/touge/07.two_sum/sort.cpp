//! Sort and find  
//! Amortized time complexity is O(nlog(n))
#include <cstdint>
#include <vector>
#include <iostream>

// qsort
uint32_t seed=114514;
inline uint16_t qrand(){
    return ((seed = (214013*seed+2531011))>>16);
}
template<typename T>
void qsort(T* arr, size_t len){
    if(len<=1) return;
    size_t i=qrand()%len;
    T pivot=arr[i];
    arr[i]=arr[0];
    size_t left=0, right=len-1;
    while(left<right) {
        // now arr[left] is free
        while(left<right && arr[right]<=pivot) right--;
        arr[left]=arr[right];
        // now arr[right] is free
        while(left<right && pivot<=arr[left]) left++;
        arr[right]=arr[left];
    }
    arr[left]=pivot;
    qsort(arr+left+1, len-left-1);
    qsort(arr, left);
}

int main(){
    size_t len; std::cin>>len;
    std::vector<int> vec;
    vec.reserve(len);
    for(int i=0; i<len; i++){
        int tmp; std::cin>>tmp;
        vec.push_back(tmp);
    }
    qsort(vec.data(), len);
    int k; std::cin>>k;
    int left=0, right=len-1;
    while(left<right){
        while(left<right && vec[left]+vec[right]>k) left++;
        while(left<right && vec[left]+vec[right]<k) right--;
        if(left<right && vec[left]+vec[right]==k){
            std::cout<<vec[left]<<' '<<vec[right];
            return 0;
        }
    }
    std::cout<<"null";
}