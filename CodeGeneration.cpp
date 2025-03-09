
#include "cdl.h"
#include <io.h>
#include <direct.h>
// #include "VcxprojCreateUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
// #include <atlbase.h> 
// #include <atlstr.h>
#include <vector>
/////////////ZLC MODIFIED//////////////
#include "QtCreateUtil.h"
#include "util.h"
#include "Periodic.h"
/////////////ZLC MODIFIED//////////////
string RootDir;
string CDLName;
string CDLDir;

string EcomPath;
string getTime();

bool Now_Gen_Test = true;//true 生成dds代码,false生成release代码
// lian add   判断void是转成int还是void
bool VoidJudge = false;//false 表示void转void  ture表示void转int

void GetCDLName(char *CDLFile)
{
	string Path(CDLFile);
	int pos = Path.find_last_of('/');
	Path = Path.substr(pos + 1);
	pos = Path.find_last_of('.');
	if (pos <= 0)
	{
		// Has no extention or invalid extention name
		CDLName.assign("NOCDLNAME");
		return;
	}
	CDLName = Path.substr(0, pos);
}
//基本数据类型的映射
void GenerateFundmemtalTypeNameIDL(FILE *fpIDL, int Type)
{
	switch (Type)
	{
	case T_SHORT:
		fprintf(fpIDL, "short ");
		break;
	case T_UNSINGED_SHORT:
		fprintf(fpIDL, "unsigned short ");
		break;
	case T_LONG:
		fprintf(fpIDL, "long ");
		break;
	case T_UNSIGNED_LONG:
		fprintf(fpIDL, "unsigned long ");
		break;
	case T_LONG_LONG:
		fprintf(fpIDL, "long long ");
		break;
	case T_UNSIGNED_LONG_LONG:
		fprintf(fpIDL, "unsigned long long ");
		break;
	case T_FLOAT:
		fprintf(fpIDL, "float ");
		break;
	case T_DOUBLE:
		fprintf(fpIDL, "double ");
		break;
	case T_CHAR:
		fprintf(fpIDL, "char ");
		break;
	case T_BOOLEAN:
		fprintf(fpIDL, "boolean ");
		break;
	case T_OCTET:
		fprintf(fpIDL, "octet ");
		break;
	case T_STRING:
		// Deal with later
		fprintf(fpIDL, "string ");
		break;
	case T_VOID:
		if (VoidJudge==true)
			fprintf(fpIDL, "int ");
		else
			fprintf(fpIDL, "void ");
		break;
	}
}
//基本数据类型的映射
void GenerateFundmemtalTypeName(FILE *fpHeader, int Type)
{
	switch (Type)
	{
	case T_SHORT:
		fprintf(fpHeader, "short ");
		break;
	case T_UNSINGED_SHORT:
		fprintf(fpHeader, "unsigned short ");
		break;
	case T_LONG:
		fprintf(fpHeader, "int ");
		break;
	case T_UNSIGNED_LONG:
		fprintf(fpHeader, "unsigned long ");
		break;
	case T_LONG_LONG:
		fprintf(fpHeader, "long ");
		break;
	case T_UNSIGNED_LONG_LONG:
		fprintf(fpHeader, "unsigned long ");
		break;
	case T_FLOAT:
		fprintf(fpHeader, "float ");
		break;
	case T_DOUBLE:
		fprintf(fpHeader, "double ");
		break;
	case T_CHAR:
		fprintf(fpHeader, "char ");
		break;
	case T_BOOLEAN:
		fprintf(fpHeader, "bool ");
		break;
	case T_OCTET:
		fprintf(fpHeader, "unsigned char ");
		break;
	case T_STRING:
		// Deal with later
		fprintf(fpHeader, "DDS_Char* ");
		break;
	case T_VOID:
		if (VoidJudge==true)
			fprintf(fpHeader, "int ");
		else
			fprintf(fpHeader, "void ");
		break;
	}
}
//cdl文件除了构件另外实体的c++代码
void CDLFile::GenerateBasicEntity(FILE *fpHeader, FILE *fpSource,FILE *fpIDL)
{
	vector<CDLEntity *>::iterator it;
	for (it = m_listCDLEntity.begin(); it != m_listCDLEntity.end(); ++it)
	{
		CDLEntity *pEntity = *it;
		int EntityType = pEntity->getType();
		if (EntityType != T_COMPONENT)
			pEntity->CodeGeneration(fpHeader, fpSource,fpIDL);
	}
}

//枚举类型不变
void ENumEntity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{
	fprintf(fpIDL, "enum %s { ", getName().c_str());
	vector<string>::iterator it;
	for (it = m_listValueName.begin(); it != m_listValueName.end(); ++it)
	{
		if (it != m_listValueName.begin())
			fprintf(fpIDL, ", ");
		fprintf(fpIDL, (*it).c_str());
	}
	fprintf(fpIDL, " }; \n\n");
}
//Now_Gen_Test 没修改
//Sequence类型
void VectorEntity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{
	fprintf(fpIDL, "struct ");
	fprintf(fpIDL, "%s \n{\n", m_sName.c_str());
	if (length == 0)//说明是向量第一种形式，不定长数组
	{
		fprintf(fpIDL, "\nsequence<");
		if (m_type->m_iType < 0)//基础数据类型
		{
			GenerateFundmemtalTypeNameIDL(fpIDL, m_type->m_iType);
		}
		else
		{
			fprintf(fpIDL, "%s ", m_type->m_pTypeDesc->getName().c_str());
		}
		//fprintf(fpIDL, "> %s;\n\n", m_sName.c_str());
		fprintf(fpIDL, "> Vec_%s;\n\n",m_sName.c_str());
	}
	else//向量第二种形式，定长数组
	{
		fprintf(fpIDL, "\nsequence< ");
		if (m_type->m_iType < 0)//基础数据类型
		{
			GenerateFundmemtalTypeNameIDL(fpIDL, m_type->m_iType);
		}
		else
		{
			fprintf(fpIDL, "%s ", m_type->m_pTypeDesc->getName().c_str());
		}
		//fprintf(fpIDL, ",%d> %s;\n\n", length, m_sName.c_str());
		fprintf(fpIDL, ",%d>  Vec_%s;\n\n",length,m_sName.c_str());
	}
	fprintf(fpIDL, "\n};\n\n");
}
//Now_Gen_Test 没修改
// TODO
void TreeEntity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{

}
//Now_Gen_Test 修改
//结构体和联合（变）
void S_U_Entity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{
	if(Now_Gen_Test==true)
	{
		//fprintf(fpHeader, "typedef ");
		if (m_iType == T_STRUCT)
			fprintf(fpIDL, "struct ");
		else
			fprintf(fpIDL, "union ");
		//fprintf(fpHeader, "_%s \n{\n", m_sName.c_str());
		fprintf(fpIDL, "%s \n{\n", m_sName.c_str());
		vector<DataMember *>::iterator it;
		for (it = m_listMember.begin(); it != m_listMember.end(); ++it)
		{
			fprintf(fpIDL, "   ");	// Left margin = 3;
			DataMember *pMember = *it;
			if (pMember->m_pTypeIndex->m_iType < 0)
				// fundmental type as a data member
				GenerateFundmemtalTypeNameIDL(fpIDL, pMember->m_pTypeIndex->m_iType);
			else
				fprintf(fpIDL, "%s ", pMember->m_pTypeIndex->m_pTypeDesc->getName().c_str());

			fprintf(fpIDL, pMember->m_sName.c_str());
			fprintf(fpIDL, " ; \n");
		}
		//fprintf(fpHeader, "} %s ;\n\n", m_sName.c_str());

		fprintf(fpIDL, "   friend istream & operator>>(istream &stream, %s &temp)\n   {\n", m_sName.c_str());
		if (!m_listMember.empty())
		{
			fprintf(fpIDL, "      stream");
		}
		for (it = m_listMember.begin(); it != m_listMember.end(); ++it)
		{
			DataMember *pMember = *it;
			if (it == m_listMember.end() - 1)
			{
				fprintf(fpIDL, " >> temp.%s;\n", pMember->m_sName.c_str());
			}
			else
			{
				fprintf(fpIDL, " >> temp.%s", pMember->m_sName.c_str());
			}
		}
		fprintf(fpIDL, "      return stream;\n   }\n");

		//lian add <<运算符重载
		fprintf(fpIDL, "   friend ostream & operator<<(ostream &stream, const %s &temp)\n   {\n", m_sName.c_str());
		if (!m_listMember.empty())
		{
			fprintf(fpIDL, "      stream << \"(\"");
		}
		for (it = m_listMember.begin(); it != m_listMember.end(); ++it)
		{
			DataMember *pMember = *it;
			if (it == m_listMember.end() - 1)
			{
				fprintf(fpIDL, " << temp.%s << \")\";\n", pMember->m_sName.c_str());
			}
			else
			{
				fprintf(fpIDL, " << temp.%s << \",\"", pMember->m_sName.c_str());
			}
		}
		fprintf(fpIDL, "      return stream;\n   }\n");
		fprintf(fpIDL, "};\n\n");
	}
	else
	{
		fprintf(fpIDL, "struct %s\n{\n", m_sName.c_str());
		//fprintf(fpIDL, "public:\n");
		vector<DataMember *>::iterator it;
		for (it = m_listMember.begin(); it != m_listMember.end(); ++it)
		{
			fprintf(fpIDL, "\t");	// Left margin = 3;
			DataMember *pMember = *it;
			if (pMember->m_pTypeIndex->m_iType < 0)//基础数据类型
				GenerateFundmemtalTypeNameIDL(fpIDL, pMember->m_pTypeIndex->m_iType);
			else//复合数据类型
				fprintf(fpIDL, "%s ", pMember->m_pTypeIndex->m_pTypeDesc->getName().c_str());

			fprintf(fpIDL, pMember->m_sName.c_str());
			fprintf(fpIDL, "; \n");
		}
		//
		/*fprintf(fpIDL, "\tfriend class boost::serialization::access;\n");
		fprintf(fpIDL, "private:\n");
		fprintf(fpIDL, "\ttemplate<class Archive>\n");
		fprintf(fpIDL, "\tvoid serialize(Archive & ar, const unsigned int version)\n\t{\n");
		for (it = m_listMember.begin(); it != m_listMember.end(); ++it)
		{
			DataMember *pMember = *it;
			fprintf(fpIDL, "\t\tar & %s;\n", pMember->m_sName.c_str());
		}*/
		fprintf(fpIDL, "\n};\n\n");
	}
}

