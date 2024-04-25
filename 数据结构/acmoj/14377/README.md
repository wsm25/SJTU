# 14377. 二叉搜索树的形状

好数学...

基础思路：
$$
p(n)=
\left\{  
    \begin{array}{ll}  
    1, & n\le 1 \\  
    \sum _{i=0}^{n-1}{p(i)\cdot p(n-i-1)}, &\text{otherwise}
    \end{array}  
\right.  
$$

转成 dp...这就过了？那些更快的是打表了吗...