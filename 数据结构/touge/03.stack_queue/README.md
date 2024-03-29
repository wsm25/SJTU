# 栈or队列

栈和队列都提供 Push/Pop 两种操作，其中 Push：加入一个元素。Pop：弹出一个元素。给出一个线性结构的进出顺序，判定这个结构是栈还是队列。(40') 

## 输入描述

第一行输入一个整数s，代表有s组测试数据。

对于每组测试数据，第一行输入一个整数 n，代表操作的次数 (3<=n<=1000)。 随后输入 n 行，每行包含两个整数 type val。 当 type = 1时，表示该次操作为 push 操作，val 表示进入的数字。当 type=2 时，表示该次操作为 pop 操作，val 代表出来的数字。 输入的数值间用空格分隔。

## 输出描述

对每组测试数据输出一行， 输出该组数据对应的线性结构，若为栈则输出”Stack”，若为队列则输出“Queue”，若两者都是则输出“Both”，若两者都不是则输出“Error”。

## 举例

输入：
```
2 
6 
1 1 
1 2 
1 3 
2 3 
2 2 
2 1 
4 
1 1 
1 2 
2 1 
2 2
```
注意：输入的数值间用空格分隔。

输出：
```
Stack 
Queue
```

输入：
```
1
8
1 5
1 7
1 7
1 3
2 3
2 5
2 7
2 7
```
输出：
```
Error
```

## 注意事项

- 每个测试用例中有多组测试，每组测试输入输出可能是 不等 的，因此在进行下一组测试之前要把目前还没出栈/队的元素清空，不然就会影响下一组测试。
- 输入输出可能发生在任意位置，并非先全部输入再全部输出。

