# ARM 汇编小 Lab

## Bootstrap

本实验需要配置交叉编译环境和转译执行环境。

首先是 arm-linux-gnueabi 编译工具链。Ubuntu 下可以 apt 安装 `gcc-arm-linux-gnueabi`，Archlinux 是 `arm-linux-gnueabi-gcc`。

然后是虚拟机。x86 可以用编译好的 qemu-arm-static ([link](https://github.com/multiarch/qemu-user-static/releases/download/v7.2.0-1/qemu-arm-static.tar.gz))；当然也可以装包管理器自带的，比如 Ubuntu 和 Archlinux 的 `qemu-user-static`。

## 编译运行

```bash
arm-linux-gnueabi-gcc main.c mm.s -o main -static
qemu-arm-static -L /usr/arm-linux-gnueabi main
```

或者改改 Makefile 直接 `make run`

输入格式：输入两个矩阵，每个矩阵先输入矩阵的 `rows` `columns`，然后输入整个矩阵值。

示例输入：

```txt
1 2 1 2
2 1 3 4
```

输出：

```txt
11
```

解释： $\left(\begin{matrix}1&2\end{matrix}\right)\left(\begin{matrix}3\\4\end{matrix}\right)=(11)$

## 测试

依赖 Python 和 numpy。

`python grade.py` 或 `make test`
