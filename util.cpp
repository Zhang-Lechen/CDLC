#include "util.h"

map<string, PortInfo> ports_info;
//存储命令行参数-i后的输入路径以及默认输入路径，使用set是为了不存储相同路径
set<string> gSetInputPath;
//输入的cdl文件名
string gFileName;
//存储命令行参数-o后的输出路径
string gOutputPath;

ENVIRONMENT environment;

// 简单的函数，用于去掉字符串两端的空白字符
string trim(const string& str) {
    const char* whitespace = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(whitespace);
    size_t end = str.find_last_not_of(whitespace);
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

void AppendSlashToPath(string& path) {
    if (environment == WINDOWS) {
        if (path[path.size() - 1] != '\\' && path[path.size() - 1] != '/') {
            path.append("\\");
        }
    }
    else {
        if (path[path.size() - 1] != '/') {
            path.append("/");
        }
    }
}

size_t getJsonVal(const string& line, string& val, size_t beg)
{
    if (line.find('"', beg)!=string::npos) {
        size_t start_quote = line.find('"', beg);
        size_t end_quote = line.find('"', start_quote+1);
        if (start_quote != string::npos && end_quote != string::npos) {
            val = line.substr(start_quote + 1, end_quote - start_quote - 1);
            val = trim(val);
            return end_quote + 1;
        }
    }
    return 0;
}

bool getJsonIntVal(const string& line, int& val, size_t beg)
{
    size_t colon_pos = line.find(':', beg);
    if (colon_pos != string::npos) {
        string number_str = line.substr(colon_pos + 1);
        try {
            val = stoi(trim(number_str));
            return true;
        } catch (const invalid_argument& e) {
            cerr << "解析整数时出错: " << e.what() << endl;
        }
    }
    return false;
}

bool ReadPortInfoFromJson(ifstream& ifs, const string& port_name)
{
    if (ports_info.find(port_name) != ports_info.end()) {
        cerr << "端口\"" << port_name << "\"重复定义" << endl;
        return false;
    }
    PortInfo port;
    port.name = port_name;
    string line;
    while (getline(ifs, line)) {
        // 到达端口定义的末尾
        if (line.find('}')!=string::npos) {
            break;
        }
        string key;
        size_t pos = getJsonVal(line, key, 0);
        if (pos != 0) {
            // consume端口消息接收方式,分为周期型和事件型
            if (key == "message") {
                string msg;
                if (!getJsonVal(line, msg, pos)) {
                    cerr << "没有给出消息接收方式" << endl;
                    return false;
                }
                port.message = (msg == "event") ? port.EVENT : port.PERIODIC;
            }
            // 端口类型,分为publish和consume
            else if (key == "type") {
                string tp;
                if (!getJsonVal(line, tp, pos)) {
                    cerr << "没有给出端口类型" << endl;
                    return false;
                }
                port.port_type = (tp == "publish") ? port.PUBLISH : port.CONSUME;
            }
            // consume端口处理方式,分为采样和消息队列
            else if (key == "method") {
                string mthd;
                if (!getJsonVal(line, mthd, pos)) {
                    cerr << "没有给出端口处理方式" << endl;
                    return false;
                }
                port.behavior = (mthd == "sample") ? port.SAMPLING : port.MSGQUEUE;
            } else if (key == "length") {
                int len;
                if (!getJsonIntVal(line, len, pos)) {
                    cerr << "没有正确给出队列长度" << endl;
                    return false;
                }
                port.queue_length = len;
            } else if (key == "period") {
                int period;
                if (!getJsonIntVal(line, period, pos)) {
                    cerr << "没有正确给出周期" << endl;
                    return false;
                }
                if (port.port_type == port.CONSUME && port.behavior == port.SAMPLING)
                    port.sampling_interval = period;
                // 这里对于consume端口的消息队列做了修改，添加了接收周期
                else if (port.port_type == port.CONSUME && port.behavior == port.MSGQUEUE)
                    port.recv_period = period;
                else
                    port.send_period = period;
            }
            else {
                cout << line << endl;
                cerr << "未定义的端口行为!" << endl;
                return false;
            }
        }
    }
    ports_info[port_name] = port;
    return true;
}

bool ReadFromJsonFile(const string& path)
{
	ifstream ifs(path);
	if (!ifs.is_open()) {
        cerr << "无法打开文件: " << path << endl;
        return false;
    }

    string line;
    // 首先获取文件名
    while (getline(ifs, line)) {
        // 当出现"且出现{时，判断为找到文件名
        if (line.find('"')!=string::npos) {
            if (!getJsonVal(line, gFileName, 0)) {
                cerr << "未正确输入CDL文件名!" << endl;
                return false;
            }
            break;
        }
    }
    while (getline(ifs, line)) {
        string key;
        size_t pos;
        if ((pos = getJsonVal(line, key, 0)) != 0) {
            if (key == "env") {
                string env;
                if (!getJsonVal(line, env, pos)) {
                    cerr << "没有正确指定运行环境!" << endl;
                    return false;
                }
                environment = (env == "windows") ? WINDOWS : LINUX;
            } else if (key == "inputpath") {
            	string strInputPath;
                if (!getJsonVal(line, strInputPath, pos)) {
                    cerr << "请给出正确的输入路径" << endl;
                    return false;
                }
                AppendSlashToPath(strInputPath);
                gSetInputPath.insert(strInputPath);
            } else if (key == "outputpath") {
                if (!getJsonVal(line, gOutputPath, pos)) {
                    cerr << "请给出正确的输出路径" << endl;
                    return false;
                }
                AppendSlashToPath(gOutputPath);
            }
            // 说明是端口的定义
            else {
                if(!ReadPortInfoFromJson(ifs, key))
                    return false;
            }
        }
    }
    return true;
}

// 通用平台下的文件复制函数
bool copyFile(const string& sourcePath, const string& destPath) {
    // 打开源文件
    ifstream source(sourcePath, ios::binary);
    // 打开目标文件
    ofstream dest(destPath, ios::binary);

    // 检查源文件是否成功打开
    if (!source.is_open()) {
        cerr << "Error: Could not open source file: " << sourcePath << endl;
        return false;
    }

    // 检查目标文件是否成功打开
    if (!dest.is_open()) {
        cerr << "Error: Could not open destination file: " << destPath << endl;
        return false;
    }

    // 复制文件内容
    dest << source.rdbuf();

    // 关闭文件
    source.close();
    dest.close();

    return true;
}

// PortInfo类的成员函数实现
void PortInfo::showPortInfo()
{
    cout << "Port Name: " << name << endl;
    switch (port_type) {
        case PUBLISH:
            cout << "PUBLISH\t";
            break;
        case CONSUME:
            cout << "CONSUME\t";
            break;
    }
    switch (message) {
        case PERIODIC:
            cout << "PERIODIC\t";
            break;
        case EVENT:
            cout << "EVENT\t";
            break;
    }
    if (message == PERIODIC && port_type == PUBLISH) {
        cout << send_period << endl;
    }
    else if (message == PERIODIC && port_type == CONSUME) {
        switch (behavior) {
            case SAMPLING:
                cout << "Sampling Interval: " << sampling_interval << "ms" << endl;
                break;
            case MSGQUEUE:
                cout << "Queue Length: " << queue_length << '\t';
                cout << "Receive Period: " << recv_period << "ms" << endl;
                break;
        }
    }
    else {
        cout << endl;
    }
}

int getPublishPeriod(ComponentPortDesc *pPort)
{
    if (ports_info.find(pPort->getName()) == ports_info.end()) {
        cerr << "Error: Port \"" << pPort->getName() << "\" not found." << endl;
        return -1;
    }
    PortInfo port = ports_info[pPort->getName()];
    if (port.port_type == PortInfo::PUBLISH && port.message == PortInfo::PERIODIC) {
        return port.send_period;
    }
    return 0;
}

