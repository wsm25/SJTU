//! Of course we can O(nlog(n)) sort and O(n) search on ordered list.
//! However, a better solution is to use hashset, which provides amortized 
//! O(1) read and write. We can search k-arr[i] in hashset. 
//! Amortized time complexity is O(n)
#include <unordered_set>
#include <vector>
#include <iostream>

int main(){
    size_t len; std::cin>>len;
    std::unordered_set<int> map;
    map.reserve(len);
    std::vector<int> vec;
    vec.reserve(len);
    for(int i=0; i<len; i++){
        int tmp; std::cin>>tmp;
        vec.push_back(tmp);
    }
    int k; std::cin>>k;
    for(int i=0; i<len; i++){
        int a=vec[i], b=k-a;
        if(map.find(b)!=map.end()){ // found
            if(a<b){int tmp=a; a=b; b=tmp;}
            std::cout<<a<<' '<<b;
            return 0;
        }
        map.insert(a);
    }
    std::cout<<"null";
}