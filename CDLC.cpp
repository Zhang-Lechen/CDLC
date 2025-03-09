#define CDL_MAIN

#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <stdio.h>
#include <direct.h>
#include <string>

#include "cdl.h"
#include "Parse.h"
#include "util.h"

#include <algorithm>

using namespace std;

extern FILE *yyin;
extern int yylineno;
void yyrestart(FILE *input_file);
int yyparse();
int yyerrornumber;

void CodeGeneration(char *CDLFile, char *OutputDirectory);
void ProGeneration(string rootDir);

FILE *fp;

//标记是否需要覆盖式生成
bool gOverWrite;

//正在处理的cdl文件名
string gCurrentHandleFileName;

//当前文件直接或间接所包含的文件集合
set<string> gSetCurrentImportFile;
//正在处理import的文件列表
list<string> gSetCurrentHandleImportFile;

void foreachRange(vector<RangeDesc *>::iterator it)
{
	if ((*it)->rangeType == Basic)
	{
		BasicRange *basic = static_cast<BasicRange*>((*it));
		cout << basic->lower << "  " << basic->upper << endl;
	}
	else
	{
		ComplexRange *complex = static_cast<ComplexRange*>((*it));
		for (vector<RangeDesc*>::iterator temp = complex->m_listRange.begin(); temp != complex->m_listRange.end(); temp++)
		{
			foreachRange(temp);
		}
	}
}

//判断该文件在输入路径中是否存在，如果只存在一次，返回true，absolutePath参数为该文件的绝对路径
//如果不存在或在多个输入路径中都存在，返回false
bool FindFileFromInputPath(string fileName, string& absolutePath)
{
	ifstream ifs;
	int fileCount = 0;
	set<string>::iterator iSetInputPath = gSetInputPath.begin();
	while (iSetInputPath != gSetInputPath.end())
	{
		string strPath = *iSetInputPath;
		strPath.append(fileName);
		ifs.open(strPath.c_str());

		if (ifs.is_open())
		{
			absolutePath = strPath;
			fileCount++;
			ifs.close();
		}
		iSetInputPath++;
	}

	if (fileCount == 0)
	{
		cout << "Error: Cannot find the file: " << fileName << "." << endl;
		return false;
	}

	if (1 < fileCount)
	{
		cout << "Error: the file: " << fileName << "exists multiple times." << endl;
		return false;
	}
	return true;
}

//设置默认输入输出路径以及覆盖模式
void SetDefaultConfig() {
	char szDirectory[200];
	//获得当前路径
	_getcwd(szDirectory, sizeof(szDirectory));
	string strInputPath = string(szDirectory);
	cout<<"当前默认路径为========="<<strInputPath<<endl;
	AppendSlashToPath(strInputPath);
	//向输入路径集合中插入当前路径
	gSetInputPath.insert(strInputPath);

	//gOutputPath = "d:/ComponentCode";
	gOutputPath = strInputPath;
	gOverWrite = false;
}

bool CompileFile(string currentFileName)
{
	//gSetCurrentHandleImportFile是一个list
	gSetCurrentHandleImportFile.push_back(currentFileName);

	//得到绝对路径
	string currentFileAbsolutePath;
	if (!FindFileFromInputPath(currentFileName, currentFileAbsolutePath)) {
		return false;
	}

	ifstream ifs(currentFileAbsolutePath);
	string line;
	while (getline(ifs, line)) {
		if (line.find("import") != string::npos) {
			int s = line.find('<');
			int e = line.find('>');
			string importFileName = line.substr(s + 1, e - s - 1);
			//如果正在处理import的文件列表中能找到importFileName，说明产生循环包含错误
			if (find(gSetCurrentHandleImportFile.begin(), gSetCurrentHandleImportFile.end(), 
				importFileName) == gSetCurrentHandleImportFile.end()) 
			{
				//如果gFileName当前已直接包含或间接包含的文件列表中能找到importFileName，说明产生重复包含错误
				if (gSetCurrentImportFile.find(importFileName) == gSetCurrentImportFile.end()) {
					gSetCurrentImportFile.insert(importFileName);
					if (!CompileFile(importFileName)) {
						return false;
					}
				}
				else {
					cout << "Error: reimport file: " << importFileName << "." << endl;
					return false;
				}
			}
			else {
				cout << "Error: circle import file: " << importFileName << "." << endl;
				return false;
			}
		}
	}
	ifs.close();

	gCurrentHandleFileName = currentFileName;

	//解析CDL
	yyin = fopen(currentFileAbsolutePath.c_str(), "r");
	if (yyin == NULL) {
		cout << "Error: Cannot open the file: " << currentFileName.c_str() << "." << endl;
		return false;
	}
	yyrestart(yyin);
	yylineno = 1;
	yyerrornumber = 0;
	int res = yyparse();
	fclose(yyin);
	if (res || yyerrornumber > 0)
	{
		cout << "There are ERRORS ... " << endl;
		return false;
	}

	gSetCurrentHandleImportFile.erase(--gSetCurrentHandleImportFile.end());
	return true;
}

int main(int argc, char *argv[])
{
	string property_path;
	if (argc < 2) {
		cout << "请输入配置文件所在路径" << endl;
		cin >> property_path;
	}
	else {
		property_path = argv[1];
	}
	//读取配置文件
	if (!ReadFromJsonFile(property_path)) {
		cout << "读取配置文件失败" << endl;
		return 1;
	}

	// 显示配置信息
	for (auto& port : ports_info) {
		port.second.showPortInfo();
	}

	Initialize();

	gFileName.append(".cdl");

	
	//在CompileFile里生成了中间表示
	if (CompileFile(gFileName)) {
		cout << "Codes generating ... " << endl;

		char* fileName = new char[gFileName.size() + 1];
		char* outputPath = new char[gOutputPath.size() * 2 + 10];
		strcpy(fileName, gFileName.c_str());
		strcpy(outputPath, gOutputPath.c_str());

		//生成idl和c代码
		CodeGeneration(fileName, outputPath);

		//生成工程文件
		ProGeneration(outputPath);

		delete[] fileName;
		delete[] outputPath;

		cout << "Code generation completed .... " << endl;
		cout << "Press any key to exit compiler .... " << endl;

		getchar();
	}
	getchar();
	system( "PAUSE ");
	return 0;

}
