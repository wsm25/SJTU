# 1295. `#include <random>`

由 [Min number of primes up to n](https://mathoverflow.net/questions/208621/min-number-of-primes-up-to-n)，
我们可以对于 `n>60000` 做 $p=\frac{\pi(n)}{n^2/2}=\frac2{n(\ln n-1.1)}$。

更小的可以尝试 $O(n\log\log n)$[^1] 的欧拉筛法。

[^1]: https://en.wikipedia.org/wiki/Divergence_of_the_sum_of_the_reciprocals_of_the_primes