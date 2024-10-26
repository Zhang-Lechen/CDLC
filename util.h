#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <stdio.h>
#include <direct.h>
#include <string>
#include <map>

// JSON文件规范：每一行只能有一个信息。不能在一行定义多个变量
// 左花括号({)在定义文件名和端口名时最好和它们在同一行
// 右花括号要使用独立的一行,不能和变量定义放在同行

using namespace std;

struct PortInfo
{
    string name;
    // 消息接收方式
    enum Message {
        PERIODIC,
        EVENT
    }message;
    // 何种端口
    enum PortType {
        PUBLISH,
        CONSUME
    }port_type;
    // 若为接收端口，用何种方式接收
    enum Behavior {
        SAMPLING,
        MSGQUEUE
    }behavior;
    union {
        int sampling_interval;
        int queue_length;
        int send_period;
    };

    // 显示端口信息
    void showPortInfo();
};

enum ENVIRONMENT {
    WINDOWS, 
    LINUX
};

extern map<string, PortInfo> ports_info;
//存储命令行参数-i后的输入路径以及默认输入路径，使用set是为了不存储相同路径
extern set<string> gSetInputPath;
//输入的cdl文件名
extern string gFileName;
//存储命令行参数-o后的输出路径
extern string gOutputPath;

extern ENVIRONMENT environment;

void AppendSlashToPath(string& path);
bool ReadFromJsonFile(const string& path);
bool copyFile(const std::string& sourcePath, const std::string& destPath);

#endif
