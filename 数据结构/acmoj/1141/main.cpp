#include <cstdio>
#include <cstdlib>
#include <cstring>
#define OFFSET '0'
#define MAX 2000000
struct Trie{
    // root: pool[0]
    int pool[MAX][43];
    int cur; // pool len
    Trie():cur(0){memset(pool, -1, 43*MAX*sizeof(int));}
    bool insert(char* s){
        bool is_new=false;
        int i=0;
        while(*s!=0){
            if(pool[i][*s]==-1){
                pool[i][*s]=++cur;
                is_new=true;
            }
            i=pool[i][*s];
            s++;
        }
        return is_new;
    }
};
void getline(char* buf){
    while((*buf=getchar())!='\n' && *buf!=EOF) buf++;
    *buf=0;
}

int main(){
    int n; scanf("%d", &n);
    int cnt=0;
    Trie trie;
    char buf[1500];
    for(int i=0; i<n; i++){
        getline(buf);
        cnt+=trie.insert(buf);
    }
    printf("%d", cnt);
}