#include <stdio.h>

int r() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

double max_avg(long long* x, int n, int ml) {
    double max = 0;
    for(int i=0; i<n; i++)
        for(int j=i+ml; j<=n; j++) {
            double avg = (double)(x[j]-x[i])/(double)(j-i);
            if (avg > max) max = avg;
        }
    return max;
}

void input(long long* x, int n) {
    long long sum = 0;
    x[0] = 0;
    for(int i=1; i<=n; i++) {
        sum += r();
        x[i] = sum;
    }
}

int main() {
    int n=r(), m=r(), x=r(), y=r();
    long long *a=new long long[n+1], *b=new long long[m+1];
    input(a, n); input(b, m);
    printf("%.6f", max_avg(a,n,x)+max_avg(b,m,y));
    delete []a; delete []b;
    return 0;
}