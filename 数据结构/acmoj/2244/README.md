# 2244. 下棋

是 36 个节点的最短路问题。但是常规最短路是不能用的，因为最小边推不出松弛后最小。（没错傻傻写了一个 bellman_ford 的就是我）

或许只能指数级遍历？