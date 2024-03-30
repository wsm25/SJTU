# Bootstrap

## Energia
在 [Download Energia](https://energia.nu/download/) 下载合适版本的
Energia IDE，解压到合适位置，

在 [Guide to the MSP430F5529 LaunchPad](https://energia.nu/pinmaps/msp-exp430f5529/#_installing_the_drivers)
下载合适版本的驱动，安装。

连接开发板，启动 Energia，会自动提示安装开发板组件。注意安装 MSP430 1.0.7 版本。

选一个示例程序，上传运行。

## VS Code
喜欢用 VS Code 开发的小朋友（比如我）可以添加以下配置：
```json
{
    "C_Cpp.default.forcedInclude": [
        "${base}\\energia\\hardware\\energia\\msp430\\cores\\msp430\\Energia.h"
    ],
    "C_Cpp.default.includePath": [
        "${base}\\energia\\hardware\\tools\\msp430\\msp430\\include",
        "${base}\\energia\\hardware\\energia\\msp430\\cores\\msp430",
        "${base}\\energia\\hardware\\energia\\msp430\\variants\\MSP-EXP430F5529LP"
    ]
}
```

其中 `${base}` 是你 energia 解压到的位置。