//Now_Gen_Test
//端口实体（陈新卫）
void PortEntity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{
	if(Now_Gen_Test==true)
	{
		fprintf(fpHeader, "class port%s\n", m_sName.c_str()); // Fundmental port ignored
		fprintf(fpHeader, "{\n");

		fprintf(fpHeader, "protected:\n");
		fprintf(fpHeader, "\t");
		if (m_DataDesc->m_iType < 0)
			GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
		else
			fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
		fprintf(fpHeader, "Buffer;\n");

		fprintf(fpHeader, "public:\n");
		fprintf(fpHeader, "\t");
		if (m_DataDesc->m_iType < 0)
			GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
		else
			fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
		fprintf(fpHeader, "*getPortBuffer();\n");

		fprintf(fpHeader, "};\n\n");

		// ************************************************

		if (m_DataDesc->m_iType < 0)
			GenerateFundmemtalTypeName(fpSource, m_DataDesc->m_iType);
		else
			fprintf(fpSource, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
		fprintf(fpSource, "*port%s::getPortBuffer()\n{\n\treturn &Buffer;\n}\n\n", m_sName.c_str());

	}
	else
	{
		//Publish 端口
		fprintf(fpHeader, "namespace ECOM{\n");
		fprintf(fpHeader, "namespace Port{\n");
		fprintf(fpHeader, "namespace %s{\n", m_sName.c_str());
		fprintf(fpHeader, "namespace Publish{\n"); // 
		fprintf(fpHeader, "class %s\n{\n", m_sName.c_str());  
		fprintf(fpHeader, "public:\n \t%sDataWriter *%s_writer;\n\t",(m_DataDesc->m_pTypeDesc)->getName().c_str(),(m_DataDesc->m_pTypeDesc)->getName().c_str());//private属性
		fprintf(fpHeader, "%s *instance;\n",(m_DataDesc->m_pTypeDesc)->getName().c_str());
		fprintf(fpHeader, "public:\n\t%s() {};\n};//END class %s\n}//END namespace Publish\n\n",m_sName.c_str(),m_sName.c_str());
		//Consume 端口
		fprintf(fpHeader, "namespace Consume{\n");
		fprintf(fpHeader, "class %s\n",m_sName.c_str());
		fprintf(fpHeader,"{\npublic:\n");
		fprintf(fpHeader,"\tvirtual void DataProcess(%s *pinstance) = 0;\n};\n\n",(m_DataDesc->m_pTypeDesc)->getName().c_str());
		fprintf(fpHeader,"class ThreadForConsumePort%s\n{\n",m_sName.c_str());
		fprintf(fpHeader,"public:\n");
		fprintf(fpHeader,"\tECOM::Port::%s::Consume::%s *pPort;\n",m_sName.c_str(),m_sName.c_str());
		fprintf(fpHeader,"\t%s instance;\n\t%s *pinstance;\n",(m_DataDesc->m_pTypeDesc)->getName().c_str(),(m_DataDesc->m_pTypeDesc)->getName().c_str());
		fprintf(fpHeader,"public:\n");
		fprintf(fpHeader,"\tThreadForConsumePort%s(){\n\t\tpinstance = &instance;\n\t}\n\n",m_sName.c_str());
		fprintf(fpHeader,"\tvoid invoke()\n\t{\n\t\tpPort->DataProcess(pinstance);\n\t}\n\n");
		fprintf(fpHeader,"};\n");
		//Consume 端口end
		fprintf(fpHeader,"}//END namespace Consume\n}//END namespace %s\n}//END Port\n}//END ECOM\n\n",m_sName.c_str());
	//	if (m_DataDesc->m_iType < 0)
	//	{
	//		GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
	//		fprintf(fpHeader, "Buffer;\n\t");
	//		GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
	//		fprintf(fpHeader, "*pBuffer;\n\t");
	//	}

	//	else
	//	{
	//		fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
	//		fprintf(fpHeader, "Buffer;\n\t");

	//		fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
	//		fprintf(fpHeader, "*pBuffer;\n\t");
	//	}
	//	fprintf(fpHeader, "void *pComponent;\n");
	//	fprintf(fpHeader, "\tint ComponentType;\n");


	//	//public
	//	fprintf(fpHeader, "public:\n\t");//public:
	//	fprintf(fpHeader, "%s(void *pComponent, int ComponentType, int portID)\n\t{\n\t", m_sName.c_str()); // 
	//	fprintf(fpHeader, "\tpBuffer = &Buffer;\n \
	//	this->pComponent = pComponent;\n \
	//	this->ComponentType = ComponentType;\n \
	//	this->portID = portID;\n \
	//}\n\n");//End constructor
	//	fprintf(fpHeader, "\t");
	//	if (m_DataDesc->m_iType < 0)
	//	{
	//		GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
	//		fprintf(fpHeader, "*getBuffer(){return pBuffer;}\n\n");
	//	}
	//	else
	//	{
	//		fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
	//		fprintf(fpHeader, "*getBuffer(){return pBuffer;}\n\n");
	//	}

	//	fprintf(fpHeader, "\tvoid Publish()\n\t{\n \
	//	std::ostringstream os; \n\
	//	boost::archive::text_oarchive oa(os);\n\
	//	oa << Buffer;		//序列化到一个ostringstream里面\n\
	//	std::string content = os.str();		//content保存了序列化后的数据。\n\
	//	int len = content.length();\n\
	//	char *buff = (char *)malloc(len+1);\n\
	//	strcpy(buff, content.c_str());\n\
	//	if (ComponentType == SERVICE)\n\
	//	{\n\
	//		BaseSer *pCom = (BaseSer *)pComponent;\n\
	//		pCom->PostDdsEvent(pCom->serAttrInfo->componentId, PORT_MSG, portID, len, buff);\n\
	//	}\n\
	//	else\n\
	//	{\n\
	//		BaseUi *pCom = (BaseUi *)pComponent;\n\
	//		pCom->PostDdsEvent(pCom->uiAttrInfo->pluginId, PORT_MSG, portID, len, buff);\n\
	//	}\n\
	//	\n\t}");

	//	fprintf(fpHeader, "\n\n}; // END  classs %s\n", m_sName.c_str());
	//	// end Publish
	//	fprintf(fpHeader, "} // END namespace Publish \n\n\n");
	//	//#endif

	//	//#if 0
	//	//->Consume:
	//	fprintf(fpHeader, "namespace Consume{\n"); // 
	//	fprintf(fpHeader, "class %s : public PortConsume\n{\n", m_sName.c_str()); // 
	//	fprintf(fpHeader, "public:\n\t");//private属性
	//	if (m_DataDesc->m_iType < 0)
	//	{
	//		GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
	//		fprintf(fpHeader, "Buffer;\n\t");
	//		GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
	//		fprintf(fpHeader, "*pBuffer;\n\t");
	//	}

	//	else
	//	{
	//		fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
	//		fprintf(fpHeader, "Buffer;\n\t");

	//		fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
	//		fprintf(fpHeader, "*pBuffer;\n\t");
	//	}
	//	fprintf(fpHeader, "\n\tvoid *pComponment;\n");
	//	fprintf(fpHeader, "\tint ComponentType;\n");
	//	fprintf(fpHeader, "\n");

	//	fprintf(fpHeader, "\tvirtual void DataProcess(");
	//	if (m_DataDesc->m_iType < 0)
	//	{
	//		GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
	//	}
	//	else
	//	{
	//		fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
	//	}
	//	fprintf(fpHeader, " *pBuffer) = 0 ;\n\n");

	//	fprintf(fpHeader, "public:\n\t");//public:

	//	fprintf(fpHeader, "%s(void *pComponment, int ComponentType)\n\t{\n\t", m_sName.c_str()); // 
	//	fprintf(fpHeader, "\tpBuffer = &Buffer;\n\t");
	//	fprintf(fpHeader, "\tthis->pComponment = pComponment;\n\t");
	//	fprintf(fpHeader, "\tthis->ComponentType = ComponentType;\n\t");
	//	fprintf(fpHeader, "}\n\n");//End constructor

	//	fprintf(fpHeader, "\t");
	//	if (m_DataDesc->m_iType < 0)
	//	{
	//		GenerateFundmemtalTypeName(fpHeader, m_DataDesc->m_iType);
	//		fprintf(fpHeader, "*getBuffer(){return pBuffer;}\n\n");
	//	}
	//	else
	//	{
	//		fprintf(fpHeader, "%s ", (m_DataDesc->m_pTypeDesc)->getName().c_str());
	//		fprintf(fpHeader, "*getBuffer(){return pBuffer;}\n\n");
	//	}

	//	fprintf(fpHeader, "\
	//void ReceiveMessage(char *buff) \n\
	//{  \n\
	//	std::istringstream is(buff); \n\
	//	boost::archive::text_iarchive ia(is); \n\
	//	ia >> Buffer; \n\
	//	DataProcess(&Buffer); \n\
	//} \n");
	//	fprintf(fpHeader, "}; // END  classs %s\n", m_sName.c_str());
	//	// end Consume
	//	fprintf(fpHeader, "} // END namespace Consume \n");


	//	//#endif

	//	fprintf(fpHeader, "} // END namespace %s \n", m_sName.c_str());
	//	fprintf(fpHeader, "} // END Port \n");
	//	fprintf(fpHeader, "} // END ECOM \n");
	}
}


// DDS
void OperationDesc::CodeGeneration(FILE *fpHeader, FILE *fpSource,FILE *fpIDL)
{
	if(true == Now_Gen_Test)
	{
		TypeIndex *pReturnType = getReturntype();
		if (pReturnType->m_iType < 0)
			// fpHeader to fpIDL
			GenerateFundmemtalTypeName(fpHeader, pReturnType->m_iType);
		else
			fprintf(fpHeader, "%s *", pReturnType->m_pTypeDesc->getName().c_str());
		fprintf(fpHeader, "%s(", m_sName.c_str());

		vector <OpParamDesc *>::iterator it;
		for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
		{
			if (it != m_listParam.begin())
				fprintf(fpHeader, ", ");
			if ((*it)->getDirection() == M_IN)
			{
				if ((*it)->getTypeIndex()->m_iType < 0)
					GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
				else
					fprintf(fpHeader, "const %s & ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpHeader, " %s", (*it)->getName().c_str());
			}
			else
			{
				if ((*it)->getTypeIndex()->m_iType < 0)
					GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
				else
					fprintf(fpHeader, "%s ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpHeader, "&%s", (*it)->getName().c_str());
			}
		}
		fprintf(fpHeader, ") = 0;\n");
	}
}

//priovide命名空间中接口类中函数C++代码
void OperationDesc::CodeGeneration(FILE *fpHeader)
{
	if(Now_Gen_Test == true)
	{
		TypeIndex *pReturnType = getReturntype();
		if (pReturnType->m_iType < 0)
			GenerateFundmemtalTypeName(fpHeader, pReturnType->m_iType);
		else
			fprintf(fpHeader, "%s *", pReturnType->m_pTypeDesc->getName().c_str());
		fprintf(fpHeader, "%s(", m_sName.c_str());

		vector <OpParamDesc *>::iterator it;
		for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
		{
			if (it != m_listParam.begin())
				fprintf(fpHeader, ", ");
			if ((*it)->getDirection() == M_IN)
			{
				if ((*it)->getTypeIndex()->m_iType < 0)
					GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
				else
					fprintf(fpHeader, "const %s & ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpHeader, "%s", (*it)->getName().c_str());
		}
		else
		{
			if ((*it)->getTypeIndex()->m_iType < 0)
				GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
			else
				fprintf(fpHeader, "%s ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpHeader, "&%s", (*it)->getName().c_str());
		}
	}
	fprintf(fpHeader, ");\n");
	}
	else
	{
		TypeIndex *pReturnType = getReturntype();
		if (pReturnType->m_iType < 0)
			GenerateFundmemtalTypeName(fpHeader, pReturnType->m_iType);
		else
			fprintf(fpHeader, "%s ", pReturnType->m_pTypeDesc->getName().c_str());
		fprintf(fpHeader, "%s(", m_sName.c_str());

		vector <OpParamDesc *>::iterator it;
		for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
		{
			if (it != m_listParam.begin())
				fprintf(fpHeader, ", ");
			if ((*it)->getDirection() == M_IN)
			{
				if ((*it)->getTypeIndex()->m_iType < 0)
				{
					fprintf(fpHeader, "const ");
					GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
				}
				else
					fprintf(fpHeader, "const %s & ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpHeader, "%s", (*it)->getName().c_str());
			}
			else
			{
				if ((*it)->getTypeIndex()->m_iType < 0)
					GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
				else
					fprintf(fpHeader, "%s ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpHeader, "&%s", (*it)->getName().c_str());
			}
		}
		fprintf(fpHeader, ")");
	}
}
// DDS 时用到
void OperationDesc::CodeGeneration2(FILE *fpHeader, const char *ComName, const char *InterfaceName)
{
	if(true == Now_Gen_Test)
	{
		TypeIndex *pReturnType = getReturntype();
		if (pReturnType->m_iType < 0)
			GenerateFundmemtalTypeName(fpHeader, pReturnType->m_iType);
		else
			fprintf(fpHeader, "%s *", pReturnType->m_pTypeDesc->getName().c_str());
		fprintf(fpHeader, " %s::%s::", ComName, InterfaceName);
		fprintf(fpHeader, "%s(", m_sName.c_str());

		vector <OpParamDesc *>::iterator it;
		for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
		{
			if (it != m_listParam.begin())
				fprintf(fpHeader, ", ");
			if ((*it)->getDirection() == M_IN)
			{
				if ((*it)->getTypeIndex()->m_iType < 0)
					GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
				else
					fprintf(fpHeader, "const %s & ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpHeader, "%s", (*it)->getName().c_str());
			}
			else
			{
				if ((*it)->getTypeIndex()->m_iType < 0)
					GenerateFundmemtalTypeName(fpHeader, (*it)->getTypeIndex()->m_iType);
				else
					fprintf(fpHeader, "%s ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpHeader, "&%s", (*it)->getName().c_str());
			}
		}
		fprintf(fpHeader, ")\n");
	}
}

//命名空间MethodsParams下接口函数的代码生成（师玉林）
void OperationDesc::OpMethParGeneration(FILE *fpIDL)
{
	//int OpParamCount = 1;
	fprintf(fpIDL, "struct %s_ret\n{\n", m_sName.c_str());
	//fprintf(fpHeader, "public:\n");
	TypeIndex *pReturnType = getReturntype();
	if (pReturnType->m_iType < 0)
	{
		if (pReturnType->m_iType == T_VOID)
		{
			VoidJudge = true;
		}
		fprintf(fpIDL, "\t");
		GenerateFundmemtalTypeNameIDL(fpIDL, pReturnType->m_iType);
		fprintf(fpIDL, "result;\n");
		VoidJudge = false;
	}
	else
	{
		fprintf(fpIDL, "\t");
		fprintf(fpIDL, "%s ", pReturnType->m_pTypeDesc->getName().c_str());
		fprintf(fpIDL, "result;\n");
	}
	vector <OpParamDesc *>::iterator it1;
	for (it1 = m_listParam.begin(); it1 != m_listParam.end(); ++it1)
	{
			if((*it1)->getDirection() != M_IN)
			{
				if ((*it1)->getTypeIndex()->m_iType < 0)
				{
					fprintf(fpIDL, "\t");
					GenerateFundmemtalTypeNameIDL(fpIDL, (*it1)->getTypeIndex()->m_iType);
					fprintf(fpIDL, "%s;\n", (*it1)->getName().c_str());
				}
				else
				{
					fprintf(fpIDL, "\t");
					fprintf(fpIDL, "%s", (*it1)->getTypeIndex()->m_pTypeDesc->getName().c_str());
					fprintf(fpIDL, " %s;\n", (*it1)->getName().c_str());
				}
			}
	}

	fprintf(fpIDL,"};\n\n");
//-------------------------------DJC modified-----------------------------------------
	fprintf(fpIDL, "struct %s_params\n{\n", m_sName.c_str());
//-------------------------------DJC modified-----------------------------------------
	vector <OpParamDesc *>::iterator it;
	for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
	{
		if ((*it)->getTypeIndex()->m_iType < 0)
		{
			fprintf(fpIDL, "\t");
			GenerateFundmemtalTypeNameIDL(fpIDL, (*it)->getTypeIndex()->m_iType);
			fprintf(fpIDL, "%s;\n", (*it)->getName().c_str());
		}
		else
		{
			fprintf(fpIDL, "\t");
			fprintf(fpIDL, "%s", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpIDL, " %s;\n", (*it)->getName().c_str());
		}
	}
	fprintf(fpIDL, "};\n\n");
	/*fprintf(fpHeader, "\tfriend class boost::serialization::access;\n");
	fprintf(fpHeader, "private:\n\t");
	fprintf(fpHeader, "template<class Archive>\n\t");
	fprintf(fpHeader, "void serialize(Archive & ar, const unsigned int version)\n\t{\n\t\t");
	fprintf(fpHeader, "ar & ret;\n");
	for (int Count = 1; Count <= m_listParam.size(); ++Count)
	{
		fprintf(fpHeader, "\t\tar & Param%d;\n", Count);
	}
	fprintf(fpHeader, "\t}\n");
	fprintf(fpHeader, "};\n");*/
}
//接口下命名空间Prioide下Methods命名空间C++代码（师玉林）
void OperationDesc::OpProvideMethodsGeneration(FILE *fpHeader,const char *InterfaceName)
{
	fprintf(fpHeader, "class %s : public ECOM::MethodProvided\n{\n", m_sName.c_str());
	fprintf(fpHeader, "private:\n\t");
	fprintf(fpHeader, "int methodID;\n\t");
	fprintf(fpHeader, "ECOM::Interface::%s::Provide::%s *pInterface;\n", InterfaceName, InterfaceName);
	fprintf(fpHeader, "public:\n\t");
	fprintf(fpHeader, "ECOM::Interface::%s::MethodsParams::%s parameters;\n", InterfaceName, m_sName.c_str());
	fprintf(fpHeader, "public:\n\t");
	fprintf(fpHeader, "%s(int methodID, ECOM::Interface::%s::Provide::%s *pInterface)\n\t", m_sName.c_str(), InterfaceName, InterfaceName);
	fprintf(fpHeader, "{\n\t");
	fprintf(fpHeader, "\tthis->methodID = methodID;\n\t");
	fprintf(fpHeader, "\tthis->pInterface = pInterface;\n\t");
	fprintf(fpHeader, "}\n");
	fprintf(fpHeader, "public:\n\t");
	fprintf(fpHeader, "void Call(int CallerComID, int CallerInterfaceID, std::string info);\n");
	fprintf(fpHeader, "};\n");
}
//provide下Methods命名空间下的每个操作类中Call函数
void OperationDesc::OpProvideMethodsCallOp(FILE *fpSource, const string InterfaceName)
{
	fprintf(fpSource, "void ECOM::Interface::%s::Provide::Methods::%s::Call(int CallerComID, int CallerInterfaceID, std::string info)\n",InterfaceName.c_str(),m_sName.c_str());
	fprintf(fpSource, "{\n\tstd::istringstream iss(info);\n");
	fprintf(fpSource, "\tboost::archive::text_iarchive ia(iss);\n");
	fprintf(fpSource, "\tia >> parameters;\n\n");

	//eg:	parameters.ret = pInterface->Op1(parameters.Param1); 
	int OpParamCount;
	if (getReturntype()->m_iType == T_VOID)
	{
		OpParamCount = 1;
		fprintf(fpSource, "\tpInterface->%s(", m_sName.c_str());
		while (OpParamCount <= m_listParam.size())
		{
			if (OpParamCount != 1)
			{
				fprintf(fpSource, ", ");
			}
			fprintf(fpSource, "parameters.Param%d", OpParamCount);
			OpParamCount++;
		}
		fprintf(fpSource, ");\n\n");
	}
	else
	{
		OpParamCount = 1;
		fprintf(fpSource, "\tparameters.ret = pInterface->%s(", m_sName.c_str());
		while (OpParamCount <= m_listParam.size())
		{
			if (OpParamCount != 1)
			{
				fprintf(fpSource, ", ");
			}
			fprintf(fpSource, "parameters.Param%d", OpParamCount);
			OpParamCount++;
		}
		fprintf(fpSource, ");\n\n");
	}

	fprintf(fpSource, "\tstd::ostringstream oss;\n");
	fprintf(fpSource, "\tboost::archive::text_oarchive oa(oss);\n");
	fprintf(fpSource, "\toa << parameters;\n");
	fprintf(fpSource, "\tstd::string content;\n");
	fprintf(fpSource, "\tcontent = oss.str();\n\n");
	fprintf(fpSource, "\tInterfaceSerialize intfSerial;\n");
	fprintf(fpSource, "\tintfSerial.CallerInterfaceID = CallerInterfaceID;\n");
	fprintf(fpSource, "\tintfSerial.CalleeMethodID = this->methodID;\n");
	fprintf(fpSource, "\tintfSerial.Parameters = content;\n\n");
	fprintf(fpSource, "\tstd::ostringstream oss2;\n");
	fprintf(fpSource, "\tboost::archive::text_oarchive oa2(oss2);\n");
	fprintf(fpSource, "\toa2 << intfSerial;\n\n");
	fprintf(fpSource, "\tcontent = oss2.str();\n\n");
	fprintf(fpSource, "\tint len = content.length();\n");
	fprintf(fpSource, "\tchar *buff = (char *)malloc(len + 1);\n");
	fprintf(fpSource, "\tstrcpy(buff, content.c_str());\n\n");
	//fprintf(fpSource, "\tpInterface->pComponent->SendMsgEvent(pInterface->pComponent->serAttrInfo->ComponentID, INTF_RET_MSG, CallerComID, len, buff);\n}\n\n");
	fprintf(fpSource, "\tif (pInterface->ComponentType == SERVICE)\n");
	fprintf(fpSource, "\t{\n\t\tBaseSer *pCom = (BaseSer *)(pInterface->pComponent);\n");
	fprintf(fpSource, "\t\tpCom->PostDdsEvent(pCom->serAttrInfo->componentId, INTF_RET_MSG, CallerComID, len, buff);\n\t}\n");
	fprintf(fpSource, "\telse\n\t{\n\t\tBaseUi *pCom = (BaseUi *)(pInterface->pComponent);\n");
	fprintf(fpSource, "\t\tpCom->PostDdsEvent(pCom->uiAttrInfo->pluginId, INTF_RET_MSG, CallerComID, len, buff);\n\t}\n}\n\n");




}
// 递归查找用户自定义类型中的Char*类型，并使用拷贝内存的赋值方式
void CharSeq_copy(TypeIndex* it,string &output,FILE *fpSource)
{
	if (it->m_iType == T_STRUCT||it->m_iType == T_UNION)
	{
		CDLEntity *entity = it->m_pTypeDesc;
		S_U_Entity *s_u_entity = (S_U_Entity*)entity;
		vector <DataMember *> memberlist = s_u_entity->get_listmember();
		vector <DataMember*>::iterator mem;
		for (mem = memberlist.begin();mem != memberlist.end();++mem)
		{
			if ((*mem)->m_pTypeIndex->m_iType == T_STRING)
			{
				string temp = output;
				temp += (*mem)->m_sName;
				fprintf(fpSource,"\trequest.data().%s = DDS_String_dup(%s);\n",temp.c_str(),temp.c_str());
			}
			else if(!((*mem)->m_pTypeIndex->m_iType < 0))
			{
				output += ".";
				output += (*mem)->m_sName;
				CharSeq_copy((*mem)->m_pTypeIndex,output,fpSource);
			}
		}
	}
}
//require下接口类的每个函数的实现Cpp
void OperationDesc::OpRequireOperationCpp(FILE *fpSource, const string ComponentName, const string ComInterfaceName,const string MethodName)
{
	TypeIndex *pReturnType = getReturntype();
	if (pReturnType->m_iType < 0)
		GenerateFundmemtalTypeName(fpSource, pReturnType->m_iType);
	else
		fprintf(fpSource, "%s ", pReturnType->m_pTypeDesc->getName().c_str());
	fprintf(fpSource, "ECOM::Components::%s::%s(", ComInterfaceName.c_str(), m_sName.c_str());

	vector <OpParamDesc *>::iterator it;
	for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
	{
		if (it != m_listParam.begin())
			fprintf(fpSource, ", ");
		if ((*it)->getDirection() == M_IN)
		{
			if ((*it)->getTypeIndex()->m_iType < 0)
			{
				fprintf(fpSource, "const ");
				GenerateFundmemtalTypeName(fpSource, (*it)->getTypeIndex()->m_iType);
			}
			else
				fprintf(fpSource, "const %s & ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpSource, "%s", (*it)->getName().c_str());
		}
		else
		{
			if ((*it)->getTypeIndex()->m_iType < 0)
				GenerateFundmemtalTypeName(fpSource, (*it)->getTypeIndex()->m_iType);
			else
				fprintf(fpSource, "%s ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpSource, "&%s", (*it)->getName().c_str());
		}
	}
	fprintf(fpSource, ")\n");
	fprintf(fpSource, "{\n");
	//BY CJ
	fprintf(fpSource,"\tconnext::WriteSample<%s_params> request;\n",MethodName.c_str());
	//初始化request
	for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
	{
		if ((*it)->getTypeIndex()->m_iType != T_STRUCT&&(*it)->getTypeIndex()->m_iType != T_UNION)
		{
			//如果是Char*类型，使用sprintf赋值方式
			if((*it)->getTypeIndex()->m_iType == T_STRING)
			{
				fprintf(fpSource,"\tsprintf(request.data().%s,%s);\n",(*it)->getName().c_str(),(*it)->getName().c_str());
			}
			else
			{
				fprintf(fpSource,"\trequest.data().%s = %s;\n",(*it)->getName().c_str(),(*it)->getName().c_str());
			}

		}
		else
		{
			string strpos = (*it)->getName() + ".";
			CharSeq_copy((*it)->getTypeIndex(),strpos,fpSource);
			//fprintf(fpSource,"\trequest.data().%s = %s;\n",it->getName().c_str(),it->getName().c_str());

		}

	}
	fprintf(fpSource,"\t");
	if (pReturnType->m_iType < 0)
		GenerateFundmemtalTypeName(fpSource, pReturnType->m_iType);
	else
		fprintf(fpSource, "%s ", pReturnType->m_pTypeDesc->getName().c_str());
	fprintf(fpSource,"result;\n");
	fprintf(fpSource,"\tthis->requester->send_request(request);\n\n");
	fprintf(fpSource,"\t/*Receive replies */\n");
	fprintf(fpSource,"\tconst DDS::Duration_t MAX_WAIT = {4,0};\n");
	fprintf(fpSource,"\tconnext::Sample<%s_ret> reply;\n",MethodName.c_str());
	fprintf(fpSource,"\tbool received = this->requester->receive_reply(reply,MAX_WAIT);\n");
	fprintf(fpSource,"\tif (received) {\n");
	fprintf(fpSource,"\t\tif(reply.info().valid_data) {\n");
	//fprintf(fpSource,"\t\t\tstd::cout<<\"Received reply: \"<< reply.data().result <<std::endl;\n");
	fprintf(fpSource,"\t\t\tresult = reply.data().result;\n");
	for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
	{
		if ((*it)->getDirection() != M_IN)
		{
			fprintf(fpSource, "\t\t\t%s = reply.data().%s;\n",(*it)->getName().c_str(),(*it)->getName().c_str());
		}
	}
	fprintf(fpSource,"\t\t} else {\n");
	//fprintf(fpSource,"\t\t\tstd::cout<<\"Received invalid reply\"<<std::endl;\n");
	fprintf(fpSource,"\t\t}\n");
	fprintf(fpSource,"\t} else {\n");
	fprintf(fpSource,"\t\tstd::cout <<\"Reply not received\"<< std::endl;\n");
	fprintf(fpSource,"\t}\n");
	fprintf(fpSource,"\treturn result;\n\n");
	fprintf(fpSource,"}\n\n");
}
//构件cpp文件中provide接口中操作的C++代码
void OperationDesc::OpComProvideOpCpp(FILE *fpSource, const string ComponentName, const string ComInterfaceName)
{
	TypeIndex *pReturnType = getReturntype();
	if (pReturnType->m_iType < 0)
		GenerateFundmemtalTypeName(fpSource, pReturnType->m_iType);
	else
		fprintf(fpSource, "%s ", pReturnType->m_pTypeDesc->getName().c_str());
	fprintf(fpSource, "ECOM::Components::%s::%s(", ComInterfaceName.c_str(), m_sName.c_str());
	
	vector <OpParamDesc *>::iterator it;
	for (it = m_listParam.begin(); it != m_listParam.end(); ++it)
	{
		if (it != m_listParam.begin())
			fprintf(fpSource, ", ");
		if ((*it)->getDirection() == M_IN)
		{
			if ((*it)->getTypeIndex()->m_iType < 0)
			{
				fprintf(fpSource, "const ");
				GenerateFundmemtalTypeName(fpSource, (*it)->getTypeIndex()->m_iType);
			}
			else
				fprintf(fpSource, "const %s & ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpSource, "%s", (*it)->getName().c_str());
		}
		else
		{
			if ((*it)->getTypeIndex()->m_iType < 0)
				GenerateFundmemtalTypeName(fpSource, (*it)->getTypeIndex()->m_iType);
			else
				fprintf(fpSource, "%s ", (*it)->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpSource, "&%s", (*it)->getName().c_str());
		}
	}
	fprintf(fpSource, ")\n");
	fprintf(fpSource, "{\n");
	fprintf(fpSource, "\tif (pComponent->status==ECOM::Base::Activated)");
	fprintf(fpSource, "\t{\n");
	fprintf(fpSource, "\t\t//TODO : Add your business logic here\n\n\n");
	fprintf(fpSource, "\t}\n");
	if (pReturnType->m_iType == T_VOID)
	{
		fprintf(fpSource, "\n}\n\n");
	}
	else
	{
		fprintf(fpSource, "\treturn 0;\n}\n\n");
	}
}
//为on_request_available中的函数参数赋值 董俊晨 2018/07/17
void OperationDesc::onRequestOpParamCpp(FILE *fpSource,const string MethodName)
{
	//vector <OpParamDesc *>::iterator par;
	//for (par = m_listParam.begin(); par != m_listParam.end(); ++par)
	//{
	//	OpParamDesc *pPar = *par;
	//	if (pPar->getTypeIndex()->m_iType < 0)
	//	{
	//		fprintf(fpSource, "\t\t\t");
	//		GenerateFundmemtalTypeName(fpSource, pPar->getTypeIndex()->m_iType);
	//		fprintf(fpSource, "%s = it->data().%s;\n", pPar->getName().c_str(),pPar->getName().c_str());
	//	}
	//	else
	//	{
	//		fprintf(fpSource, "\t\t\t");
	//		fprintf(fpSource, "%s", pPar->getTypeIndex()->m_pTypeDesc->getName().c_str());
	//		fprintf(fpSource, " %s = it->data().%s;\n", pPar->getName().c_str(),pPar->getName().c_str());
	//	}

	//}
	fprintf(fpSource,"\t\t\t");
	TypeIndex *pReturnType = getReturntype();
	if (pReturnType->m_iType < 0)
		GenerateFundmemtalTypeName(fpSource, pReturnType->m_iType);
	else
		fprintf(fpSource, "%s ", pReturnType->m_pTypeDesc->getName().c_str());

	fprintf(fpSource,"result = this->pInterface->%s(",m_sName.c_str());
	vector <OpParamDesc *>::iterator op_param;
	for (op_param = m_listParam.begin(); op_param != m_listParam.end(); ++op_param)
	{
		if (op_param != m_listParam.begin())
			fprintf(fpSource, ", ");
		fprintf(fpSource, "it->data().%s", (*op_param)->getName().c_str());

	}
	fprintf(fpSource, ");\n\n");
	//发送回复
	fprintf(fpSource,"\t\t\t/*Send reply indicating error */\n");
	fprintf(fpSource,"\t\t\tconnext::WriteSample<%s_ret> reply;\n",MethodName.c_str());
	fprintf(fpSource,"\t\t\treply.data().result = result;\n");
	for (op_param = m_listParam.begin(); op_param != m_listParam.end(); ++op_param)
	{
		if ((*op_param)->getDirection() != M_IN)
		{

			fprintf(fpSource, "\t\t\treply.data().%s = it->data().%s;\n", (*op_param)->getName().c_str(),(*op_param)->getName().c_str());
		}
	}
	fprintf(fpSource,"\t\t\treplier.send_reply(reply, it->identity());\n");
	//fprintf(fpSource,"\t\t\tstd::cout << \"Transformer DONE\"<<std::endl;");
	fprintf(fpSource,"\t\t}\n\t}\n");
}
//provide命名空间下cpp文件
void InterfaceEntity::ProvideGeneration(FILE *fpSource)
{
	//provide命名空间下接口类构造函数
	fprintf(fpSource, "ECOM::Interface::%s::Provide::%s::%s(void *pComponent, int ComponentType, int interfaceID)\n", m_sName.c_str(), m_sName.c_str(), m_sName.c_str());
	fprintf(fpSource, "\t: ECOM::InterfaceProvided(pComponent, ComponentType, interfaceID)\n{\n");
	vector <OperationDesc *>::iterator it;
	int OpCount = 1;
	for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
	{
		OperationDesc *pOP = *it;
		fprintf(fpSource, "\tMethodList.push_back(new ECOM::Interface::%s::Provide::Methods::%s(%d, this));\n", m_sName.c_str(), pOP->getName().c_str(), OpCount);
		OpCount++;
	}
	fprintf(fpSource, "}\n\n");

	//provide下Methods命名空间下的每个操作类中Call函数
	for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
	{
		OperationDesc *pOP = *it;
		pOP->OpProvideMethodsCallOp(fpSource, m_sName);
		
	}

	//provide命名空间下接口类析构函数
	fprintf(fpSource, "ECOM::Interface::%s::Provide::%s::~%s()\n", m_sName.c_str(), m_sName.c_str(), m_sName.c_str());
	fprintf(fpSource, "{\n\tstd::vector<ECOM::MethodProvided *>::iterator it;\n");
	fprintf(fpSource, "\tfor (it = MethodList.begin(); it != MethodList.end(); ++it)\n");
	fprintf(fpSource, "\t\tdelete (*it);\n}\n\n");

	//provide命名空间下接口类中MethodRoute函数
	fprintf(fpSource, "void ECOM::Interface::%s::Provide::%s::MethodRoute(int CallerComID, char *info)\n", m_sName.c_str(), m_sName.c_str());
	fprintf(fpSource, "{\n\tstd::string content(info);\n");
	fprintf(fpSource, "\tstd::istringstream iss(content);\n");
	fprintf(fpSource, "\tboost::archive::text_iarchive ia(iss);\n");
	fprintf(fpSource, "\tInterfaceSerialize interfaceSerialize;\n");
	fprintf(fpSource, "\tia >> interfaceSerialize;\n");
	fprintf(fpSource, "\tint CallerInterfaceID, CalleeMethodID;\n");
	fprintf(fpSource, "\tCallerInterfaceID = interfaceSerialize.CallerInterfaceID;\n");
	fprintf(fpSource, "\tCalleeMethodID = interfaceSerialize.CalleeMethodID;\n");
	fprintf(fpSource, "\tcontent = interfaceSerialize.Parameters;\n\n");
	fprintf(fpSource, "\tif (CalleeMethodID > MethodList.size() || CalleeMethodID < 1)\n\t{\n");
	fprintf(fpSource, "\t\tstd::cout << \"Internal Error .... \" << std::endl;\n");
	fprintf(fpSource, "\t\treturn;\n\t}\n\n");
	fprintf(fpSource, "\tMethodList[CalleeMethodID-1]->Call(CallerComID, CallerInterfaceID, content);\n}\n\n");




}
//接口实体
void InterfaceEntity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{
	if(Now_Gen_Test == true)
	{
		fprintf(fpHeader, "class %s ,\n public Interface\n{\npublic :\n", m_sName.c_str());
		vector <OperationDesc *>::iterator it;
		for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
		{
			fprintf(fpHeader, "\tvirtual ");
			OperationDesc *pOP = *it;
			pOP->CodeGeneration(fpHeader, fpSource, fpIDL);
		}

		fprintf(fpHeader, "\n};\n\n");
	}
	else
	{
		/*fprintf(fpHeader, "class %s : public Interface\n{\npublic :\n", m_sName.c_str());
		vector <OperationDesc *>::iterator it;
		for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
		{
			fprintf(fpHeader, "\tvirtual ");
			OperationDesc *pOP = *it;
			pOP->CodeGeneration(fpHeader, fpSource);
		}

		fprintf(fpHeader, "\n};\n\n");*/
		fprintf(fpHeader, "namespace ECOM{\n");
		fprintf(fpHeader, "namespace Interface{\n");
		fprintf(fpHeader, "namespace %s{\n", m_sName.c_str());
//----------------------------------------------DJC modified-----------------------------------
		//MethodsParams命名空间中的C++代码
		//fprintf(fpIDL, "namespace MethodsParams{\n");
		vector <OperationDesc *>::iterator it;
		for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
		{
			OperationDesc *pOP = *it;
			pOP->OpMethParGeneration(fpIDL);//接口下命名空间MethodsParams中的函数代码生成
		}
		//fprintf(fpIDL, "}\n\n");//MethodsParams命名空间   end

//----------------------------------------------DJC modified-----------------------------------
		//Provide命名空间中C++代码

		fprintf(fpHeader, "namespace Provide{\n");
		fprintf(fpHeader, "class %s{\n", m_sName.c_str());//接口类全局声明

		//Provide命名空间下Methods命名空间C++代码
		fprintf(fpHeader, "public:\n\tconnext::Replier<%s_params,%s_ret> *replier;\n\n",m_listOperation.front()->getName().c_str(),m_listOperation.front()->getName().c_str());

		//fprintf(fpHeader, "namespace Methods{\n");

		//for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
		//{
		//	OperationDesc *pOP = *it;
		//	pOP->OpProvideMethodsGeneration(fpHeader,m_sName.c_str());
		//}
		//fprintf(fpHeader, "}\n\n");//Provide命名空间下Methods命名空间   end 

		////Provide命名空间下接口类的C++代码
		//fprintf(fpHeader, "class %s : public ECOM::InterfaceProvided\n{\n", m_sName.c_str());
		//fprintf(fpHeader, "public:\n");
		//fprintf(fpHeader, "\t%s(void *pComponent, int ComponentType, int interfaceID);\n", m_sName.c_str());
		//fprintf(fpHeader, "\t~%s();\n\n", m_sName.c_str());
		//virtual函数C++代码
		for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
		{
			fprintf(fpHeader, "\tvirtual ");
			OperationDesc *pOP = *it;
			pOP->CodeGeneration(fpHeader);
			fprintf(fpHeader, " = 0;\n");
		}
		fprintf(fpHeader, "\n};\n}//END namespace Provide\n\n");
		//fprintf(fpHeader, "\n\tvoid MethodRoute(int CallerComID, char *info);\n");
		//fprintf(fpHeader, "private:\n\tstd::vector<ECOM::MethodProvided *> MethodList;\n");
		//fprintf(fpHeader, "};\n}\n\n");//provide命名空间


//CPP文件的写入
		//provide命名空间下cpp文件的写入
		//ProvideGeneration(fpSource);



		//require命名空间开始
		fprintf(fpHeader, "namespace Require {\n");
		fprintf(fpHeader, "class %s {\npublic:\n\tconnext::Requester<%s_params,%s_ret> *requester;\n\n",m_sName.c_str(),m_listOperation.front()->getName().c_str(),m_listOperation.front()->getName().c_str());
		//fprintf(fpHeader, "\t%s(void *pComponent, int ComponentType, int interfaceID, int CalleeComID, int CalleeInterfaceID)\n", m_sName.c_str());
		//fprintf(fpHeader, "\t\t: ECOM::InterfaceRequired(pComponent, ComponentType, interfaceID, CalleeComID, CalleeInterfaceID)\n\t{ }\n\n");
		for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
		{
			fprintf(fpHeader, "\tvirtual ");
			OperationDesc *pOP = *it;
			pOP->CodeGeneration(fpHeader);
			fprintf(fpHeader, " = 0;\n");
		}
		fprintf(fpHeader, "};\n\n}//END namespace Require\n}//END namespace TransformParam\n}//END interface\n}//END ECOM\n\n");//接口头文件中C++代码  end



		//require命名空间下CPP文件写入
		//int methodId = 1;//操作个数，主要是为了数组的取值
		//for (it = m_listOperation.begin(); it != m_listOperation.end(); ++it)
		//{
		//	OperationDesc *pOP = *it;
		//	pOP->OpRequireOperationCpp(fpSource, m_sName, methodId);
		//	methodId++;
		//}
	}
}
//构件开始写C++入口
void CDLFile::GenerateComponentEntity(string ComRootDir)
{
	string ComDir;
	string ComIncludeDir;
	string ComSourcesDir;

	vector<CDLEntity *>::iterator it;
	for (it = m_listCDLEntity.begin(); it != m_listCDLEntity.end(); ++it)
	{
		CDLEntity *pEntity = *it;
		int EntityType = pEntity->getType();
		if (EntityType == T_COMPONENT)
		{
			string ComName = (*it)->getName();
			ComDir = ComRootDir;
			ComDir.append("/").append(ComName.c_str());
			mkdir(ComDir.c_str());

			ComIncludeDir = ComDir;
			ComIncludeDir.append("/").append("include");
			mkdir(ComIncludeDir.c_str());
			ComSourcesDir = ComDir;
			ComSourcesDir.append("/").append("sources");
			mkdir(ComSourcesDir.c_str());

			string HeaderFile = ComIncludeDir;
			HeaderFile.append("/").append(ComName).append(".h");

			string SourceFile = ComSourcesDir;
			SourceFile.append("/").append(ComName).append(".cpp");

			FILE *fpHeader = fopen(HeaderFile.c_str(), "w");
			FILE *fpSource = fopen(SourceFile.c_str(), "w");
			FILE *fpIDL;

			//构件头文件的写入
					//-->
			if(true == Now_Gen_Test)
			{
				pEntity->CodeGeneration(fpHeader, fpSource, fpIDL);

				fprintf(fpSource, "DWORD %s::WorkingThread(void \*arg)\n", ComName.c_str());
				fprintf(fpSource, "{\n");
				fprintf(fpSource, "\t%s \*pObj = (%s \*)arg;\n", ComName.c_str(), ComName.c_str());
				fprintf(fpSource, "\treturn pObj->Task(pObj);\n");
				fprintf(fpSource, "}\n\n");

				fprintf(fpSource, "DWORD %s::Task(%s \*pComponent)\n", ComName.c_str(), ComName.c_str());
				fprintf(fpSource, "{\n\tBOOL bValidity = 0;\n\tBOOL bRefresh = 0;\n\n\twhile (1)\n\t{\n");
				vector <ComponentPortDesc *>::iterator it2;
				ComponentEntity *pCom = (ComponentEntity *)pEntity;
				for (it2 = pCom->m_listPort.begin(); it2 != pCom->m_listPort.end(); ++it2)
				{
					ComponentPortDesc * PortDesc = (*it2);
					if (PortDesc->getPubSub() == M_CONSUME)
					{
						string PortName = PortDesc->getName();
						fprintf(fpSource, "\t\tif (p%s != NULL)\n", PortName.c_str());
						fprintf(fpSource, "\t\t\tif (p%s->pSubscriber->DataReader(&(p%s->Buffer),sizeof(%s),50000,&bValidity,&bRefresh))\n",
							PortName.c_str(), PortName.c_str(), PortDesc->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
						fprintf(fpSource, "\t\t\t{\n");
						fprintf(fpSource, "\t\t\t\tif (bRefresh)\n\t\t\t\t{\n");
						fprintf(fpSource, "\t\t\t\t\tp%s->DataProcess(p%s, pComponent);\n", PortName.c_str(), PortName.c_str());
						fprintf(fpSource, "\t\t\t\t}\n\t\t\t}\n");
					}
				}
				fprintf(fpSource, "\t\tSleep(300);\n\t}\n\treturn 0;\n}\n\n");
			}
			else
			{
				ComponentEntity *pCom = (ComponentEntity *)pEntity;
				if(pCom->get_UI_ServiceFlag() == M_UI)
				{
					fprintf(fpHeader,"#include <BaseUi.h>\n");
					fprintf(fpHeader,"#include \"ui_%s.h\"\n",ComName.c_str());
				}
				else if(pCom->get_UI_ServiceFlag() == M_SERVICE)
				{
					fprintf(fpHeader,"#include \"BaseSer.h\"\n");
				}
				fprintf(fpHeader, "#include \"../../../include/%s.h\"\n"
								  "#include <sstream>\n"
								  "#include <boost/thread.hpp>\n", CDLName.c_str());

				if(pCom->get_UI_ServiceFlag() == M_SERVICE)
				{
					fprintf(fpSource, "#define WIN32_DLL\n\n");
				}
				else if(pCom->get_UI_ServiceFlag() == M_UI)
				{
					fprintf(fpSource, "#define PLUGIN_LIB\n\n");
				}
				fprintf(fpSource, "#include \"../include/%s.h\"\n", ComName.c_str());
				fprintf(fpSource, "#include <stdlib.h>\n\n");
				vector<ComponentInterfaceDesc* >::iterator inf;
				vector<ComponentInterfaceDesc*> infs(pCom->GetInterfaceList());
				for (inf = infs.begin();inf != infs.end(); inf++)
				{
					fprintf(fpSource,"#include \"../include/%s.h\"\n",(*inf)->getName().c_str());
				}
				vector<ComponentPortDesc* >::iterator port;
				for (port = pCom->m_listPort.begin(); port != pCom->m_listPort.end(); port++)
				{
					fprintf(fpSource,"#include \"../include/%s.h\"\n",(*port)->getName().c_str());
				}
				pCom->ComHeaderGeneration(fpHeader);
				pCom->ComSourceGeneration(fpSource);
			}
			fclose(fpHeader);
			fclose(fpSource);

		}
	}


}

//dds的即debug
void ComponentEntity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{
	fprintf(fpHeader, "#ifndef %s_HEADER\n", m_sName.c_str());
	fprintf(fpHeader, "#define %s_HEADER\n\n", m_sName.c_str());

	fprintf(fpHeader, "#include \"..\\\\..\\\\..\\\\include\\\\%s.h\"\n\n", CDLName.c_str());
	fprintf(fpHeader, "class %s : public Component\n{\n", m_sName.c_str());

	fprintf(fpSource, "#include \"..\\\\include\\\\%s.h\"\n", m_sName.c_str());
	fprintf(fpSource, "\nextern DDS \*pDDS;\n\n");
	fprintf(fpSource, "%s::%s(char \*InstName)\n{\n", m_sName.c_str(), m_sName.c_str());
	//
	// Header generation write to fpHeader
	// But Source file generation must use temp files as below:
	// fpSource for component's constructor, it is not a temp file
	// one for component deconstructor
	// one for component's global methods
	// one for each part's methods
	// so we must create 3 temp files : Destroy, ComMethds, PartMethods(this could be used in cycle)
	// all temp file put in RootDir
	string DestroyFile = RootDir + string("/temp1.txt");
	string ComMethods = RootDir + string("/temp2.txt");
	string PartMethods = RootDir + string("/temp3.txt");

	FILE *fpDestroy = fopen(DestroyFile.c_str(), "w");
	FILE *fpComMethod = fopen(ComMethods.c_str(), "w");
	FILE *fpPartMethod = fopen(PartMethods.c_str(), "w");

	fprintf(fpDestroy, "%s::~%s()\n{\n", m_sName.c_str(), m_sName.c_str());

	// Handle with eath part in the component here
	// Firstly, we handle with ports in the component
	vector <ComponentPortDesc *>::iterator it;
	for (it = m_listPort.begin(); it != m_listPort.end(); ++it)
	{
		ComponentPortDesc *pPort = (*it);
		int PubSub = pPort->getPubSub();
		if (PubSub == M_CONSUME)
		{  // It is CONSUME port or INPUT-PORT
			fprintf(fpHeader, "private:\n");
			fprintf(fpHeader, "\tclass %s : public port%s, PortConsume\n", pPort->getName().c_str(), pPort->getPortEntity()->getName().c_str());
			fprintf(fpHeader, "\t{\n");
			fprintf(fpHeader, "\tpublic:\n");
			fprintf(fpHeader, "\t\t%s();\n", pPort->getName().c_str());
			fprintf(fpHeader, "\t\t~%s();\n\n", pPort->getName().c_str());

			fprintf(fpHeader, "\t\tvoid DataProcess(port%s \*Data, %s \*pComponent);\n", pPort->getPortEntity()->getName().c_str(), m_sName.c_str());
			fprintf(fpHeader, "\t\tvoid ConnectTo(char \*PortInstName);\n");
			fprintf(fpHeader, "\t\tfriend class %s;\n", m_sName.c_str());
			fprintf(fpHeader, "\t};\n");
			fprintf(fpHeader, "\t%s \*p%s;\n", pPort->getName().c_str(), pPort->getName().c_str());

			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s *getPort_%s();\n\n", pPort->getName().c_str(), pPort->getName().c_str());
		}
		else // It is PROVIDE PORT
		{
			fprintf(fpHeader, "private:\n");
			fprintf(fpHeader, "\tclass %s : public port%s, PortPublish\n", pPort->getName().c_str(), pPort->getPortEntity()->getName().c_str());
			fprintf(fpHeader, "\t{\n");
			fprintf(fpHeader, "\tpublic:\n");
			fprintf(fpHeader, "\t\t%s();\n", pPort->getName().c_str());
			fprintf(fpHeader, "\t\t~%s();\n\n", pPort->getName().c_str());

			fprintf(fpHeader, "\t\tvoid Publish();\n");
			fprintf(fpHeader, "\t\tfriend class %s;\n", m_sName.c_str());
			fprintf(fpHeader, "\t};\n");
			fprintf(fpHeader, "\t%s \*p%s;\n", pPort->getName().c_str(), pPort->getName().c_str());

			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s *getPort_%s();\n\n", pPort->getName().c_str(), pPort->getName().c_str());
		}

		fprintf(fpDestroy, "\tdelete p%s;\n", pPort->getName().c_str());

		fprintf(fpComMethod, "%s::%s \*%s::getPort_%s()\n", m_sName.c_str(), pPort->getName().c_str(), m_sName.c_str(), pPort->getName().c_str());
		fprintf(fpComMethod, "{\n");
		fprintf(fpComMethod, "\treturn p%s;\n", pPort->getName().c_str());
		fprintf(fpComMethod, "}\n\n");

		if (PubSub == M_CONSUME)
		{
			fprintf(fpPartMethod, "%s::%s::%s()\n", m_sName.c_str(), pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tTopic[0] = '\\0';\n");
			fprintf(fpPartMethod, "\tpSubscriber = NULL;\n");
			fprintf(fpPartMethod, "}\n\n");

			fprintf(fpPartMethod, "%s::%s::~%s()\n", m_sName.c_str(), pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tif (pSubscriber != NULL)\n");
			fprintf(fpPartMethod, "\t\tpDDS->ReleaseSubscriber(pSubscriber);\n");
			fprintf(fpPartMethod, "}\n\n");

			fprintf(fpPartMethod, "void %s::%s::ConnectTo(char \*PortInstName)\n", m_sName.c_str(), pPort->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tstrcpy(Topic, PortInstName);\n");
			fprintf(fpPartMethod, "\tpSubscriber = pDDS->CreateQueuingSubscriber(Topic, sizeof(%s));\n", pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPartMethod, "}\n\n");

			fprintf(fpPartMethod, "void %s::%s::DataProcess(port%s \*Data, %s \*pComponent)\n", m_sName.c_str(),
				pPort->getName().c_str(), pPort->getPortEntity()->getName().c_str(), m_sName.c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\t%s \*pBuffer = Data->getPortBuffer();\n", pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPartMethod, "\t// TODO : Your code here for processing data received \n\n\n\n\n");
			fprintf(fpPartMethod, "}\n\n");
		}
		else	// For PUBLISH PORT
		{
			fprintf(fpPartMethod, "%s::%s::%s()\n", m_sName.c_str(), pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tTopic[0] = '\\0';\n");
			fprintf(fpPartMethod, "\tpPublisher = NULL;\n");
			fprintf(fpPartMethod, "}\n\n");

			fprintf(fpPartMethod, "%s::%s::~%s()\n", m_sName.c_str(), pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tif (pPublisher != NULL)\n");
			fprintf(fpPartMethod, "\t\tpDDS->ReleasePublisher(pPublisher);\n");
			fprintf(fpPartMethod, "}\n\n");

			fprintf(fpPartMethod, "void %s::%s::Publish()\n", m_sName.c_str(), pPort->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tpPublisher->DataWriter(&Buffer, sizeof(%s), INFINITE); \n",
				pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPartMethod, "}\n\n");
		}

		if (PubSub == M_CONSUME)
		{
			fprintf(fpSource, "\tp%s = new %s();\n\n", pPort->getName().c_str(), pPort->getName().c_str());
		}
		else
		{
			fprintf(fpSource, "\tstrcpy(this->InstName, InstName);\n");
			fprintf(fpSource, "\tp%s = new %s();\n", pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpSource, "\tstrcpy(p%s->Topic, InstName);\n", pPort->getName().c_str());
			fprintf(fpSource, "\tstrcat(p%s->Topic, \"_Data_%s\");\n", pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpSource, "\tp%s->pPublisher = pDDS->CreateQueuingPublisher(p%s->Topic, sizeof(%s));\n\n",
				pPort->getName().c_str(), pPort->getName().c_str(), pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
		}
	} // End of for-loop

	vector <ComponentInterfaceDesc *>::iterator it2;
	for (it2 = m_listInterface.begin(); it2 != m_listInterface.end(); ++it2)
	{
		ComponentInterfaceDesc *pIntf = (*it2);
		int Role = pIntf->getRole();
		if (Role == M_PROVIDE)
		{
			fprintf(fpHeader, "private:\n");
			fprintf(fpHeader, "\tclass %s : public %s\n", pIntf->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str());
			fprintf(fpHeader, "\t{\n");
			fprintf(fpHeader, "\tprivate:\n");
			fprintf(fpHeader, "\t\t%s \*pComponent;\n", m_sName.c_str());
			fprintf(fpHeader, "\tpublic:\n");
			fprintf(fpHeader, "\t\t%s(%s \*pObj);\n", pIntf->getName().c_str(), m_sName.c_str());

			InterfaceEntity *pIntfEntity = pIntf->getInterfaceEntity();
			vector <OperationDesc *>::iterator it3;
			for (it3 = pIntfEntity->m_listOperation.begin(); it3 != pIntfEntity->m_listOperation.end(); ++it3)
			{
				OperationDesc *OPdesc = (*it3);
				fprintf(fpHeader, "\t\t");
				OPdesc->CodeGeneration(fpHeader);
			}
			fprintf(fpHeader, "\tfriend class %s;\n", m_sName.c_str());
			fprintf(fpHeader, "};\n\n");
			fprintf(fpHeader, "\t%s \*p%s;\n", pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s \*getInterface_%s();\n\n", pIntf->getName().c_str(), pIntf->getName().c_str());
		}
		else
		{
			fprintf(fpHeader, "private:\n");
			fprintf(fpHeader, "\tclass %s\n", pIntf->getName().c_str());
			fprintf(fpHeader, "\t{\n\tprivate:\n");
			fprintf(fpHeader, "\t\t%s \*p%s;\n", pIntf->getInterfaceEntity()->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "\tpublic:\n");
			fprintf(fpHeader, "\t\t%s();\n", pIntf->getName().c_str());
			fprintf(fpHeader, "\t\t~%s();\n\n", pIntf->getName().c_str());
			fprintf(fpHeader, "\t\tvoid ConnectTo(%s \*pComponentInterface);\n", pIntf->getInterfaceEntity()->getName().c_str());
			fprintf(fpHeader, "\t\tfriend class %s;\n", m_sName.c_str());
			fprintf(fpHeader, "\t};\n");
			fprintf(fpHeader, "\t%s \*p%s;\n\n", pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "private:\n");
			fprintf(fpHeader, "\t%s \*get%s();\n\n", pIntf->getInterfaceEntity()->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s \*getInterface_%s();\n\n", pIntf->getName().c_str(), pIntf->getName().c_str());
		}

		if (Role == M_REQUIRE)
		{
			fprintf(fpSource, "\tp%s = new %s();\n\n", pIntf->getName().c_str(), pIntf->getName().c_str());
		}
		else
		{
			fprintf(fpSource, "\tp%s = new %s(this);\n\n", pIntf->getName().c_str(), pIntf->getName().c_str());
		}

		fprintf(fpDestroy, "\tdelete p%s ;\n\n", pIntf->getName().c_str());

		fprintf(fpComMethod, "%s::%s \*%s::getInterface_%s()\n", m_sName.c_str(), pIntf->getName().c_str(),
			m_sName.c_str(), pIntf->getName().c_str());
		fprintf(fpComMethod, "{\n");
		fprintf(fpComMethod, "\treturn p%s;\n", pIntf->getName().c_str());
		fprintf(fpComMethod, "}\n\n");

		if (Role == M_REQUIRE)
		{
			fprintf(fpComMethod, "%s \*%s::get%s()\n", pIntf->getInterfaceEntity()->getName().c_str(),
				m_sName.c_str(), pIntf->getName().c_str());
			fprintf(fpComMethod, "{\n");
			fprintf(fpComMethod, "\treturn p%s->p%s;\n", pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpComMethod, "}\n\n");
		}

		if (Role == M_PROVIDE)
		{
			fprintf(fpPartMethod, "%s::%s::%s(%s \*pObj)\n", m_sName.c_str(), pIntf->getName().c_str(),
				pIntf->getName().c_str(), m_sName.c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tpComponent = pObj;\n}\n\n");

			InterfaceEntity *pIntfEntity = pIntf->getInterfaceEntity();
			vector <OperationDesc *>::iterator it3;
			for (it3 = pIntfEntity->m_listOperation.begin(); it3 != pIntfEntity->m_listOperation.end(); ++it3)
			{
				OperationDesc *OPdesc = (*it3);
				OPdesc->CodeGeneration2(fpPartMethod, m_sName.c_str(), pIntf->getName().c_str());
				fprintf(fpPartMethod, "{\n");
				fprintf(fpPartMethod, "////TODO : Put your implementation below\n\n\n\n\n");
				if (OPdesc->getReturntype()->m_iType != T_VOID)
				{
					fprintf(fpPartMethod, "\treturn 0;\n");
				}
				else
				{
					fprintf(fpPartMethod, "\n");
				}
				
				fprintf(fpPartMethod, "}\n\n");
			}
		}
		else
		{
			fprintf(fpPartMethod, "%s::%s::%s()\n", m_sName.c_str(), pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tp%s = NULL;\n}\n\n", pIntf->getName().c_str());

			fprintf(fpPartMethod, "%s::%s::~%s()\n", m_sName.c_str(), pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpPartMethod, "{\n}\n\n");

			fprintf(fpPartMethod, "void %s::%s::ConnectTo(%s \*pComponentInterface)\n", m_sName.c_str(),
				pIntf->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str());
			fprintf(fpPartMethod, "{\n");
			fprintf(fpPartMethod, "\tif (pComponentInterface == NULL)\n");
			fprintf(fpPartMethod, "\t{\n\t\treturn;\n\t}\n");
			fprintf(fpPartMethod, "\tp%s = pComponentInterface;\n}\n\n", pIntf->getName().c_str());
		}
	} // End of loop for interfaces generation


	fprintf(fpHeader, "public:\n");
	fprintf(fpHeader, "\t%s(char \*instName);\n", m_sName.c_str());
	fprintf(fpHeader, "\t~%s();\n", m_sName.c_str());
	fprintf(fpHeader, "\tstatic DWORD WorkingThread(void *arg);\n");
	fprintf(fpHeader, "\tDWORD Task(%s \*Component);\n", m_sName.c_str());

	fprintf(fpHeader, "};\n\n#endif\n");

	//	fclose(fpHeader);

	fprintf(fpSource, "\thWorkingThread = CreateThread(0, 0 ,(LPTHREAD_START_ROUTINE)WorkingThread,this,CREATE_SUSPENDED,&dwThreadID);\n");
	fprintf(fpSource, "}\n");

	fprintf(fpDestroy, "}\n");
	fclose(fpDestroy);
	//	fprintf(fpComMethod, "}\n");
	fclose(fpComMethod);
	//	fprintf(fpPartMethod, "}\n");
	fclose(fpPartMethod);

	FILE *fp = fopen(DestroyFile.c_str(), "r");
	while (!feof(fp))
	{
		int c;
		c = fgetc(fp);
		if (c != EOF) fputc(c, fpSource);
	}
	fclose(fp);

	fp = fopen(ComMethods.c_str(), "r");
	while (!feof(fp))
	{
		int c;
		c = fgetc(fp);
		if (c != EOF) fputc(c, fpSource);
	}
	fclose(fp);

	fp = fopen(PartMethods.c_str(), "r");
	while (!feof(fp))
	{
		int c;
		c = fgetc(fp);
		if (c != EOF) fputc(c, fpSource);
	}
	fclose(fp);
	//lian add
	remove(DestroyFile.c_str());
	remove(ComMethods.c_str());
	remove(PartMethods.c_str());
	//	fclose(fpSource);
}
//构件源程序cpp中OnMsgEvent函数c++代码(师玉林)
//void ComponentEntity::ComSourceOnDdsEventGeneration(FILE *fpSource, bool Ifdds)
void ComponentEntity::ComSourceOnDdsEventGeneration(FILE *fpSource)
{
//	if(Ifdds)
//	{
	fprintf(fpSource, "\nint ECOM::Components::%s::OnDdsEvent(int msgMain, int msgSub1, int msgSub2, size_t length, char *info)\n{\n\t", m_sName.c_str());
//	}
//	else
//	{
	//	fprintf(fpSource, "\nint ECOM::Components::%s::OnMsgEvent(int msgMain, int msgSub1, int msgSub2, size_t length, char *info)\n{\n\t", m_sName.c_str());
//	}
	
	fprintf(fpSource, "if (!MainMsgConcern(msgMain)) return 0;\n\t");
	fprintf(fpSource, "switch (msgSub1)\n\t{\n\t");
	fprintf(fpSource, "case PORT_MSG:  {\n\t\t\t\t\t\t");
	fprintf(fpSource, "std::map<int, int>::iterator it;\n\t\t\t\t\t\t");

	fprintf(fpSource, "it = PortComing.find(msgMain*10000 + msgSub2);\n\t\t\t\t\t\t");
	fprintf(fpSource, "if (it == PortComing.end()) return 0;\n\t\t\t\t\t\t");
	fprintf(fpSource, "int MyPortID = it->second;\n\n\t\t\t\t\t\t");

	fprintf(fpSource, "ThreadForPortReceive *pPortThread;\n\t\t\t\t\t\t");
	fprintf(fpSource, "pPortThread = new ThreadForPortReceive;\n\t\t\t\t\t\t");
	fprintf(fpSource, "pPortThread->pPort = cPortID[MyPortID];\n\t\t\t\t\t\t");
	fprintf(fpSource, "pPortThread->info = new char[length + 1];\n\n\t\t\t\t\t\t");
	fprintf(fpSource, "memcpy(pPortThread->info, info, length + 1);\n\t\t\t\t\t\t");
	fprintf(fpSource, "boost::thread *pThread;\n\n\t\t\t\t\t\t");
	fprintf(fpSource, "pThread = new boost::thread(boost::bind(&ThreadForPortReceive::invoke, pPortThread));\n\n\t\t\t\t\t\t");
	fprintf(fpSource, "ThreadList.insert(std::pair<boost::thread::id, boost::thread *>(pThread->get_id(), pThread));\n\t\t\t\t\t\t");
	fprintf(fpSource, "break;\n\t\t\t\t\t");
	fprintf(fpSource, "}\n");

	fprintf(fpSource,
		"\tcase INTF_CALL_MSG:\n\t\t\t\t\t{\n\t\t\t\t\t\t"
		"ECOM::InterfaceProvided *pCalleeInterface;\n\t\t\t\t\t\t"
		"pCalleeInterface = pInterfaceID[msgSub2];\n\n\t\t\t\t\t\t"

		"if (pCalleeInterface == NULL)\n\t\t\t\t\t\n\t\t\t\t\t\t"

			"return 0;\n\t\t\t\t\t\n\t\t\t\t\t\t"

		"ECOM::ThreadForInterfaceCall *pInterfaceThread;\n\t\t\t\t\t\t"
		"pInterfaceThread = new ECOM::ThreadForInterfaceCall;\n\t\t\t\t\t\t"
		"pInterfaceThread->pInterface = pCalleeInterface;\n\t\t\t\t\t\t"
		"pInterfaceThread->CallerComID = msgMain;\n\t\t\t\t\t\t"
		"pInterfaceThread->info = new char[length + 1];\n\t\t\t\t\t\t"
		"memcpy(pInterfaceThread->info, info, length + 1);\n\n\t\t\t\t\t\t"
		"boost::thread *pThread;\n\t\t\t\t\t\t"
		"pThread = new boost::thread(boost::bind(& ECOM::ThreadForInterfaceCall::invoke,pInterfaceThread));\n\n\t\t\t\t\t\t"


		"ThreadList.insert(std::pair<boost::thread::id, boost::thread *>(pThread->get_id(), pThread));\n\n\t\t\t\t\t\t"

		"break;\n\t\t\t\t\t"
		"}\n"
		);
	if(UI_ServiceFlag == M_UI)
	{
		fprintf(fpSource,
		"\tcase INTF_RET_MSG:\n\t\t\t\t\t{\n\t\t\t\t\t\t"
		"if (msgSub2 != uiAttrInfo->pluginId) return 0;\n\t\t\t\t\t\t"
		"ECOM::InterfaceSerialize interfaceSerialize;\n\t\t\t\t\t\t"
		"std::istringstream is(info);\n\t\t\t\t\t\t"
		"boost::archive::text_iarchive ia(is);\n\t\t\t\t\t\t"
		"ia >> interfaceSerialize;\n\n\t\t\t\t\t\t"

		"InterfaceRequired *pInterfaceRequired = rInterfaceID[interfaceSerialize.CallerInterfaceID];\n\t\t\t\t\t\t"
		"int methodID = interfaceSerialize.CalleeMethodID;\n\n\t\t\t\t\t\t"

		"if (pInterfaceRequired->ReturnFlag[methodID] == 0) return 0;\n\n\t\t\t\t\t\t"

		"pInterfaceRequired->ReturnValues[methodID] = interfaceSerialize.Parameters;\n\t\t\t\t\t\t"
		"pInterfaceRequired->ReturnFlag[methodID] = 0;\n\n\t\t\t\t\t\t"

		"boost::thread::id *pThreadID = pInterfaceRequired->pThread[methodID];\n\t\t\t\t\t\t"
		"boost::thread *pThread = ThreadList[*pThreadID];\n\t\t\t\t\t\t"
		"pThread->interrupt();\n\n\t\t\t\t\t\t"

		"break;\n\t\t\t\t\t"
		"}\n"
		);
	}
	else if(UI_ServiceFlag == M_SERVICE)
	{
		fprintf(fpSource,
		"\tcase INTF_RET_MSG:\n\t\t\t\t\t{\n\t\t\t\t\t\t"
		"if (msgSub2 != serAttrInfo->componentId) return 0;\n\t\t\t\t\t\t"
		"ECOM::InterfaceSerialize interfaceSerialize;\n\t\t\t\t\t\t"
		"std::istringstream is(info);\n\t\t\t\t\t\t"
		"boost::archive::text_iarchive ia(is);\n\t\t\t\t\t\t"
		"ia >> interfaceSerialize;\n\n\t\t\t\t\t\t"

		"InterfaceRequired *pInterfaceRequired = rInterfaceID[interfaceSerialize.CallerInterfaceID];\n\t\t\t\t\t\t"
		"int methodID = interfaceSerialize.CalleeMethodID;\n\n\t\t\t\t\t\t"

		"if (pInterfaceRequired->ReturnFlag[methodID] == 0) return 0;\n\n\t\t\t\t\t\t"

		"pInterfaceRequired->ReturnValues[methodID] = interfaceSerialize.Parameters;\n\t\t\t\t\t\t"
		"pInterfaceRequired->ReturnFlag[methodID] = 0;\n\n\t\t\t\t\t\t"

		"boost::thread::id *pThreadID = pInterfaceRequired->pThread[methodID];\n\t\t\t\t\t\t"
		"boost::thread *pThread = ThreadList[*pThreadID];\n\t\t\t\t\t\t"
		"pThread->interrupt();\n\n\t\t\t\t\t\t"

		"break;\n\t\t\t\t\t"
		"}\n"
		);

	}
	fprintf(fpSource, "\t}\n");
	fprintf(fpSource, "\treturn 1;\n");
	fprintf(fpSource, "}\n");
}


//构件C++头文件的生成
void ComponentEntity::ComHeaderGeneration(FILE *fpHeader)
{
	//构件目录路径 2018.12.25
	string HeadDir = CDLDir;
	HeadDir.append("/Component/");
	HeadDir.append(m_sName);
	HeadDir.append("/include/");

	fprintf(fpHeader, "\nnamespace ECOM {\n");
	fprintf(fpHeader, "namespace Components {\n");
	vector<ComponentInterfaceDesc* >::iterator inf;
	for (inf = m_listInterface.begin();inf != m_listInterface.end(); inf++)
	{
		fprintf(fpHeader,"class %s;\n",(*inf)->getName().c_str());
	}
	vector<ComponentPortDesc* >::iterator port;
	for (port = m_listPort.begin(); port != m_listPort.end(); port++)
	{
		fprintf(fpHeader,"class %s;\n",(*port)->getName().c_str());
	}
	if(UI_ServiceFlag == M_SERVICE)
	{
		fprintf(fpHeader, "class %s: public BaseSer\n{\n",m_sName.c_str());
		fprintf(fpHeader, "public:\n");
		fprintf(fpHeader, "\t%s(SerLoad *ser);\n", m_sName.c_str());
		//fprintf(fpHeader, "\t{\n\t\tInitComponent();\n\t}\n");
		fprintf(fpHeader, "\t~%s(void) {}\n", m_sName.c_str());
		//fprintf(fpHeader, "\tstatic int InitComponentCount;\n\n");

		fprintf(fpHeader, "\npublic:\n");
		fprintf(fpHeader, "\tvirtual void InitComponent();\n");
		fprintf(fpHeader, "\tvirtual void FreeComponent();\n");
		fprintf(fpHeader, "\tvirtual void ActivateComponent();\n");
		fprintf(fpHeader, "\tvirtual void UnActivateComponent();\n");
		//fprintf(fpHeader, "\tvirtual void OnMsgEvent(int msgMain, int msgSub1, int msgSub2, size_t length = 0, char *info = 0);\n");
		//fprintf(fpHeader, "\tvirtual int OnDdsEvent(int msgMain, int msgSub1, int msgSub2, size_t length = 0, char *info = 0);\n\n");
	}
	else if(UI_ServiceFlag == M_UI)
	{
		fprintf(fpHeader, "class %s: public QWidget, public BaseUi\n{\n",m_sName.c_str());
		fprintf(fpHeader,"\tQ_OBJECT\n\n");
		fprintf(fpHeader, "public:\n");
		fprintf(fpHeader, "\texplicit %s(QWidget *parent = 0,ViewLoad *view = NULL);\n", m_sName.c_str());
		//fprintf(fpHeader, "\t{\n\t\tInitPlugin();\n\t}\n");
		fprintf(fpHeader, "\t~%s();\n", m_sName.c_str());
		//fprintf(fpHeader, "\tstatic int InitComponentCount;\n\n");

		fprintf(fpHeader, "\npublic:\n");
		fprintf(fpHeader, "\tvirtual void InitPlugin();\n");
		fprintf(fpHeader, "\tvirtual void FreePlugin();\n");
		fprintf(fpHeader, "\tvirtual void ActivatePlugin();\n");
		fprintf(fpHeader, "\tvirtual void UnActivatePlugin();\n");
		fprintf(fpHeader,"\tvirtual void ShowPlugin();\n");
		fprintf(fpHeader,"\tvirtual void HidePlugin();\n");

		fprintf(fpHeader, "\tUi_Form *getUiForm() const{return uiForm;};\n\n");
		//fprintf(fpHeader, "\tvirtual int OnMsgEvent(int msgMain, int msgSub1, int msgSub2, size_t length = 0, char *info = 0);\n");
		//fprintf(fpHeader, "\tvirtual int OnDdsEvent(int msgMain, int msgSub1, int msgSub2, size_t length = 0, char *info = 0);\n\n");
		fprintf(fpHeader,"private:\n");
		fprintf(fpHeader,"\tUi_Form *uiForm;\n\n");
	}


	fprintf(fpHeader, "private:\n");
	//构件中的接口C++  begin

	fprintf(fpHeader,"///////////////////////////////////////////////interface  instance/////////////////////////////////////////////////\n");
	vector <ComponentInterfaceDesc *>::iterator it2;
	for (it2 = m_listInterface.begin(); it2 != m_listInterface.end(); ++it2)
	{
		ComponentInterfaceDesc *pIntf = (*it2);
		//构造接口头文件路径
		string InfDir = HeadDir;
		InfDir.append(pIntf->getName());
		InfDir.append(".h");
		FILE *fpInfHeader = fopen(InfDir.c_str(),"w");
		//接口头文件公共部分
		fprintf(fpInfHeader,
			"#pragma  once\n\
			#include \"BaseSer.h\"\n\
			#include \"../../../include/%s.h\"\n\
			namespace ECOM {\n\
			namespace Components {\n\
			class %s;\n",CDLName.c_str(),m_sName.c_str()
		);
		int Role = pIntf->getRole();
		if (Role == M_PROVIDE)
		{
			//接口构造函数声明begin
			fprintf(fpInfHeader, "\t\tclass %s : public ECOM::Interface::%s::Provide::%s,ECOM::Base::Interface\n\t\t{\n", pIntf->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str());
			fprintf(fpInfHeader, "\t\tpublic:\n");
			fprintf(fpInfHeader, "\t\t\t%s *pComponent;\n", m_sName.c_str());
			fprintf(fpInfHeader, "\t\t\tclass MyReplierListener : public connext::ReplierListener<%s_params,%s_ret>{\n\t\t",pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfHeader,"\tpublic:\n\t\t\t%s *pInterface;\n\n",pIntf->getName().c_str());
			fprintf(fpInfHeader,"\t\t\t\tMyReplierListener(%s *p%s){\n\t\t\t\tthis->pInterface = p%s;\n\t\t\t}\n",pIntf->getName().c_str(),pIntf->getName().c_str(),pIntf->getName().c_str());
			fprintf(fpInfHeader,"\t\t\t\tvirtual void on_request_available(connext::Replier<%s_params, %s_ret> &replier);\n\t\t};\n",pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfHeader,"\t\t\t%s(%s *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier);\n\n\t",pIntf->getName().c_str(),m_sName.c_str());
			fprintf(fpInfHeader,"\t\tMyReplierListener *myreplierlistener;\n\n");
			//构造函数内的方法体声明
			vector <OperationDesc *>::iterator it;
			for (it = pIntf->getInterfaceEntity()->m_listOperation.begin(); it != pIntf->getInterfaceEntity()->m_listOperation.end(); ++it)
			{
				OperationDesc *pOP = *it;
				fprintf(fpInfHeader, "\t\t\t");
				pOP->CodeGeneration(fpInfHeader);
				fprintf(fpInfHeader, ";\n");
			}
			fprintf(fpInfHeader, "\t\t};\n\n");
			fprintf(fpInfHeader,"\t}\n}");
			fclose(fpInfHeader);
			//接口构造函数end
			//接口指针
			fprintf(fpHeader, "//pointer to interface & get pointer\nprivate:\n\t%s *p%s;\n", pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s *getProvideInterface%s()\n", pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "\t{\n\t\treturn p%s;\n\t}\n\n", pIntf->getName().c_str());

		}
		else if (Role == M_REQUIRE)
		{
			//接口构造函数begin
			fprintf(fpInfHeader, "\t\tclass %s : public ECOM::Interface::%s::Require::%s,ECOM::Base::Interface\n\t\t{\n", pIntf->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str());
			fprintf(fpInfHeader, "\t\tpublic:\n");
			//if(UI_ServiceFlag == M_SERVICE)//服务构件
			//{
			//	fprintf(fpHeader, "\t\t%s(BaseSer *pComponent, int ComponentType, int interfaceID, int CalleeComID, int CalleeInterfaceID)\n", pIntf->getName().c_str());
			//	fprintf(fpHeader, "\t\t\t: ECOM::Interface::%s::Require::%s(pComponent, ComponentType, interfaceID, CalleeComID, CalleeInterfaceID)\n", pIntf->getInterfaceEntity()->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str());
			//}
			//else if(UI_ServiceFlag == M_UI)//UI构件
			//{
			//	fprintf(fpHeader, "\t\t%s(BaseUi *pComponent, int ComponentType, int interfaceID, int CalleeComID, int CalleeInterfaceID)\n", pIntf->getName().c_str());
			//	fprintf(fpHeader, "\t\t\t: ECOM::Interface::%s::Require::%s(pComponent, ComponentType, interfaceID, CalleeComID, CalleeInterfaceID)\n", pIntf->getInterfaceEntity()->getName().c_str(), pIntf->getInterfaceEntity()->getName().c_str());
			//}
			fprintf(fpInfHeader, "\t\t\t%s *pComponent;\n", m_sName.c_str());
			fprintf(fpInfHeader,"\t\t\t%s(%s *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier);\n\n",pIntf->getName().c_str(),m_sName.c_str());
			vector <OperationDesc *>::iterator it;
			for (it = pIntf->getInterfaceEntity()->m_listOperation.begin(); it != pIntf->getInterfaceEntity()->m_listOperation.end(); ++it)
			{
				OperationDesc *pOP = *it;
				fprintf(fpInfHeader, "\t\t\t");
				pOP->CodeGeneration(fpInfHeader);
				fprintf(fpInfHeader, ";\n");
			}
			fprintf(fpInfHeader, "\t\t};\n");
			fprintf(fpInfHeader,"\t}\n}");
			fclose(fpInfHeader);
			//接口构造函数end
			fprintf(fpHeader, "//pointer to interface & get pointer\nprivate:\n\t%s *p%s;\n", pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s *getRequireInterface%s()\n", pIntf->getName().c_str(), pIntf->getName().c_str());
			fprintf(fpHeader, "\t{\n\t\treturn p%s;\n\t}\n\n", pIntf->getName().c_str());

			//hy发送请求函数 add 2018.10.11
			fprintf(fpHeader,"private:\n");
			fprintf(fpHeader,"\tvoid %s_send_request();\n",pIntf->getName().c_str());
		}
		
	}//构件中的接口C++ end
	//构件中端口C++ begin
	fprintf(fpHeader,"///////////////////////////////////////////////port  instance/////////////////////////////////////////////////\n");
	vector <ComponentPortDesc *>::iterator it;
	for (it = m_listPort.begin(); it != m_listPort.end(); ++it)
	{
		ComponentPortDesc *pPort = (*it);
		//构造端口头文件路径
		string PortDir = HeadDir;
		PortDir.append(pPort->getName());
		PortDir.append(".h");
		FILE *fpPortHeader = fopen(PortDir.c_str(),"w");
		//端口头文件公共部分
		fprintf(fpPortHeader,
			"#pragma  once\n\
			#include \"BaseSer.h\"\n\
			#include \"../../../include/%s.h\"\n\
			#include <stdarg.h>\n\
			#include <boost/thread/mutex.hpp>\n\n",CDLName.c_str()
		);
		// 在这里判断一下是端口是否是周期性接收
		int recvType = getRecvType(pPort->getName());
		cout << pPort->getName() << endl;

		if (recvType != RECV_EVENT) {
			fprintf(fpPortHeader, "#include <queue>\n\n");
		}
		fprintf(fpPortHeader, 
			"namespace ECOM {\n\
			namespace Components {\n\
			class %s;\n", m_sName.c_str()
		);
		
		int PubSub = pPort->getPubSub();
		if (PubSub == M_CONSUME)
		{
			//端口构造函数begin
			fprintf(fpPortHeader, "\t\tclass %s : public ECOM::Base::PortConsume,public ECOM::Base::Port,public ECOM::Port::%s::Consume::%s\n",
					pPort->getName().c_str(),pPort->getPortEntity()->getName().c_str(),pPort->getPortEntity()->getName().c_str());
			fprintf(fpPortHeader, "\t\t{\n\t\tpublic:\n");
			fprintf(fpPortHeader, "\t\t\t%s(%s *pComponent,int portID,std::string portName, std::string portType, std::string portModifier);\n",
					pPort->getName().c_str(), m_sName.c_str());
			fprintf(fpPortHeader,"\t\t\t%s *pComponent;\n",m_sName.c_str());
			// 判断是否为周期性接收
			if (recvType == RECV_EVENT)
				fprintf(fpPortHeader,"\t\t\tvoid ReceiveMegs();\n");
			else
				fprintf(fpPortHeader,"\t\t\tvoid ReceiveMegs(int period);\n");
			
			// 如果是消息队列，需要设置buffer大小
			if (recvType == RECV_MSGQUEUE) 
				fprintf(fpPortHeader, "\t\t\tvoid setBufferSize(int size);\n");
			//监听器函数begin
			fprintf(fpPortHeader,"\t\t\tclass %sListener : public DDSDataReaderListener{\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortHeader,"\t\t\tpublic:\n");
			fprintf(fpPortHeader,"\t\t\t\t%s *pPort;\n",pPort->getName().c_str());
			fprintf(fpPortHeader,"\t\t\t\t%sListener(%s *pPort);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),
					pPort->getName().c_str());
			// 使用事件型或消息队列，用on_data_available函数接收数据
			if (recvType == RECV_EVENT || recvType == RECV_MSGQUEUE)
				fprintf(fpPortHeader,"\t\t\t\tvirtual void on_data_available(DDSDataReader* reader);\n");
			fprintf(fpPortHeader,"\t\t\t};\n\n");
			//监听器函数end
			fprintf(fpPortHeader,"\t\tprivate:\n");
			fprintf(fpPortHeader,"\t\t\tvoid DataProcess(%s *pinstance);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			// 添加消息队列
			if (recvType == RECV_MSGQUEUE) {
				fprintf(fpPortHeader,"\t\t\tstd::queue<%s> msgQueue;\n", pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
				fprintf(fpPortHeader,"\t\t\tint bufferSize;\n");
			}
			fprintf(fpPortHeader, "\t\t};\n\n");
			fprintf(fpPortHeader,"\t}\n}");
			fclose(fpPortHeader);
			//端口构造函数end

			//指向端口的指针
			fprintf(fpHeader, "private:\n");
			fprintf(fpHeader, "\t%s *p%s;\n", pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s *getConsumePort%s()\n", pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpHeader, "\t{\n\t\treturn p%s;\n\t}\n\n", pPort->getName().c_str());

		}
		else if (PubSub == M_PUBLISH)
		{
			//端口构造函数begin
			fprintf(fpPortHeader, "\t\tclass %s : public ECOM::Port::%s::Publish::%s,ECOM::Base::PortPublish,ECOM::Base::Port\n", pPort->getName().c_str(), pPort->getPortEntity()->getName().c_str(), pPort->getPortEntity()->getName().c_str());
			fprintf(fpPortHeader, "\t\t{\n");
			fprintf(fpPortHeader, "\t\tprivate:\n");
			fprintf(fpPortHeader, "\t\t\tboost::mutex mLock;\n");
			fprintf(fpPortHeader, "\t\tpublic:\n");
			fprintf(fpPortHeader, "\t\t\t%s(%s *pComponent, int portID, std::string portName, "
								 "std::string portType, std::string portModifier);\n",pPort->getName().c_str(),m_sName.c_str());
			fprintf(fpPortHeader,"\t\t\t%s *pComponent;\n",m_sName.c_str());
			fprintf(fpPortHeader,"\t\t\tDDS_ReturnCode_t Publish();\n");
			// 需要讨论周期和非周期的情况
			if (getPublishPeriod(pPort) != 0) {
				fprintf(fpPortHeader,"\t\t\tvoid %sSendMegs(int send_period));\n",pPort->getName().c_str());
			}
			else {
				fprintf(fpPortHeader,"\t\t\tvoid %sSendMegs();\n",pPort->getName().c_str());
			}
			//by CJ
			fprintf(fpPortHeader,"\t\t\tvoid SetMessage(%s& Megs);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			//CJ Coding Ending
			fprintf(fpPortHeader,"\t\t};\n\n");
			fprintf(fpPortHeader,"\t}\n}");
			fclose(fpPortHeader);
			//端口构造函数end

			//端口指针
			fprintf(fpHeader, "private:\n");
			fprintf(fpHeader, "\t%s *p%s;\n", pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpHeader, "public:\n");
			fprintf(fpHeader, "\t%s *getPublishPort%s()\n", pPort->getName().c_str(), pPort->getName().c_str());
			fprintf(fpHeader, "\t{\n\t\treturn p%s;\n\t}\n\n", pPort->getName().c_str());

			/*fprintf(fpHeader, "\tECOM::Port::%s::Publish::%s *p%s;\n", pPort->getPortEntity()->getName().c_str(), pPort->getPortEntity()->getName().c_str(), pPort->getName().c_str());
			fprintf(fpHeader, "\tECOM::Port::%s::Publish::%s *getPublishPort%s()\n", pPort->getPortEntity()->getName().c_str(), pPort->getPortEntity()->getName().c_str(), pPort->getName().c_str());
			fprintf(fpHeader, "\t{\n\t\treturn p%s;\n\t}\n\n", pPort->getName().c_str());*/
		}
	}

	if(UI_ServiceFlag == M_UI)
	{
		fprintf(fpHeader,"\nprivate:\n");
		fprintf(fpHeader,"\t//// You can define any private variables here\n\n");

		//HY  add 2018.10.11
		fprintf(fpHeader,"\t//// You can define any private variables here\n\n");
		fprintf(fpHeader,"private slots:\n");
		fprintf(fpHeader,"\t//// You put your slots declarations here\n\n");

	}

	fprintf(fpHeader, "};\n\n");  //构件类  end
	//fprintf(fpHeader, "int %s::InitComponentCount = 0;\n\n", m_sName.c_str());

	fprintf(fpHeader, "}\n}\n");//命名空间Component和ECOM  end
	//声明导出的函数
	/*fprintf(fpHeader, "extern \"C\" _declspec(dllexport) \n");
	fprintf(fpHeader, "BaseSer* CreatComponent();\n\n",m_sName.c_str());*/
}
//构件实体cpp代码生成
void ComponentEntity::ComSourceGeneration(FILE *fpSource)
{
	//构件目录路径 2018.12.25
	string SourceDir = CDLDir;
	SourceDir.append("/Component/");
	SourceDir.append(m_sName);
	SourceDir.append("/sources/");

	// 在这里设置组件内部发送端口的编号，方便后续给它们标记flagNum
	int flagNum = 1;
	// 周期性接收端口的数量
	int recv_periodic_num = 0;
	// 统计发送端口和接收端口的信息
	for (auto it = m_listPort.begin(); it != m_listPort.end(); ++it) {
		ComponentPortDesc *pPort = (*it);
		// 如果是周期性发送端口，就添加flag标志位
		if (getPublishPeriod(pPort) != 0) {
			publish_flags[pPort->getName()] = flagNum;
			flagNum++;
		}
		if (getRecvPeriod(pPort) != 0) {
			receive_periods[pPort->getName()] = getRecvPeriod(pPort);
			recv_periodic_num++;
		}
	}

	if (flagNum != 1) {
		fprintf(fpSource, "#include \"../flagSign.h\"\n");
		fprintf(fpSource, "void sendMegs(ECOM::Components::%s *pCom);\n", m_sName.c_str());
	}
	// send和recv函数声明
	if (recv_periodic_num != 0) {
		fprintf(fpSource, "void recvMegs(ECOM::Components::%s *pCom);\n", m_sName.c_str());
	}

	if(UI_ServiceFlag == M_UI)
	{
		//构造函数
		fprintf(fpSource, "ECOM::Components::%s::%s(QWidget *parent,ViewLoad *view):QWidget(parent)\n",m_sName.c_str(), m_sName.c_str());
		fprintf(fpSource, "{\n\n");
		fprintf(fpSource,"\t/* To customize the participant QoS, use the configuration file USER_QOS_PROFILES.xml */\n");
		fprintf(fpSource,"\tthis->compId = view->pluginId;\n");
		fprintf(fpSource,"\tthis->compName = view->pluginName;\n");
		fprintf(fpSource,"\tthis->vec_Ports = view->vec_Ports;\n");
		fprintf(fpSource,"\tthis->vec_Interfaces = view->vec_Interfaces;\n");
		fprintf(fpSource,"\tthis->uix = view->x;\n");
		fprintf(fpSource,"\tthis->uiy = view->y;\n");
		fprintf(fpSource,"\tuiForm = new Ui_Form;\n");
		fprintf(fpSource,"\tuiForm->setupUi(this);\n");
		fprintf(fpSource,"\tthis->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);\n");
		fprintf(fpSource, "}\n");
		//析构函数
		fprintf(fpSource, "ECOM::Components::%s::~%s()\n",m_sName.c_str(), m_sName.c_str());
		fprintf(fpSource, "{\n\tif (uiForm != NULL)\n");
		fprintf(fpSource, "\t{\n\t\tdelete uiForm;\n\t}\n}\n\n");
	}
	else if(UI_ServiceFlag == M_SERVICE)
	{
		//构造函数
		fprintf(fpSource, "ECOM::Components::%s::%s(SerLoad *ser)\n",m_sName.c_str(), m_sName.c_str());
		fprintf(fpSource, "{\n\n");
		fprintf(fpSource,"\tthis->compId = ser->compId;\n");
		fprintf(fpSource,"\tthis->compName = ser->compName;\n");
		fprintf(fpSource,"\tthis->vec_Ports = ser->vec_Ports;\n");
		fprintf(fpSource,"\tthis->vec_Interfaces = ser->vec_Interfaces;\n\n");
		fprintf(fpSource,"this->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);\n");
		fprintf(fpSource,"\t/* To customize participant QoS, use DDSTheParticipantFactory->get_default_participant_qos() instead */\n");
		fprintf(fpSource,"}\n\n");
	}
	if(UI_ServiceFlag == M_SERVICE)
	{
		fprintf(fpSource, "void ECOM::Components::%s::InitComponent()\n{\n\n", m_sName.c_str());
	}
	else if(UI_ServiceFlag == M_UI)
	{
		fprintf(fpSource, "void ECOM::Components::%s::InitPlugin()\n{\n\n", m_sName.c_str());
		//fprintf(fpSource, "\tthis->uiAttrInfo->pluginPoint = (long)this;\n\n");
		//fprintf(fpSource, "\tuiForm = new Ui_Form;\n\tuiForm->setupUi(this);\n\n");
	}

	//InitPlugin/Component function
	fprintf(fpSource,"\tvector<ECOM::Base::Port>::iterator it1;\n");
	fprintf(fpSource,"\tfor(it1 = this->vec_Ports.begin();it1 != this->vec_Ports.end();it1++)\n\t{\n");
	vector <ComponentPortDesc *>::iterator it;
	for (it = m_listPort.begin(); it != m_listPort.end(); ++it)
	{

		ComponentPortDesc *pPort = (*it);
		int PubSub = pPort->getPubSub();

		string name = pPort->getName();
		fprintf(fpSource,"\t\tif(it1->portName == \"%s\")\n\t\t{\n",name.c_str());
		fprintf(fpSource,"\t\t\tp%s = new %s(this,it1->portID,it1->portName,it1->portType,it1->portModifier);\n",name.c_str(), name.c_str());
		// 如果是周期性接收需要添加的设置
		int type = getRecvType(name);
		if (type == RECV_MSGQUEUE) {
			fprintf(fpSource, "\t\t\tp%s->setBufferSize(%d);\n", name.c_str(), getRecvQueueLen(pPort));
		}
		if (type == RECV_SAMPLING || type == RECV_MSGQUEUE) {
			fprintf(fpSource, "\t\t\tboost::thread thrdb1(boost::bind(&recvMegs,this));\n");
		}
		fprintf(fpSource,"\t\t}\n");
	}
	fprintf(fpSource,"\t}\n");
	fprintf(fpSource,"\tvector<ECOM::Base::Interface>::iterator it2;\n");
	fprintf(fpSource,"\tfor(it2 = this->vec_Interfaces.begin();it2 != this->vec_Interfaces.end();it2++)\n\t{\n");
	vector <ComponentInterfaceDesc *>::iterator it1;
	for (it1 = m_listInterface.begin(); it1 != m_listInterface.end(); ++it1)
	{
		ComponentInterfaceDesc *pInterface = (*it1);
		fprintf(fpSource,"\t\tif(it2->interfaceName == \"%s\")\n\t\t{\n",pInterface->getName().c_str());
		fprintf(fpSource,"\t\t\tp%s = new %s(this,it2->interfaceID,it2->interfaceName,it2->serviceName,it2->interfaceType,it2->interfaceModifier);\n\t\t}\n"
				,pInterface->getName().c_str(),pInterface->getName().c_str());
	}
	fprintf(fpSource,"\t}\n");
	/*for (it = m_listPort.begin(); it != m_listPort.end(); ++it)
	{
		ComponentPortDesc *pPort = (*it);
		int PubSub = pPort->getPubSub();
		if (PubSub == M_CONSUME)
		{
			fprintf(fpSource,"\tboost::thread *pThreadFor%s;\n",pPort->getName().c_str());
			fprintf(fpSource,"\tpThreadFor%s = new boost::thread(boost::bind(&ECOM::Components::%s::%s::ReceiveMegs,p%s));\n",
				pPort->getName().c_str(),m_sName.c_str(),pPort->getName().c_str(),pPort->getName().c_str());
		}
	}*/
	fprintf(fpSource,"\tthis->status=ECOM::Base::Initialized;\n");
	fprintf(fpSource,"}\n\n");
	//rest lifecycle functions
	if (UI_ServiceFlag == M_UI)
	{
		fprintf(fpSource,"void ECOM::Components::%s::FreePlugin()\n{\n\n\tthis->status=ECOM::Base::UnLoaded;\n}\n\n",m_sName.c_str());
		fprintf(fpSource,"void ECOM::Components::%s::ActivatePlugin()\n{\n\n\tthis->status=ECOM::Base::Activated;\n}\n\n",m_sName.c_str());
		fprintf(fpSource,"void ECOM::Components::%s::UnActivatePlugin()\n{\n\n\tthis->status=ECOM::Base::UnActivated;\n}\n\n",m_sName.c_str());
		fprintf(fpSource,"void ECOM::Components::%s::ShowPlugin()\n{",m_sName.c_str());
		fprintf(fpSource,"\t//TODO: put your logic for plugin showing\n");
		fprintf(fpSource,"\tthis->show();\n\tthis->move(uix,uiy);\n");
		fprintf(fpSource,"}\n\n");
		fprintf(fpSource,"void ECOM::Components::%s::HidePlugin()\n{\n}\n\n",m_sName.c_str());
	}
	else if(UI_ServiceFlag == M_SERVICE)
	{
		if (flagNum != 1) {
			periodic_freeComp(fpSource, m_sName.c_str(), flagNum-1);
			periodic_activateComp(fpSource, m_sName.c_str(), flagNum-1);
			periodic_unactivateComp(fpSource, m_sName.c_str(), flagNum-1);
		}
		else {
			fprintf(fpSource,"void ECOM::Components::%s::FreeComponent()\n{\n\n\tthis->status=ECOM::Base::UnLoaded;\n}\n\n",m_sName.c_str());
			fprintf(fpSource,"void ECOM::Components::%s::ActivateComponent()\n{\n\n\tthis->status=ECOM::Base::Activated;\n}\n\n",m_sName.c_str());
			fprintf(fpSource,"void ECOM::Components::%s::UnActivateComponent()\n{\n\n\tthis->status=ECOM::Base::UnActivated;\n}\n\n",m_sName.c_str());
		}		
	}
	//构件中接口的初始化 cpp
	vector <ComponentInterfaceDesc *>::iterator it2;
	for (it2 = m_listInterface.begin(); it2 != m_listInterface.end(); ++it2)
	{
		ComponentInterfaceDesc *pIntf = (*it2);
		string InfDir = SourceDir;
		InfDir.append(pIntf->getName());
		InfDir.append(".cpp");
		FILE *fpInfSource = fopen(InfDir.c_str(),"w");
		//接口cpp文件公共部分
		fprintf(fpInfSource,"#include \"../include/%s.h\"\n"
							"#include \"../include/%s.h\"\n",pIntf->getName().c_str(),m_sName.c_str());
		
		int Role = pIntf->getRole();
		if (Role == M_PROVIDE)
		{
			//接口构造函数
			fprintf(fpInfSource,"ECOM::Components::%s::%s(%s *pComponent,int interfaceID,std::string interfaceName,"
							 "std::string serviceName,std::string interfaceType,std::string interfaceModifier){\n",
							 pIntf->getName().c_str(),pIntf->getName().c_str(),m_sName.c_str());
			fprintf(fpInfSource,"\tthis->pComponent = pComponent;\n");
			fprintf(fpInfSource,"\tthis->interfaceID = interfaceID;\n");
			fprintf(fpInfSource,"\tthis->interfaceName = interfaceName;\n");
			fprintf(fpInfSource,"\tthis->serviceName = serviceName;\n");
			fprintf(fpInfSource,"\tthis->interfaceType = interfaceType;\n");
			fprintf(fpInfSource,"\tthis->interfaceModifier = interfaceModifier;\n\n");
			//fprintf(fpInfSource,"\tthis->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpInfSource,"\tthis->participant = this->pComponent->participant;\n");
			fprintf(fpInfSource,"\tthis->myreplierlistener = new MyReplierListener(this);\n\n");
			fprintf(fpInfSource,"\tconnext::ReplierParams<%s_params,%s_ret>replier_params(this->participant);\n",
					pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfSource,"\treplier_params.service_name(serviceName);\n");
			fprintf(fpInfSource,"\treplier_params.qos_profile(\"RequestReplyExampleProfiles\", \"ReplierExampleProfile\");\n\n");
			fprintf(fpInfSource,"\treplier_params.replier_listener(*myreplierlistener);\n");
			//异常处理 requester replierQos 加载
			fprintf(fpInfSource,"\ttry{\n");
			fprintf(fpInfSource,"\t\tthis->replier = new connext::Replier<%s_params,%s_ret>(replier_params);\n",
					pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfSource,"\t} catch(const connext::RuntimeException& ex) {\n");
			fprintf(fpInfSource,"\t\tstd::cout<<\"Exception while loading replier:\"<<ex.what()<<std::endl;\n\t}\n");
			fprintf(fpInfSource,"}\n");
/////////////on_request_avaible begin
			fprintf(fpInfSource,"void ECOM::Components::%s::MyReplierListener::on_request_available(connext::Replier<%s_params,%s_ret> &replier){\n",
			pIntf->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfSource,"\tconnext::LoanedSamples<%s_params> requests = replier.take_requests(DDS_LENGTH_UNLIMITED);\n",pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfSource,"\ttypedef connext::LoanedSamples<%s_params>::iterator iterator;\n",pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfSource,"\tfor (iterator it = requests.begin();it != requests.end(); ++it) {\n");
			fprintf(fpInfSource,"\t\tif (it->info().valid_data) {\n\n");
			//on_request_available 取出params中的值
			vector <OperationDesc *>::iterator op;
			for (op = pIntf->getInterfaceEntity()->m_listOperation.begin(); op != pIntf->getInterfaceEntity()->m_listOperation.end(); ++op)
			{
				OperationDesc *pOP = *op;
				pOP->onRequestOpParamCpp(fpInfSource,pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
				//发送回复
				//fprintf(fpSource,"\t\t\t/*Send reply indicating error */\n");
				//fprintf(fpSource,"\t\t\tconnext::WriteSample<%s_ret> reply;\n",pIntf->getInterfaceEntity()->getName().c_str());
				//fprintf(fpSource,"reply.data().result = result;\n");
				//pOP->onRequestOpResultCpp(fpSource);
				////fprintf(fpSource,"\t\t\tstd::cout << \"Transformer DONE\"<<std::endl;");
				//fprintf(fpSource,"\t\t}\n\t}\n");
			}
			fprintf(fpInfSource,"}\n\n");
/////////////on_request_availble end

////////////provide接口内函数方法体
			ComponentInterfaceDesc *pIntf = (*it2);
			int Role = pIntf->getRole();
			for (op = pIntf->getInterfaceEntity()->m_listOperation.begin(); op != pIntf->getInterfaceEntity()->m_listOperation.end(); ++op)
			{
				OperationDesc *pOP = *op;
				pOP->OpComProvideOpCpp(fpInfSource, m_sName, pIntf->getName().c_str());
			}
		}
		else if (Role == M_REQUIRE)
		{

			//接口构造函数
			fprintf(fpInfSource,"ECOM::Components::%s::%s(%s *pComponent,int interfaceID,std::string interfaceName,"
				"std::string serviceName,std::string interfaceType,std::string interfaceModifier){\n",
				pIntf->getName().c_str(),pIntf->getName().c_str(),m_sName.c_str());
			fprintf(fpInfSource,"\tthis->pComponent = pComponent;\n");
			fprintf(fpInfSource,"\tthis->interfaceID = interfaceID;\n");
			fprintf(fpInfSource,"\tthis->interfaceName = interfaceName;\n");
			fprintf(fpInfSource,"\tthis->serviceName = serviceName;\n");
			fprintf(fpInfSource,"\tthis->interfaceType = interfaceType;\n");
			fprintf(fpInfSource,"\tthis->interfaceModifier = interfaceModifier;\n\n");
			//fprintf(fpInfSource,"\tthis->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpInfSource,"\tthis->participant = this->pComponent->participant;\n");
			fprintf(fpInfSource,"\tconnext::RequesterParams requester_params(this->participant);\n");
			fprintf(fpInfSource,"\trequester_params.service_name(serviceName);\n");
			fprintf(fpInfSource,"\trequester_params.qos_profile(\"RequestReplyExampleProfiles\",\"RequesterExampleProfile\");\n");

			//异常处理 requester replierQos 加载
			fprintf(fpInfSource,"\ttry{\n");
			fprintf(fpInfSource,"\tthis->requester = new connext::Requester<%s_params,%s_ret>(requester_params);\n",
				pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpInfSource,"\t} catch(const connext::RuntimeException& ex) {\n");
			fprintf(fpInfSource,"\t\tstd::cout<<\"Exception while loading replier:\"<<ex.what()<<std::endl;\n\t}\n");
			fprintf(fpInfSource,"}\n");

			//hy add 2018.10.11 
			//增加状态的检测by CJ
			fprintf(fpSource,"/***********************************************\n");
			fprintf(fpSource,"*TODO:%s接口的请求发送函数，在该函数中调用接口的方法。\n",pIntf->getName().c_str() );
			fprintf(fpSource,"*用法已在方法体中注释\n");
			fprintf(fpSource,"***********************************************/\n");
			fprintf(fpSource,"void ECOM::Components::%s::%s_send_request()\n",m_sName.c_str(),pIntf->getName().c_str());
			fprintf(fpSource,"{\n");
			fprintf(fpSource,"\tif (this->status==ECOM::Base::Activated)\n");
			fprintf(fpSource,"\t{\n");
			fprintf(fpSource,"\t/***********************************************\n");
			fprintf(fpSource,"\t*TODO: put your logic business code here\n");
			fprintf(fpSource,"\t*调用接口内方法的例子\n");
			fprintf(fpSource,"\t*this->getRequireInterface%s->%s(parameters<>)\n",pIntf->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			fprintf(fpSource,"\t***********************************************/\n");
			fprintf(fpSource,"\n\n\n");
			fprintf(fpSource,"\t}\n");
			fprintf(fpSource,"}\n");
			



			//require接口内函数方法体
			ComponentInterfaceDesc *pIntf = (*it2);
			int Role = pIntf->getRole();
			vector <OperationDesc *>::iterator op;
			for (op = pIntf->getInterfaceEntity()->m_listOperation.begin(); op != pIntf->getInterfaceEntity()->m_listOperation.end(); ++op)
			{
				OperationDesc *pOP = *op;
				pOP->OpRequireOperationCpp(fpInfSource, m_sName, pIntf->getName().c_str(),pIntf->getInterfaceEntity()->m_listOperation.front()->getName().c_str());
			}

		}
		fclose(fpInfSource);
	}
	// 在端口初始化之前，检查是否存在周期性发送端口，如果存在的话就添加flagSign.h头文件
	if (flagNum != 1) {
		string flagSign = CDLDir;
		flagSign.append("/Component/");
		flagSign.append(m_sName);
		flagSign.append("/flagSign.h");
		FILE *fpFlagSign = fopen(flagSign.c_str(), "w");
		fprintf(fpFlagSign, "int flagGlobal = 0;\n");
		for (it = m_listPort.begin(); it != m_listPort.end(); ++it) {
			ComponentPortDesc *pPort = (*it);
			string name = pPort->getName();
			if (publish_flags.find(name) != publish_flags.end()) {
				fprintf(fpFlagSign, "int flagNum%d = 0;\n", publish_flags[name]);
			}
		}
		fclose(fpFlagSign);
	}
	// 统计publish和consume端口的名字
	vector<string> publish_names;
	vector<string> consume_names;
	//构件中端口的初始化 cpp
	for (it = m_listPort.begin(); it != m_listPort.end(); ++it)
	{
		ComponentPortDesc *pPort = (*it);
		string PortDir = SourceDir;
		PortDir.append(pPort->getName());
		PortDir.append(".cpp");
		FILE *fpPortSource = fopen(PortDir.c_str(),"w");
		//端口cpp文件公共部分
		fprintf(fpPortSource,"#include \"../include/%s.h\"\n"
			"#include \"../include/%s.h\"\n",pPort->getName().c_str(),m_sName.c_str());
		
		// 在这里判断一下是端口是否是周期性接收
		int recvType = getRecvType(m_sName);
		if (recvType == -1)
			throw runtime_error("Undefined Consume Port Type!!!");
		
		int PubSub = pPort->getPubSub();
		if (PubSub == M_CONSUME)
		{
			consume_names.push_back(pPort->getName());
			//端口构造函数
			fprintf(fpPortSource,"ECOM::Components::%s::%s(%s *pComponent,int portID,std::string portName,"
				"std::string portType,std::string portModifier){\n",
				pPort->getName().c_str(),pPort->getName().c_str(),m_sName.c_str());
			fprintf(fpPortSource,"\tthis->pComponent = pComponent;\n");
			fprintf(fpPortSource,"\tthis->portID = portID;\n");
			fprintf(fpPortSource,"\tthis->portName = portName;\n");
			fprintf(fpPortSource,"\tthis->portType = portType;\n");
			fprintf(fpPortSource,"\tthis->portModifier = portModifier;\n");
			//fprintf(fpPortSource,"\tthis->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpPortSource,"\tthis->participant = this->pComponent->participant;\n");
			fprintf(fpPortSource,"\tthis->topic_name = \"%s\";\n\n",pPort->getPortEntity()->getName().c_str());
			fprintf(fpPortSource,"\t/* Register type before creating topic */\n");
			fprintf(fpPortSource,"\ttype_name = %sTypeSupport::get_type_name();\n\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\t%sTypeSupport::register_type(this->participant, type_name);\n\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\t/* To customize topic QoS, use participant->get_default_topic_qos() instead */\n");
			//find_topic 没有则创建，已存在则使用
			fprintf(fpPortSource,"\tDDS_Duration_t t = {0,10000};\n");
			fprintf(fpPortSource,"\tthis->topic = this->participant->find_topic(this->topic_name,t);\n");
			fprintf(fpPortSource,"\tif(this->topic == NULL)\n");
			fprintf(fpPortSource,"\t{\n\t\tthis->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);\n");
			fprintf(fpPortSource,"\t}\n");
			//fprintf(fpPortSource,"\tthis->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpPortSource,"\t/* To customize the subscriber QoS, use the configuration file USER_QOS_PROFILES.xml */\n");
			fprintf(fpPortSource,"\tsubscriber = this->participant->create_subscriber(DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpPortSource,"\t%sListener *reader_listener = new %sListener(this);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),
				pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\t/* To customize the data reader QoS, use the configuration file USER_QOS_PROFILES.xml */\n");
			fprintf(fpPortSource,"\tthis->reader = subscriber->create_datareader(topic, DDS_DATAREADER_QOS_DEFAULT, reader_listener /* listener */,DDS_STATUS_MASK_ALL);\n\n");
			fprintf(fpPortSource,"}\n");
			//端口监听器构造函数
			fprintf(fpPortSource,"ECOM::Components::%s::%sListener::%sListener(%s *pPort) {\n",pPort->getName().c_str(),pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str()
				,pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),pPort->getName().c_str());
			fprintf(fpPortSource,"\tthis->pPort = pPort;\n}\n\n");


			// 设置消息队列大小
			if (recvType == RECV_MSGQUEUE) {
				fprintf(fpPortSource, "void ECOM::Components::%s::setBufferSize(int queue_length) {\n", pPort->getName().c_str());
				fprintf(fpPortSource, "\tthis->bufferSize = queue_length;\n");
				fprintf(fpPortSource, "}\n");
			}
			//端口on_data_available函数

			if (recvType == RECV_MSGQUEUE || recvType == RECV_EVENT) {
				set_on_data_available(fpPortSource, pPort, recvType);
			}

			//端口ReceiveMegs函数
			set_receive_Megs(fpPortSource, pPort, recvType);

			//端口DataProcess函数 by CJ
			fprintf(fpPortSource,"/***********************************************\n");
			fprintf(fpPortSource,"*%s端口的数据处理函数，用于处理接收到的数据\n",pPort->getName().c_str());
			fprintf(fpPortSource,"***********************************************/\n");
			fprintf(fpPortSource,"void ECOM::Components::%s::DataProcess(%s *pinstance){\n",pPort->getName().c_str(),
					pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\tif (pComponent->status==ECOM::Base::Activated)\n");
			fprintf(fpPortSource,"\t{\n");
			fprintf(fpPortSource,"\t/***********************************************\n");
			fprintf(fpPortSource,"\t*TODO : put your logic to process data\n");
			fprintf(fpPortSource,"\t***********************************************/\n\n\n");
			fprintf(fpPortSource,"\t}\n");
			fprintf(fpPortSource,"}\n\n");

		}
		else if (PubSub == M_PUBLISH)
		{
			// 周期性发送首先需要添加flag标志
			if (getPublishPeriod(pPort) != 0) {
				fprintf(fpPortSource, "\nextern int flagNum%d;\n\n", publish_flags[pPort->getName()]);
			}
			publish_names.push_back(pPort->getName());
			//端口构造函数
			fprintf(fpPortSource,"ECOM::Components::%s::%s(%s *pComponent,int portID,std::string portName,"
				"std::string portType,std::string portModifier){\n",
				pPort->getName().c_str(),pPort->getName().c_str(),m_sName.c_str());
			fprintf(fpPortSource,"\tthis->pComponent = pComponent;\n");
			fprintf(fpPortSource,"\tthis->portID = portID;\n");
			fprintf(fpPortSource,"\tthis->portName = portName;\n");
			fprintf(fpPortSource,"\tthis->portType = portType;\n");
			fprintf(fpPortSource,"\tthis->portModifier = portModifier;\n");
			//fprintf(fpPortSource,"\tthis->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpPortSource,"\tthis->participant = this->pComponent->participant;\n");
			fprintf(fpPortSource,"\tthis->topic_name = \"%s\";\n\n",pPort->getPortEntity()->getName().c_str());
			fprintf(fpPortSource,"\t/* To customize publisher Qos, use participant->get_default_publisher_qos() instead */\n");
			fprintf(fpPortSource,"\tthis->publisher = this->participant->create_publisher(DDS_PUBLISHER_QOS_DEFAULT, NULL/*listener*/, DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpPortSource,"\t/* Register type before creating topic */\n");
			fprintf(fpPortSource,"\tthis->type_name = %sTypeSupport::get_type_name();\n\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\t%sTypeSupport::register_type(this->participant, type_name);\n\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\t/* To customize topic QoS, use participant->get_default_topic_qos() instead */\n");
			//find_topic 没有则创建，已存在则使用
			fprintf(fpPortSource,"\tDDS_Duration_t t = {0,10000};\n");
			fprintf(fpPortSource,"\tthis->topic = this->participant->find_topic(this->topic_name,t);\n");
			fprintf(fpPortSource,"\tif(this->topic == NULL)\n");
			fprintf(fpPortSource,"\t{\n\t\tthis->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);\n");
			fprintf(fpPortSource,"\t}\n");
			//fprintf(fpPortSource,"\tthis->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);\n\n");
			fprintf(fpPortSource,"\t/* To customize data writer QoS, use publisher->get_default_datawriter_qos() instead */\n");
			fprintf(fpPortSource,"\tthis->writer = publisher->create_datawriter(topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);\n");
			fprintf(fpPortSource,"\tthis->%s_writer = %sDataWriter::narrow(writer);\n\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),
					pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\t/* Create data sample for writing */\n");
			fprintf(fpPortSource,"\tthis->instance = %sTypeSupport::create_data();\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\tthis->instance_handle = DDS_HANDLE_NIL;\n");
			fprintf(fpPortSource,"}\n");
			//端口Publish函数
			fprintf(fpPortSource,"DDS_ReturnCode_t ECOM::Components::%s::Publish(){\n",pPort->getName().c_str());
			fprintf(fpPortSource,"\tDDS_ReturnCode_t retcode = %s_writer->write(*instance, instance_handle);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\treturn retcode;\n");
			fprintf(fpPortSource,"}\n\n");
			//增加SetMessage函数 by CJ
			fprintf(fpPortSource,"void ECOM::Components::%s::SetMessage(%s& Megs)\n",pPort->getName().c_str(),pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"{\n");
			fprintf(fpPortSource,"\tmLock.lock();\n");
			fprintf(fpPortSource,"\t%s_copy(instance,&Megs);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
			fprintf(fpPortSource,"\tDDS_ReturnCode_t retcode = this->Publish();\n");
			fprintf(fpPortSource,"\tif (retcode != DDS_RETCODE_OK)\n");
			fprintf(fpPortSource,"\t{\n");
			fprintf(fpPortSource,"\t\tprintf(\"write error %%d\\n\",retcode);\n");
			fprintf(fpPortSource,"\t}\n");
			fprintf(fpPortSource,"\tmLock.unlock();\n");
			fprintf(fpPortSource,"}\n");
			//端口SendMegs函数
			fprintf(fpPortSource,"/***********************************************\n");
			fprintf(fpPortSource,"*%s端口的数据发送函数，调用端口内的Publish()即可\n",pPort->getName().c_str());
			fprintf(fpPortSource,"***********************************************/\n");
			// 使用周期性发送端口，需要手动添加joinThread函数，并修改sendMegs函数
			if (getPublishPeriod(pPort) != 0) {
				periodic_joinThread(fpPortSource, getPublishPeriod(pPort), publish_flags[pPort->getName()]);
				periodic_sendMegs(fpPortSource, pPort->getName().c_str(), pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(), publish_flags[pPort->getName()]);
			}
			else {
				fprintf(fpPortSource,"void ECOM::Components::%s::%sSendMegs()\n",pPort->getName().c_str(),pPort->getName().c_str());
				fprintf(fpPortSource,"{\n");
				fprintf(fpPortSource,"\tif (pComponent->status==ECOM::Base::Activated)\n");
				fprintf(fpPortSource,"\t{\n");
				fprintf(fpPortSource,"\t/***********************************************\n");
				fprintf(fpPortSource,"\t*TODO: put your logic business code here\n");
				fprintf(fpPortSource,"\t***********************************************/\n");
				fprintf(fpPortSource,"\n\n\n");
				fprintf(fpPortSource,"\t}\n");
				fprintf(fpPortSource,"}\n\n");
			}


		}
		fclose(fpPortSource);
	}

	// 如果有周期性发送端口，需要添加sendMegs函数
	if (flagNum != 1)
		periodic_sendMegs(fpSource, m_sName.c_str(), publish_names);
	if (recv_periodic_num != 0) {
		;
	}
	//导出的函数为了生成DLL
	if(UI_ServiceFlag == M_SERVICE)
	{
		fprintf(fpSource,"extern \"C\" WIN32_EXPORT SER_INSTANCE CreateComponent(SerLoad *ser)\n{\n");
		fprintf(fpSource,"\tECOM::Components::%s *ret%s = new ECOM::Components::%s(ser);\n",m_sName.c_str(),m_sName.c_str(),m_sName.c_str());
		fprintf(fpSource,"\treturn ret%s;\n",m_sName.c_str());
		fprintf(fpSource,"}\n\n");
	}
	else if(UI_ServiceFlag == M_UI)
	{
		fprintf(fpSource,"extern \"C\" QT_EXPORT UI_INSTANCE CreatePlugin(QWidget *parent,ViewLoad *view)\n");
		fprintf(fpSource,"{\n");
		fprintf(fpSource,"\tECOM::Components::%s *ret%s = new ECOM::Components::%s(parent,view);\n",m_sName.c_str(),m_sName.c_str(),m_sName.c_str());
		fprintf(fpSource,"\treturn ret%s;\n",m_sName.c_str());
		fprintf(fpSource,"}\n\n");  
	}

	////////////////////////////////////////////////HERE///////////////////////////////////////////////////////	
	

	//ComSourceOnDdsEventGeneration(fpSource);//构件cpp中OnMsgEvent函数
	//ComSourceOnDdsEventGeneration(fpSource, 0);
	//构件cpp文件中provide接口中操作方法的写入   需用户自己填写
}
//==>

//debug版本的主函数
//void DebugCodeGeneration(char *CDLFile, char *OutputDirectory)
//{
//	RootDir.assign(OutputDirectory);
//	GetCDLName(CDLFile);
//
//	//得到ECOM_PATH
//	void GetECOMpath();
//	GetECOMpath();
//
//	if (access(RootDir.c_str(), 0) == -1)
//	{  // The Directory is not exist
//		mkdir(RootDir.c_str());
//	}
//	// 在目标路径创建总文件夹 ex：Test_CDL
//	CDLDir = RootDir;
//	CDLDir.append("/");
//	CDLDir += CDLName;
//	CDLDir.append("_CDL");
//	mkdir(CDLDir.c_str());							// Create CDL directory
//
//	//debug文件夹
//	CDLDir.append("/Debug");
//	mkdir(CDLDir.c_str());
//
//	string CDLIncludeDir = CDLDir;
//	CDLIncludeDir.append("/include");
//	string CDLSourcesDir = CDLDir;
//	CDLSourcesDir.append("/sources");
//
//	mkdir(CDLIncludeDir.c_str());					// Create CDL include directory
//	mkdir(CDLSourcesDir.c_str());					// Create CDL sources directory
//
//	string CDLHeaderFile = CDLIncludeDir;
//
//	CDLHeaderFile.append("/").append(CDLName).append(".h");
//	string CDLSourceFile = CDLSourcesDir;
//	CDLSourceFile.append("/").append(CDLName).append(".cpp");
//
//	FILE *fpCDLHeader = fopen(CDLHeaderFile.c_str(), "w");
//	FILE *fpCDLSource = fopen(CDLSourceFile.c_str(), "w");
//
//	fprintf(fpCDLHeader, "#ifndef %s_HEADER\n", CDLName.c_str());
//	fprintf(fpCDLHeader, "#define %s_HEADER\n\n", CDLName.c_str());
//	fprintf(fpCDLHeader, "#include \"%s\\Debug\\ECOM.h\"\n\n",EcomPath.c_str());
//	fprintf(fpCDLHeader, "#include <vector>\n");
//
//	//lian add
//	fprintf(fpCDLHeader, "#include <fstream>\n");
//	fprintf(fpCDLHeader, "#include <sstream>\n\n");
//
//	fprintf(fpCDLSource, "#include \"..\\\\include\\\\%s.h\"\n\n", CDLName.c_str());
//
//	cdl_file.GenerateBasicEntity(fpCDLHeader, fpCDLSource, fpIDL);
//
//	fprintf(fpCDLHeader, "#endif"); // Should be output at the end of header file
//
//	fclose(fpCDLHeader);
//	fclose(fpCDLSource);
//
//	// and then generating components
//
//	string ComDir = RootDir;
//	ComDir.append("/");
//	ComDir += CDLName;
//	ComDir.append("_CDL/Debug/Component");
//	mkdir(ComDir.c_str());
//
//	/*	string ComIncludeDir = ComDir;
//	ComIncludeDir.append("/include");
//	mkdir(ComIncludeDir.c_str());
//	string ComSourcesDir = ComDir;
//	ComSourcesDir.append("/sources");
//	mkdir(ComSourcesDir.c_str());
//	*/
//	cdl_file.GenerateComponentEntity(ComDir);
//}

void ReleaseCodeGeneration(char *CDLFile, char *OutputDirectory)
{
	RootDir.assign(OutputDirectory);
	GetCDLName(CDLFile);

	if (access(RootDir.c_str(), 0) == -1)
	{  // The Directory is not exist
		mkdir(RootDir.c_str());
	}

	CDLDir = RootDir;
	if (OutputDirectory[strlen(OutputDirectory)-1] != '/')
		CDLDir.append("/");
	CDLDir += CDLName;
	CDLDir.append("_CDL");
	CDLDir.append(getTime().c_str());
	strcpy(OutputDirectory, CDLDir.c_str());
	mkdir(CDLDir.c_str());							// Create CDL directory




	//release文件夹
	//CDLDir.append("/Release");
	mkdir(CDLDir.c_str());

	string CDLIncludeDir = CDLDir;
	CDLIncludeDir.append("/include");
	string CDLSourcesDir = CDLDir;
	CDLSourcesDir.append("/sources");
	
	string CDLbinDir = CDLDir;
	CDLbinDir.append("/bin");
	string CDLbinDebugDir = CDLbinDir;
	string CDLbinReleaseDir = CDLbinDir;
	CDLbinDebugDir.append("/Debug");
	CDLbinReleaseDir.append("/Release");

	mkdir(CDLIncludeDir.c_str());					// Create CDL include directory
	mkdir(CDLSourcesDir.c_str());					// Create CDL sources directory
	mkdir(CDLbinDir.c_str());
	mkdir(CDLbinDebugDir.c_str());						// Create CDL bin directory
	mkdir(CDLbinReleaseDir.c_str());
	string CDLHeaderFile = CDLIncludeDir;

	CDLHeaderFile.append("/").append(CDLName).append(".h");
	string CDLSourceFile = CDLSourcesDir;
	CDLSourceFile.append("/").append(CDLName).append(".cpp");

	FILE *fpCDLHeader = fopen(CDLHeaderFile.c_str(), "w");
	FILE *fpCDLSource = fopen(CDLSourceFile.c_str(), "w");

	fprintf(fpCDLHeader, "#ifndef %s_HEADER\n", CDLName.c_str());
	fprintf(fpCDLHeader, "#define %s_HEADER\n\n", CDLName.c_str());
	fprintf(fpCDLHeader, "#include \"../IDLGenerate/%sIDL.h\"\n", CDLName.c_str());
	fprintf(fpCDLHeader, "#include \"../IDLGenerate/%sIDLSupport.h\"\n", CDLName.c_str());
	fprintf(fpCDLHeader, "#include \"ndds/ndds_requestreply_cpp.h\"\n\n");

	//fprintf(fpCDLSource, "char *globalContent;\n\n");
	fprintf(fpCDLSource, "#include \"..\\\\include\\\\%s.h\"\n\n", CDLName.c_str());
	//fprintf(fpCDLSource, "boost::mutex mutextemp;\n");
//---------------------------------------------DJC modified------------------------------------
//---------------------------------------------DJC modified------------------------------------
//---------------------------------------------DJC modified------------------------------------
//---------------------------------------------DJC modified------------------------------------
	//generate idl
	string IDLFlie = CDLDir;
	IDLFlie.append("/").append(CDLName).append("IDL.idl");
	FILE *fpIDL = fopen(IDLFlie.c_str(), "w");

	//cdl文件除了构件另外实体的c++代码和idl
	cdl_file.GenerateBasicEntity(fpCDLHeader, fpCDLSource,fpIDL);




//---------------------------------------------DJC modified--------------------------------------
//---------------------------------------------DJC modified--------------------------------------
//---------------------------------------------DJC modified--------------------------------------
//---------------------------------------------DJC modified--------------------------------------
//---------------------------------------------DJC modified--------------------------------------
	
	//cdl_file.GenerateBasicEntity(fpCDLHeader, fpCDLSource, fpIDL);

	fprintf(fpCDLHeader, "#endif"); // Should be output at the end of header file
	fclose(fpCDLHeader);
	fclose(fpCDLSource);
	fclose(fpIDL);
	
	//把cdl从项目外复制到项目中
	string SnapCDLinPath = RootDir;
	string SnapCDLoutPath = CDLDir;
	vector<string> CDLFileNameList;
	intptr_t Snap_hFile = 0;
	struct _finddata_t SnapFileInfo;
	string SnapP;
	if((Snap_hFile = _findfirst(SnapP.assign(SnapCDLinPath).append("\\*.cdl").c_str() , &SnapFileInfo)) != -1)
	{
		do 
		{
			CDLFileNameList.push_back(SnapFileInfo.name);
		} while (_findnext(Snap_hFile , &SnapFileInfo) == 0);
		_findclose(Snap_hFile);
	}
	for(int SnapI = 0 ; SnapI < CDLFileNameList.size() ; SnapI++)
	{
		string SnapCDLinPathName = SnapCDLinPath + "\\" + CDLFileNameList[SnapI];
		string SnapCDLoutPathName = SnapCDLoutPath + "\\" + CDLFileNameList[SnapI];
		// ZLC MODIFIED
		// CString CSnapCDLinPathName(SnapCDLinPathName.c_str());
		// CString CSnapCDLoutPathName(SnapCDLoutPathName.c_str());
		// CopyFile(CSnapCDLinPathName, CSnapCDLoutPathName,TRUE);
		copyFile(SnapCDLinPathName, SnapCDLoutPathName);
		// ZLC MODIFIED END
	}
	//复制结束


	//将IDL生成C++代码
	string batFile = RootDir;
	//CDLDir.append("/");
	//batFile += CDLName;
	//batFile.append("_batTemp");
	//if (access(batFile.c_str(), 0) == -1)
	//{  // The Directory is not exist
	//	mkdir(batFile.c_str());
	//}
	batFile.append("/").append(CDLName).append(".bat");

	string LogFlie = CDLDir;
	LogFlie.append("/").append(CDLName).append(".bat");
	FILE *fpLog = fopen(LogFlie.c_str(), "w");
	FILE *fpbatTemp = fopen(batFile.c_str(), "w");
	//generate idl file to C++
	string IDLGenerateDir = CDLDir;
	IDLGenerateDir.append("/IDLGenerate");
	mkdir(IDLGenerateDir.c_str());
	char* nddshome = getenv("NDDSHOME");

	string nddshomes = nddshome;
	
	string command = "CALL \"" + nddshomes;

	command += "/bin/rtiddsgen\" "+ IDLFlie;
	command += " -ppDisable -d ";
	/*fpLog = fopen(LogFlie.c_str(), "w");
	fprintf(fpLog, command.c_str());
	fclose(fpLog);*/
	command +=IDLGenerateDir;
	command +=  " -language C++ -create typefiles -replace"; 
	////控制台打印command命令
	//printf("%s\n",command.c_str());
	fprintf(fpLog, command.c_str());
	fprintf(fpbatTemp, command.c_str());
	fclose(fpLog);
	fclose(fpbatTemp);
	WinExec(LogFlie.c_str(),SW_HIDE);

	//if(system(command.c_str()) == -1)
	//{
	//	fprintf(fpLog, command.c_str());
	//	fclose(fpLog);
	//}

	/*fpLog = fopen(LogFlie.c_str(), "w");
	fprintf(fpLog, command.c_str());
	fclose(fpLog);*/

	// and then generating components path

	string ComDir = CDLDir;
	/*ComDir.append("/");
	ComDir += CDLName;
	ComDir.append("_CDL/Component");*/
	ComDir.append("/Component");
	mkdir(ComDir.c_str());

	/*	string ComIncludeDir = ComDir;
	ComIncludeDir.append("/include");
	mkdir(ComIncludeDir.c_str());
	string ComSourcesDir = ComDir;
	ComSourcesDir.append("/sources");
	mkdir(ComSourcesDir.c_str());
	*/

	//生成component实体的代码
	cdl_file.GenerateComponentEntity(ComDir);

}
void CodeGeneration(char *CDLFile, char *OutputDirectory)
{
	
	//DebugCodeGeneration(CDLFile, OutputDirectory);
	Now_Gen_Test = false;
	ReleaseCodeGeneration(CDLFile, OutputDirectory);

}

void ProGeneration(string rootDir)
{
	QtCreateUtil qtCreateUtil;
	vector<CDLEntity *> cdlEntity = cdl_file.GetCDLEntityList();
	vector<CDLEntity *>::iterator it;
	for (it = cdlEntity.begin(); it != cdlEntity.end(); ++it)
	{
		CDLEntity *pEntity = *it;
		int EntityType = pEntity->getType();
		if (EntityType == T_COMPONENT)
		{
			ComponentEntity *pCom = (ComponentEntity *)pEntity;
			// 获取组件的端口和接口列表，并初始化一个列表
			vector<string> listInterfacePort;
			vector <ComponentInterfaceDesc *>::const_iterator inf;
			vector <ComponentInterfaceDesc *> infs(pCom->GetInterfaceList());
			for (inf = infs.begin(); inf != infs.end(); ++inf)
			{
				listInterfacePort.push_back((*inf)->getName());
			}
			vector <ComponentPortDesc *>::iterator it1;
			for (it1 = pCom->m_listPort.begin(); it1 != pCom->m_listPort.end(); ++it1)
			{
				listInterfacePort.push_back((*it1)->getName());
			}
			qtCreateUtil.loadProperties(rootDir, pEntity->getName(), CDLName, pCom->get_UI_ServiceFlag(), listInterfacePort);
			bool istrue = qtCreateUtil.generateProFile();
		}
	}
}

//得到环境变量ECOM_PATH的路径
void GetECOMpath()
{
	char *ecomtemp;
	ecomtemp = getenv("ECOM_PATH");
	string ecompathtemp(ecomtemp);
	EcomPath = ecompathtemp;

}

string getTime(){
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%m%d%H%M%S",localtime(&timep) );
	return tmp;
}