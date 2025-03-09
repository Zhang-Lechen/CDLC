# CDLC

source code of compiler CDLC

## 使用方式

目前编译生成的CDLC.exe在.\Debug文件夹下，使用CDLC编译生成的项目文件放到.\Generate文件夹下。

当下CDLC只能通过命令行执行（VS Code编译后会报错，原因未知），命令如下

.\Debug\CDLC.exe 【json文件所在路径】

由于json文件当前统统放到了Configuration文件夹下，因此可以直接执行下面的命令：

.\Debug\CDLC.exe .\Configuration\test20241026.json

其他配置文件类似。

## 2024.11.17修改

当前的CDLC已经完成了如下功能：

1. 生成Qt格式的pro文件，之后能用Qt生成dll动态链接库。
2. 修改了命令的读取方式。将原来纯粹从命令行读取修改为从json配置文件读取

下一步的工作是：

1. 配置文件好像存在问题：周期型接收端口若要通过消息队列方式接收，不仅需要指定队列长度，还需要指定接收周期。
2. 修改代码生成部分，把周期性端口的部分加入CodeGeneration.cpp，这部分内容又可以分为三块
   1. 周期型发送
   2. 周期型/采样端口接收
   3. 周期型/消息队列接收

后面不知道还用不用完成Linux平台下的搭建，但是先完成这几样，然后去问问老师。

1完成

2-1：需要修改生成的如下文件：

+ OriginData1.h
+ OriginData1.cpp
+ Transformer.cpp
