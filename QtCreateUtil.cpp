#include"QtCreateUtil.h"
#include <objbase.h>  
#include <stdio.h>
#include <time.h>
#include <iomanip>

#define GUID_LEN 64 

// Qt的pro文件还需要UUID吗？
bool QtCreateUtil::generateProjectUUID(void)
{
	return true;
}

// bool QtCreateUtil::generateProjectUUID(void)
// {
// 	char buffer[GUID_LEN] = { 0 };

// #ifndef LINUX
// 	GUID guid;
// 	if (CoCreateGuid(&guid))
// 	{
// 		fprintf(stderr, "create guid error\n");
// 		return -1;
// 	}
// 	_snprintf(buffer, sizeof(buffer),
// 		"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
// 		guid.Data1, guid.Data2, guid.Data3,
// 		guid.Data4[0], guid.Data4[1], guid.Data4[2],
// 		guid.Data4[3], guid.Data4[4], guid.Data4[5],
// 		guid.Data4[6], guid.Data4[7]);
// 	//printf("guid: %s\n", buffer);
	
// #else
//     // 设计Linux版本的获取uuid
//     uuid_t uuid;
//     uuid_generate(uuid);
//     uuid_unparse(uuid, buffer);
// #endif

//     projectUUID = buffer;
// 	return true;
// }
//加载配置文件填充数据
bool QtCreateUtil::loadProperties(std::string rootDir, std::string componentname, std::string cdlName,  int IfUiComponent, std::vector<std::string> listInfacePort)
{
	proType = 1 ;//vcxprojType=1 Release版本的有tinyxml
	//利用BOOST_PATH
	additionalIncludeDirectories = "$(BOOST_PATH)"; //boost安装目录 boost
	//additionalLibraryDirectories = additionalIncludeDirectories+"\\lib32-msvc-10.0;";
	additionalLibraryDirectories = additionalIncludeDirectories+"\\stage\\lib;";//boost 安装目录 //组装完毕
	ComponentName = componentname;
	fileDir = rootDir;
	rootNamespace = cdlName;
	clInclude = rootDir;
	clCompile = clInclude;
	m_listInterfacePort.assign(listInfacePort.begin(),listInfacePort.end()); // 填充m_listInterfacePort的名称
	//判断ui还是服务
	this->IfUiComponent = IfUiComponent;
	//GUID是否成功生成
    /////////////ZLC MODIFIED//////////////
    return generateProjectUUID();
    // if(false == generateProjectUUID())
	// 	return false;
	// return true;
    /////////////ZLC MODIFIED//////////////
}

bool QtCreateUtil::CreateReleaseProFile()
{
	if(this->IfUiComponent == 2)
	{
		CreateReleaseUIFile();
	}
	else if(this->IfUiComponent == 1)
	{
		CreateReleaseServiceFile();
	}
	return true;
}

