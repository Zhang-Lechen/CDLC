#ifndef QT_CREATE_UTIL_H
#define QT_CREATE_UTIL_H

// #pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>

using namespace std;

class QtCreateUtil
{
private:
	int proType;//没有用到
	std::string fileDir;// 文件根目录
	std::string rootNamespace;// =cdlName
	std::string projectUUID;// 通过generateProjectGuid生成
	std::string ComponentName;// =componentName
	std::string additionalIncludeDirectories;// boost安装目录
	std::string additionalLibraryDirectories;// boost安装目录/stage/lib
	std::string clInclude;// 文件根目录
	std::string clCompile;// =clInclude=文件根目录
	//std::string targetName;
	int IfUiComponent;// 判断是UI还是组件
	//接口和端口名称
	std::vector<std::string> m_listInterfacePort;
public:
	bool generateProjectUUID(void);
	std::string TCHAR2STRING(TCHAR *STR);
	bool loadProperties(std::string rootDir,std::string componentname,std::string cdlName, int IfUiComponent, std::vector<std::string> listInfacePort);

    bool CreateDDSProFile();
	bool CreateReleaseProFile();
	bool CreateReleaseUIFile();
	bool CreateReleaseServiceFile();

	bool generateProFile();
};

#endif // !QT_CREATE_UTIL_H
