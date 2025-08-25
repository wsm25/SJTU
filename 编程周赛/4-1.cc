#include <queue>
#include <algorithm>
#include <stdio.h>

// (arrival, duration)
using Pal = std::pair<int, int>;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if(n>=m) {
        putchar('0');
        return 0;
    }
    // n<m
    Pal *pals = new Pal[m];
    for(int i=0; i<m; i++) 
        scanf("%d%d", &pals[i].first, &pals[i].second);
    std::sort(pals, pals+m);
    std::priority_queue<int, std::vector<int>, std::greater<int>> chargers;
    int wait=0;
    for(int i=0; i<n; i++) chargers.push(pals[i].first+pals[i].second);
    for(int i=n; i<m; i++) {
        int now = chargers.top(); chargers.pop();
        if (now<=pals[i].first) {
            chargers.push(pals[i].first+pals[i].second);
        } else {
            wait += now - pals[i].first;
            chargers.push(now+pals[i].second);
        }
    }
    printf("%d", wait);
    delete []pals;
}