bool QtCreateUtil::CreateReleaseUIFile()
{
	// 后面再改
    // string nowDir = fileDir+"/"+rootNamespace+"_CDL/Debug/";
	// cout << "nowDir: " << nowDir << endl;
    string proFile = fileDir + "/Component/" + ComponentName + "/" + ComponentName + ".pro";//pro文件
	cout << "proFile: " << proFile << endl;
	
    ofstream fout(proFile);
	if (!fout.is_open()) {
		cerr << "Error: Could not open file: " << proFile << endl;
		return false;
	}
    time_t curr_time;
    struct tm *p;
    time(&curr_time); // 获取从1970至今过了多少秒，存入time_t类型的timep
    p = localtime(&curr_time); // 用localtime将秒数转化为struct tm结构体

    // 尊重原生的Qt Pro文件格式
    fout << "#-------------------------------------------------\n#" << endl;
    fout << "# Project created by QtCreator " << 1900+p->tm_year << "-" << setw(2) << setfill('0') << 1+p->tm_mon << "-" << setw(2) << setfill('0')
        << p->tm_mday << "T" << p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec << endl;
    fout << "#\n#-------------------------------------------------" << endl;

#ifndef LINUX
	fout << "TEMPLATE = lib" << endl;
	fout << "TARGET = " << ComponentName << endl;
	fout << "DESTDIR = " << "\"./Debug\"" << endl;
	fout << "QT += core widgets gui" << endl;
	fout << "CONFIG += debug" << endl;
	fout << "DEFINES += NDDS_DLL_VARIABLE RTI_WIN32 _CONSOLE RTI_STATIC" << endl;
	
	fout << "INCLUDEPATH += \"./GeneratedFiles\" \\" << endl;
	fout << "\"./GeneratedFiles/$(Configuration)\" \\" << endl;
	fout << "\"$(BOOST_PATH)/boost_1_58_0\" \\" << endl;
	fout << "\"$(ECOM_PATH)/Release\" \\" << endl;
	fout << "\"$(NDDSHOME)/include\" \\" << endl;
	fout << "\"$(NDDSHOME)/include/ndds\" \\" << endl;
	fout << "\"./../../IDLGenerate\"" << endl;

	fout << "FORMS += \"" << ComponentName << ".ui\"" << endl;

	// 下面可能包含与Windows平台相关的库，需要替换为平台无关的库（先这么写）
	fout << "LIBS += -L\"$(NDDSHOME)/lib/i86Win32VS2010\" \\" << endl;
	fout << "\t-L\"$(BOOST_PATH)/boost_1_58_0/stage/lib\" \\" << endl;
	fout << "\t-lrticonnextmsgcppd \\" << endl;
	fout << "\t-lnddscppd \\" << endl;
	fout << "\t-lnddscd \\" << endl;
	fout << "\t-lnddscored \\" << endl;
	fout << "\t-lnetapi32 \\" << endl;
	fout << "\t-ladvapi32 \\" << endl;
	fout << "\t-luser32 \\" << endl;
	fout << "\t-lWS2_32" << endl;

	fout << "DEPENDPATH += \".\"" << endl;
	fout << "MOC_DIR += \"./GeneratedFiles/debug\"" << endl;
	fout << "OBJECTS_DIR += debug" << endl;
	fout << "UI_DIR += \"./GeneratedFiles\"" << endl;
	fout << "RCC_DIR += \"./GeneratedFiles\"" << endl;

	fout << "HEADERS += \"../../include/" << rootNamespace + ".h\" \\" << endl;
	fout << "\t\"./include/" << ComponentName + ".h\" \\" << endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDL.h\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLPlugin.h\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLSupport.h\"";
	for (auto it = m_listInterfacePort.begin(); it != m_listInterfacePort.end(); it++) {
		fout << " \\\n\t\"./include/" << *it << ".h\"";
	}

	fout << "SOURCES += \"../../sources/" << rootNamespace + ".cpp\" \\" << endl;
	fout << "\t\"./sources/" << ComponentName + ".cpp\" \\" << endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDL.cxx\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLPlugin.cxx\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLSupport.cxx\"";
	// 将接口和端口的文件写入
	for (auto it = m_listInterfacePort.begin(); it != m_listInterfacePort.end(); it++) {
		fout << " \\\n\t\"./sources/" << *it << ".cpp\"";
	}
	// 最后在Pro文件中写入moc自动生成的文件
	fout << " \\\n\t\"./GeneratedFiles/Debug/moc_" << ComponentName + ".cpp\"" << endl;
#else
	;
#endif
}

