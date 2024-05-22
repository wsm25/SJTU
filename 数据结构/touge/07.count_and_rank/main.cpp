//! We just count for each value (backended with hashmap),
//! and sort them by count, and find rank.
//! 
//! Time complexity: O(n)+O(nlog(n))+O(n)=O(nlog(n))
#include <unordered_map>
#include <vector>
#include <cstdio>
#include <cstdint>
typedef unsigned len_t;

inline int readint() {
    int x=0, sign=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return sign*x;
}
// qsort
uint32_t seed=114514;
inline uint16_t qrand(){
    return ((seed = (214013*seed+2531011))>>16);
}
template<typename T>
void qsort(T* arr, len_t len){
    if(len<=1) return;
    len_t i=qrand()%len;
    T pivot=arr[i];
    arr[i]=arr[0];
    len_t left=0, right=len-1;
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

struct GirlsBandCry{
    int val, count;
    GirlsBandCry(int x):val(x){}
    bool operator<=(GirlsBandCry& rhs){
        return count<=rhs.count;
    }
};

int main(){
    size_t len=readint();
    std::unordered_map<int, int> map;
    std::vector<GirlsBandCry> vec;
    for(int i=0; i<len; i++){
        int tmp=readint();
        if(map.find(tmp)!=map.end()) map[tmp]++;
        else { // newbie
            vec.push_back(GirlsBandCry(tmp));
            map[tmp]=1;
        }
    }
    // flush
    for(auto x=vec.begin(); x!=vec.end(); x++){
        x->count=map[x->val];
    }
    len=vec.size();
    qsort(vec.data(), vec.size());
    int k=readint();
    int minele, i=0;
    for(int j=0; j<len && i<k; i++){
        int cnt=vec[j].count;
        minele=vec[j].val;
        while((++j)<len && vec[j].count==cnt)
            if(vec[j].val<minele) minele=vec[j].val;
    }
    if(i==k) printf("%d", minele);
    else printf("error");

}