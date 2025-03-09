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

//����Ƿ���Ҫ����ʽ����
bool gOverWrite;

//���ڴ����cdl�ļ���
string gCurrentHandleFileName;

//��ǰ�ļ�ֱ�ӻ������������ļ�����
set<string> gSetCurrentImportFile;
//���ڴ���import���ļ��б�
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

//�жϸ��ļ�������·�����Ƿ���ڣ����ֻ����һ�Σ�����true��absolutePath����Ϊ���ļ��ľ���·��
//��������ڻ��ڶ������·���ж����ڣ�����false
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

//����Ĭ���������·���Լ�����ģʽ
void SetDefaultConfig() {
	char szDirectory[200];
	//��õ�ǰ·��
	_getcwd(szDirectory, sizeof(szDirectory));
	string strInputPath = string(szDirectory);
	cout<<"��ǰĬ��·��Ϊ========="<<strInputPath<<endl;
	AppendSlashToPath(strInputPath);
	//������·�������в��뵱ǰ·��
	gSetInputPath.insert(strInputPath);

	//gOutputPath = "d:/ComponentCode";
	gOutputPath = strInputPath;
	gOverWrite = false;
}

bool CompileFile(string currentFileName)
{
	//gSetCurrentHandleImportFile��һ��list
	gSetCurrentHandleImportFile.push_back(currentFileName);

	//�õ�����·��
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
			//������ڴ���import���ļ��б������ҵ�importFileName��˵������ѭ����������
			if (find(gSetCurrentHandleImportFile.begin(), gSetCurrentHandleImportFile.end(), 
				importFileName) == gSetCurrentHandleImportFile.end()) 
			{
				//���gFileName��ǰ��ֱ�Ӱ������Ӱ������ļ��б������ҵ�importFileName��˵�������ظ���������
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

	//����CDL
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
		cout << "�����������ļ�����·��" << endl;
		cin >> property_path;
	}
	else {
		property_path = argv[1];
	}
	//��ȡ�����ļ�
	if (!ReadFromJsonFile(property_path)) {
		cout << "��ȡ�����ļ�ʧ��" << endl;
		return 1;
	}

	// ��ʾ������Ϣ
	for (auto& port : ports_info) {
		port.second.showPortInfo();
	}

	Initialize();

	gFileName.append(".cdl");

	
	//��CompileFile���������м��ʾ
	if (CompileFile(gFileName)) {
		cout << "Codes generating ... " << endl;

		char* fileName = new char[gFileName.size() + 1];
		char* outputPath = new char[gOutputPath.size() * 2 + 10];
		strcpy(fileName, gFileName.c_str());
		strcpy(outputPath, gOutputPath.c_str());

		//����idl��c����
		CodeGeneration(fileName, outputPath);

		//���ɹ����ļ�
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