bool QtCreateUtil::CreateReleaseServiceFile()
{
	// string nowDir = fileDir+"/"+rootNamespace+"_CDL/Debug/";
    string proFile = fileDir + "/Component/" + ComponentName + "/" + ComponentName + ".pro";//pro文件

    ofstream fout(proFile);
    time_t curr_time;
    struct tm *p;
    time(&curr_time); // 获取从1970至今过了多少秒，存入time_t类型的timep
    p = localtime(&curr_time); // 用localtime将秒数转化为struct tm结构体

    // 尊重原生的Qt Pro文件格式
    fout << "#-------------------------------------------------\n#" << endl;
    fout << "# Project created by QtCreator " << 1900+p->tm_year << "-" << setw(2) << setfill('0') << 1+p->tm_mon << "-" << setw(2) << setfill('0')
        << p->tm_mday << "T" << p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec << endl;
    fout << "#\n#-------------------------------------------------" << endl;

#ifndef LINUX
	fout << "TEMPLATE = lib" << endl;
	fout << "TARGET = " << ComponentName << endl;
	fout << "DESTDIR = " << "\"./Debug\"" << endl;
	fout << "QT += core" << endl;
	fout << "CONFIG += debug" << endl;
	fout << "DEFINES += NDDS_DLL_VARIABLE RTI_WIN32 _CONSOLE RTI_STATIC" << endl;
	
	fout << "INCLUDEPATH += \"./GeneratedFiles\" \\" << endl;
	fout << "\"./GeneratedFiles/$(Configuration)\" \\" << endl;
	fout << "\"$(BOOST_PATH)/boost_1_58_0\" \\" << endl;
	fout << "\"$(ECOM_PATH)/Release\" \\" << endl;
	fout << "\"$(NDDSHOME)/include\" \\" << endl;
	fout << "\"$(NDDSHOME)/include/ndds\" \\" << endl;
	fout << "\"./../../IDLGenerate\"" << endl;

	// 下面可能包含与Windows平台相关的库，需要替换为平台无关的库（先这么写）
	fout << "LIBS += -L\"$(NDDSHOME)/lib/i86Win32VS2010\" \\" << endl;
	fout << "\t-L\"$(BOOST_PATH)/boost_1_58_0/stage/lib\" \\" << endl;
	fout << "\t-lrticonnextmsgcppd \\" << endl;
	fout << "\t-lnddscppd \\" << endl;
	fout << "\t-lnddscd \\" << endl;
	fout << "\t-lnddscored \\" << endl;
	fout << "\t-lnetapi32 \\" << endl;
	fout << "\t-ladvapi32 \\" << endl;
	fout << "\t-luser32 \\" << endl;
	fout << "\t-lWS2_32" << endl;

	fout << "DEPENDPATH += \".\"" << endl;
	fout << "MOC_DIR += \"./GeneratedFiles/debug\"" << endl;
	fout << "OBJECTS_DIR += debug" << endl;
	fout << "RCC_DIR += \"./GeneratedFiles\"" << endl;

	fout << "HEADERS += \"../../include/" << rootNamespace + ".h\" \\" << endl;
	fout << "\t\"./include/" << ComponentName + ".h\" \\" << endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDL.h\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLPlugin.h\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLSupport.h\"";
	for (auto it = m_listInterfacePort.begin(); it != m_listInterfacePort.end(); it++) {
		fout << " \\\n\t\"./include/" << *it << ".h\"";
	}

	fout << "SOURCES += \"../../sources/" << rootNamespace + ".cpp\" \\" << endl;
	fout << "\t\"./sources/" << ComponentName + ".cpp\" \\" << endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDL.cxx\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLPlugin.cxx\" \\" <<endl;
	fout << "\t\"../../IDLGenerate/" << rootNamespace + "IDLSupport.cxx\"";
	// 将接口和端口的文件写入
	for (auto it = m_listInterfacePort.begin(); it != m_listInterfacePort.end(); it++) {
		fout << " \\\n\t\"./sources/" << *it << ".cpp\"";
	}
	// 最后在Pro文件中写入moc自动生成的文件
	fout << " \\\n\t\"./GeneratedFiles/Debug/moc_" << ComponentName + ".cpp\"" << endl;
#else
	;
#endif
}

bool QtCreateUtil::generateProFile()
{
	return CreateReleaseProFile();
	//return (flag1&&flag2);
}

