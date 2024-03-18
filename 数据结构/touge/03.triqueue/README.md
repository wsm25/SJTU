# NewQueue

编程实现可以分别在头部`Front`、中间`Middle`以及尾部`Rear`执行进队`EnQueue`和出队`DeQueue`功能的队列 `NewQueue`。

在 `NewQueue` 类中完成以下函数：

- `void EnFront(int x)` : 在队列头部进队值为 x 的结点；
- `void EnMiddle(int x)` : 在队列正中间进队值为 x 的结点；
- `void EnRear(int x)` : 在队列尾部进队值为 x 的结点；
- `int DeFront()` : 将队列头部结点出队，队列为空时返回-1；
- `int DeMiddle()` : 将队列正中间结点出队，队列为空时返回-1；
- `int DeRear()` : 将队列尾部结点出队，队列为空时返回-1；

注1：当Middle指示两个可能的中间位置时，选择靠前位置进行操作，例如：

- 对队列 `[1, 2, 3, 4, 5]` 执行 `EnMiddle(100)`，结果为 `[1, 2, 100, 3, 4, 5]`；
- 对队列 `[1]` 执行 `EnMiddle(100)`，结果为 `[100, 1]`；
- 对队列 `[1, 2, 3, 4]` 执行 `DeMiddle`，结果为 `[1, 3, 4]`；
- 对队列 `[1, 2]` 执行 `DeMiddle()`，结果为 `[2]`；

注2：所有出队De操作必须判断当前队列是否为空，测试用例中会存在空时出队的情况，该情况下无需进行操作。

注3：实现时注意各操作对于不同指针的影响。

注4：禁止使用 STL 实现。

## 输入描述
输入一行，包含多组操作，操作由操作名称（与函数名称相同）和数值组成，例如 `EnFront 25`，中间以空格间隔，各组操作同样以空格间隔，数值均为`int`类型。

## 输出描述
输出一行，为从头部到尾部遍历的结点值，若队列为空，则输出 `"null"`。

## 输入输出例
```
EnFront 13 EnRear 21 EnMiddle 5 DeRear -1 DeMiddle -1
```
```
5
```
```
EnMiddle 13 EnRear 21 EnMiddle 5 DeRear -1 DeMiddle -1 DeMiddle -1
```
```
null
```