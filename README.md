# CDLC

source code of compiler CDLC

## 2024.10.27

修改了temp/portCtrl.cpp文件，添加了周期型发送数据的模板函数

事件型接收端口只用到了on_data_available函数，ReceiveMegs函数没用到

周期型接收端口（使用采样周期）只需要修改ReceiveMegs函数中的receive_period就可以了，并修改构造函数

采用消息队列方式的接收端口
