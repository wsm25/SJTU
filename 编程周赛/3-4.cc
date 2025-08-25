#include <stdio.h>
#include <vector>

using std::vector;

int main() {
    const int* pa;
    int* const pb = 0;
    int const* pc;
    int* pd const;

    *pa=1;
    *pb=1;
    *pc=1;
    *pd=1;



    int s,n;
    scanf("%d%d", &s, &n);
    vector<vector<int>> dp(n + 1, vector<int>(s + 1, 0));
    dp[0][1]=1;
    printf("%d", dp[1][1]);
    return 0;
}

class X {
public:
    void greet() const {
        printf("hello, world!");
    }
};