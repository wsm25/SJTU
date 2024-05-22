#ifndef QSORT_HPP
#define QSORT_HPP

#include <cstdint>

template<typename T>
void swap(T& x, T& y){
    T t=x; x=y; y=t;
}

template<typename T>
void qsort(T* arr, T* end){
    if(end-arr<=16) { // insertion sort
        for(T* cur=arr+1; cur<end; cur++){
            T key=*cur, *p=cur-1;
            for(; p>=arr && *p>key; p--)
                *(p+1)=*p;
            *(p+1)=key;
        }
        return;
    }
    // find mid of 0, len-1 and len/2

    T *left=arr, *right=end-1;
    T* mid=(arr+(end-arr)/2);
    if(*left>*right) swap(*arr, *right);
    if(*mid>*right) swap(*mid, *right);
    if(*left<*mid) swap(*left, *mid);
    T pivot=*left;
    while(left<right) {
        // now arr[left] is free
        while(left<right && *right>=pivot) right--;
        *left=*right;
        // now arr[right] is free
        while(left<right && pivot>=*left) left++;
        *right=*left;
    }
    *left=pivot;
    qsort(arr, left);
    qsort(left+1, end);
}

#endif // QSORT_HPP