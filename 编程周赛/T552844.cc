//T552844 24fa 4-1 校园基建计划
//https://www.luogu.com.cn/problem/T552844?contestId=221092

#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    
    using PQ = pair<int, int>;
    
    vector<PQ> v(m);
    for(int i = 0; i < m; ++i)
    {
        cin >> v[i].first >> v[i].second;
    }
    
    priority_queue<PQ, vector<PQ>, greater<PQ>> students(greater<PQ>(), move(v));//所有学生
    priority_queue<int, vector<int>, greater<int>> charge;//充电
    int wait = 0;
    
    for(int t = 1; ; )
    {
        while(!charge.empty() && charge.top() <= t)
            charge.pop();
        
        while(charge.size() < n && !students.empty() && students.top().first <= t)
        {
            wait += t - students.top().first;
            charge.push(t + students.top().second);
            students.pop();
        }
        
        if(students.empty()) break;
        t = students.top().first;
        if(charge.size() == n) t = max(t, charge.top());
    }
    
    cout << wait;
    
    return 0;
}