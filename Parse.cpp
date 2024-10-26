#include "Parse.h"
#include <iostream>
int yyerror(char *msg);

int Initialize()
{
	CurrENumEntity = NULL;
	CurrS_UEntity = NULL;
	CurrTreeEntity = NULL;
	CurrPortEntity = NULL;
	CurrInterfaceEntity = NULL;
	CurrOperation = NULL;
	CurrComponentEntity = NULL;

	InComponent = false;

	return 0;
}

int PushCurrPackage(const char * PackageName)
{
	if (PackageName == NULL) return ERR_NULL_POINTER;
	if (CurrPackage.size() == 0) 
	{
		CurrPackage.assign(PackageName); return SUCCESS;
	}
	CurrPackage += "::";
	CurrPackage += string(PackageName);
	return SUCCESS;
}

int PopCurrPackage()
{
	if (CurrPackage.size() == 0) return SUCCESS;

	int pos = CurrPackage.rfind(':');
	if (pos == string::npos)
	{
		CurrPackage.clear(); return SUCCESS;
	}

	CurrPackage.erase(pos-1);

	return SUCCESS;
}

int CreateENumEntity(const char * Name)
{
	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];
		message += "Error: Name of ENum Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message , message.c_str());
		yyerror(c_message);
	}
    CurrENumEntity = new ENumEntity();
	CurrENumEntity->setName(Name);
	CurrENumEntity->setPackageName(CurrPackage);
	CurrENumEntity->setType(T_ENUM);
	cdl_file.AppendCDLEntity(CurrENumEntity);

	return SUCCESS;
}



int CreateVectorEntity(const char * Name)
{
	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];
		message += "Error: Name of Tree Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}
	CurrVectorEntity = new VectorEntity();
	CurrVectorEntity->setName(Name);
	CurrVectorEntity->setPackageName(CurrPackage);
	CurrVectorEntity->setType(T_VECTOR);
	cdl_file.AppendCDLEntity(CurrVectorEntity);

	return SUCCESS;
}


int RecordVectorSimpleType(int FundType, int len)
{
	TypeIndex *pTpIndex = new TypeIndex();

	pTpIndex->m_iType = FundType;
	pTpIndex->m_pTypeDesc = NULL;
	CurrVectorEntity->SetVectorType(pTpIndex);
	CurrVectorEntity->SetLength(len);

	return SUCCESS;
}
int RecordVectorComplexType(const char * TypeName, int len )
{
	int TypeCode;
	string sTypeName(TypeName);

	TypeIndex *pTpIndex = new TypeIndex();

	CDLEntity *pEntity;

	pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message;
		char c_message[255];

		message += "Error: Referenced Type Name ";
		message += sTypeName;
		message += " Not Exist ... ";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
		delete pTpIndex;;

		return ERR_FATAL;
	}

	TypeCode = pEntity->getType();
	if (TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		// Member has invalid type
		string message; char c_message[255];
		message += "Error: Invalid Sequence Type in ";
		message += CurrVectorEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
		delete pTpIndex;
		return ERR_FATAL;
	}

	pTpIndex->m_iType = TypeCode;
	pTpIndex->m_pTypeDesc = pEntity;
	CurrVectorEntity->SetVectorType(pTpIndex);
	CurrVectorEntity->SetLength(len);


	return SUCCESS;
}




int CreateTreeEntity(const char * Name)
{
	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];
		message += "Error: Name of Tree Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}
	CurrTreeEntity = new TreeEntity();
	CurrTreeEntity->setName(Name);
	CurrTreeEntity->setPackageName(CurrPackage);
	CurrTreeEntity->setType(T_TREE);
	cdl_file.AppendCDLEntity(CurrTreeEntity);

	return SUCCESS;
}

int RecordTreeSimpleType(int FundType)
{
	TypeIndex *pTpIndex = new TypeIndex();

	pTpIndex->m_iType = FundType;
	pTpIndex->m_pTypeDesc = NULL;

	CurrTreeEntity->SetTreeType(pTpIndex);

	return SUCCESS;
}

int RecordTreeComplexType(const char * TypeName)
{
	int TypeCode;
	string sTypeName(TypeName);

	TypeIndex *pTpIndex = new TypeIndex();

	CDLEntity *pEntity;

	pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message;
		char c_message[255];

		message += "Error: Referenced Type Name ";
		message += sTypeName;
		message += " Not Exist ... ";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
		delete pTpIndex;;

		return ERR_FATAL;
	}

	TypeCode = pEntity->getType();
	if (TypeCode == T_TREE||TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		// Member has invalid type
		string message; char c_message[255];
		message += "Error: Invalid Tree Type in ";
		message += CurrTreeEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
		delete pTpIndex;
		return ERR_FATAL;
	}

	pTpIndex->m_iType = TypeCode;
	pTpIndex->m_pTypeDesc = pEntity;
	CurrTreeEntity->SetTreeType(pTpIndex);

	return SUCCESS;
}

int AppendValueName(const char * Name)
{
	 int res;
	 res = CurrENumEntity->AppendValueName(Name);
	 if (res == ERR_DUPLICATED_NAME)
	 {
		string message;
		char c_message[255];

		message += "Error: Value Name ";
		message += string(Name);
		message += " in ENum Type of ";
		message += CurrENumEntity->getName();
		message += " Is Duplicated ... ";
		strcpy(c_message , message.c_str());
		yyerror(c_message);
	 }

	 return SUCCESS;
}

int CreateStructEntity(const char *Name)
{
	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];

		message += "Error: Name of Struct Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message , message.c_str());
		yyerror(c_message);
	}
    CurrS_UEntity = new StructEntity();
	CurrS_UEntity->setName(Name);
	CurrS_UEntity->setPackageName(CurrPackage);
	CurrS_UEntity->setType(T_STRUCT);
	cdl_file.AppendCDLEntity(CurrS_UEntity);

	return SUCCESS;
}

int CreateUnionEntity(const char *Name)
{
	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];

		message += "Error: Name of Union Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message , message.c_str());
		yyerror(c_message);
	}
    CurrS_UEntity = new UnionEntity();
	CurrS_UEntity->setName(Name);
	CurrS_UEntity->setPackageName(CurrPackage);
	CurrS_UEntity->setType(T_UNION);
	cdl_file.AppendCDLEntity(CurrS_UEntity);

	return SUCCESS;
}

int AddFundamentalDataMember(int FundType, const char *Name)
{
	DataMember *pDMember = new DataMember();
	TypeIndex *pTpIndex = new TypeIndex();

	pTpIndex->m_iType = FundType;
	pTpIndex->m_pTypeDesc = NULL;

	pDMember->m_pTypeIndex = pTpIndex;

	if (CurrS_UEntity->DuplicatedMemberName(Name))
	{
		string message;
		char c_message[255];

		message += "Error: Member Name ";
		message += Name;

		if (CurrS_UEntity->getType() == T_STRUCT)
		    message += " in Struct Type ";
		else
			message += " in Union Type ";
		message += CurrS_UEntity->getName();
		message += " Is Duplicated ...";

		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	pDMember->m_sName.assign(Name);
	CurrS_UEntity->AppendMember(pDMember);

	return SUCCESS;
}

int AddComplexDataMember(const char *TypeName, const char *MemberName)
{
	int TypeCode;
	string sTypeName(TypeName);

	DataMember *pDMember = new DataMember();
	TypeIndex *pTpIndex = new TypeIndex();

	CDLEntity *pEntity;

	pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message;
		char c_message[255];

		message += "Error: Referenced Type Name ";
		message += sTypeName;
		message += " Not Exist ... ";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
		delete pDMember;
		delete pTpIndex;;

		return ERR_FATAL;
	}

	TypeCode = pEntity->getType();
	if (  TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT||TypeCode==T_TREE)
	{
		// Member has invalid type
		string message; char c_message[255];
		message += "Error: Invalid Type of Data Member in ";
		message += CurrS_UEntity->getName();
		message += " of Member ";
		message += string(MemberName);
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
		delete pDMember;
		delete pTpIndex;
		return ERR_FATAL;
	}

	pTpIndex->m_iType = TypeCode;
	pTpIndex->m_pTypeDesc = pEntity;

	pDMember->m_pTypeIndex = pTpIndex;

	if (CurrS_UEntity->DuplicatedMemberName(MemberName))
	{
		string message;
		char c_message[255];

		message += "Error: Member Name ";
		message += MemberName;

		if (CurrS_UEntity->getType() == T_STRUCT)
		    message += " in Struct Type ";
		else
			message += " in Union Type ";
		message += CurrS_UEntity->getName();
		message += " Is Duplicated ...";

		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	pDMember->m_sName.assign(MemberName);
	CurrS_UEntity->AppendMember(pDMember);

	return SUCCESS;
}

int CreatePortEntity(const char *Name)
{
	//一个端口类型只能存在一个, 检查防止重复创建
	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];

		message += "Error: Name of Port Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message , message.c_str());
		yyerror(c_message);
	}
    CurrPortEntity = new PortEntity();
	CurrPortEntity->setName(Name);
	CurrPortEntity->setPackageName(CurrPackage);
	CurrPortEntity->setType(T_PORT);
	cdl_file.AppendCDLEntity(CurrPortEntity);

	return SUCCESS;
}

int RecordPortSimpleType(int type)
{
	TypeIndex *pTpIndex = new TypeIndex();

	pTpIndex->m_iType = type;
	//lian add 
	FundmemtalEntity *fundType = new FundmemtalEntity();
	//fundType->setName
	switch (type)
	{
	case T_SHORT:
		//fprintf(fpHeader, "short ");
		fundType->setName("short");
		break;
	case T_UNSINGED_SHORT:
		//fprintf(fpHeader, "unsigned short ");
		fundType->setName("unsigned short");
		break;
	case T_LONG:
		//fprintf(fpHeader, "int ");
		fundType->setName("int");
		break;
	case T_UNSIGNED_LONG:
		//fprintf(fpHeader, "unsigned int ");
		fundType->setName("unsigned int");
		break;
	case T_LONG_LONG:
		//fprintf(fpHeader, "long ");
		fundType->setName("long");
		break;
	case T_UNSIGNED_LONG_LONG:
		//fprintf(fpHeader, "unsigned long ");
		fundType->setName("unsigned long");
		break;
	case T_FLOAT:
		//fprintf(fpHeader, "float ");
		fundType->setName("float");
		break;
	case T_DOUBLE:
		//fprintf(fpHeader, "double ");
		fundType->setName("double");
		break;
	case T_CHAR:
		//fprintf(fpHeader, "char ");
		fundType->setName("char");		
		break;
	case T_BOOLEAN:
		//fprintf(fpHeader, "bool ");
		fundType->setName("bool");	
		break;
	case T_OCTET:
		//fprintf(fpHeader, "char ");
		fundType->setName("char");	
		break;
	case T_STRING:
		// Deal with later
		//fprintf(fpHeader, "std::string ");
		fundType->setName("std::string");	
		break;
	case T_VOID:
		fundType->setName("void");		
		break;
	}
	pTpIndex->m_pTypeDesc = fundType;
	//pTpIndex->m_pTypeDesc = NULL;
	CurrPortEntity->setTypeIndex(pTpIndex);

	return SUCCESS;
}

int RecordPortComplexType(const char *Name)
{
	CDLEntity *pEntity;
	string sTypeName(Name);

	pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message;
		char c_message[255];

		message += "Error: Referenced Type Name ";
		message += sTypeName;
		message += " Not Exist in Port ";
		message += CurrPortEntity->getName();
		message += "'s Declaration ... ";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		return ERR_FATAL;
	}
	int TypeCode = pEntity->getType();
	if (  TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		// Member has invalid type
		string message; char c_message[255];
		message += "Error: Invalid Type Referenced by Port ";
		message += CurrPortEntity->getName();
		message += " ....";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		return ERR_FATAL;
	}

	TypeIndex *pTpIndex = new TypeIndex();
	pTpIndex->m_iType = TypeCode;;
	pTpIndex->m_pTypeDesc = pEntity;

	CurrPortEntity->setTypeIndex(pTpIndex);

	return SUCCESS;
}




int LoadPortDataRange(const char *Range)
{
	if (Range[0] == '\0')
	{

		return SUCCESS;
	}
	else
	{
		if (CurrPortEntity->RangeFormatCheck(Range) == ERR_FATAL)
		{
			string message;
			char c_message[255];

			message += "Error: Wrong Range Format ";
			message += " in Port ";
			message += CurrPortEntity->getName();
			message += "'s Declaration ... ";
			strcpy(c_message, message.c_str());
			yyerror(c_message);
			return ERR_FATAL;
		}
		else
		{

			TypeIndex *pTpIndex = CurrPortEntity->getTypeIndex();
			//简单数据类型
			if (pTpIndex->m_pTypeDesc == NULL)
			{
				string lower, upper;
				string strtemp(Range);
				size_t pos1 = strtemp.find('[');
				size_t pos2 = strtemp.find(',');
				size_t pos3 = strtemp.find(']');

				BasicRange *pBasicRange = new BasicRange();
				pBasicRange->rangeType = Basic;
				pBasicRange->lower = strtemp.substr(pos1 + 1, pos2 - pos1 - 1);
				pBasicRange->upper = strtemp.substr(pos2 + 1, pos3 - pos2 - 1);

				if (CurrPortEntity->BasicRangeCheck(CurrPortEntity->getTypeIndex()->m_iType, pBasicRange) == SUCCESS)
				{
					CurrPortEntity->valueRange.push_back(pBasicRange);
				}
				else
				{
					string message; char c_message[255];
					message += "Error: Port RangeValue ";
					message += CurrPortEntity->getName();
					message += "  in Operation ";
					message += " ...";
					strcpy(c_message, message.c_str());
					yyerror(c_message);
				}
			}
			//复杂数据类型
			else
			{
				//提供一个e层数和对应的ComplexRange的容器
				map<int, ComplexRange*> mapFloor;
				BasicRange *currBasicRange;
				//在解析字符串时，numFloor代表当前层，numFloor-1为上一层
				int numFloor = 0;
				//表示最基本类型的个数
				int numBasic = 0;
				while (*Range)
				{
					//左括号层数加一
					if (*Range == '(')
					{
						if (++numFloor > 1)
						{
							//将层数和对应的复杂类型放入map
							ComplexRange *pComplexRange = new ComplexRange();
							pComplexRange->rangeType = Complex;
							mapFloor[numFloor] = pComplexRange;
						}
					}
					//右括号表示完成当前层解析，并将填充完的当前层从map中找出，存在外层，并从map中删除当前层，因为当前层已经解析完毕
					if (*Range == ')')
					{
						if (numFloor == 1)
							break;
						map<int, ComplexRange*>::const_iterator it = mapFloor.find(numFloor);
						if ((numFloor - 1) == 1)
							CurrPortEntity->valueRange.push_back(it->second);
						else
							(mapFloor.find(numFloor - 1))->second->m_listRange.push_back(it->second);

						mapFloor.erase(mapFloor.find(numFloor));
						numFloor--;
					}
					//在（）之间解析当前层内容，并填充当前层的vector
					if (*Range == '[')
					{
						string strTemp = "";
						while (*(++Range) != ',')
							strTemp.append(1, *Range);

						currBasicRange = new BasicRange();
						currBasicRange->rangeType = Basic;
						currBasicRange->lower = strTemp;
						strTemp.clear();
						while (*(++Range) != ']')
							strTemp.append(1, *Range);
						currBasicRange->upper = strTemp;
						++numBasic;

						//先检查range和对应的类型是否匹配，若匹配再添加
						if (CurrPortEntity->ComplexRangeCheck(CurrPortEntity->getTypeIndex()->m_iType, currBasicRange, numBasic) == SUCCESS)
						{
							if (numFloor == 1)
								CurrPortEntity->valueRange.push_back(currBasicRange);
							else
							{
								//找出当前层并填充
								map<int, ComplexRange*>::iterator it = mapFloor.find(numFloor);
								it->second->m_listRange.push_back(currBasicRange);
							}
						}
						else
						{
							string message; char c_message[255];
							message += "Error: Port RangeValue ";
							message += CurrPortEntity->getName();
							message += "  in Operation ";
							message += " ...";
							strcpy(c_message, message.c_str());
							yyerror(c_message);
						}

					}
					Range++;
				}

			}
			return SUCCESS;
		}

	}
}

int CreateInterfaceEntity(const char *Name)
{
//	if (CreateInterfaceEntity) return SUCCESS;

	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];

		message += "Error: Name of Interface Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message , message.c_str());
		yyerror(c_message);
	}
    CurrInterfaceEntity = new InterfaceEntity();
	CurrInterfaceEntity->setName(Name);
	CurrInterfaceEntity->setPackageName(CurrPackage);
	CurrInterfaceEntity->setType(T_INTERFACE);
	cdl_file.AppendCDLEntity(CurrInterfaceEntity);

	return SUCCESS;
}

OperationDesc* CreateOperation(int OneWayOption)
{
	CurrOperation = new OperationDesc();
	CurrOperation->setOneWayOption(OneWayOption);

	return CurrOperation;
}

TypeIndex *CreateTypeIndex(const char *EntityName)
{
	CDLEntity *pEntity;
	string sTypeName(EntityName);

	pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message;
		char c_message[255];

		message += "Error: Referenced Type Name ";
		message += sTypeName;
		message += " Not Exist .... ";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		return NULL;
	}
	int TypeCode = pEntity->getType();
/*
if (  TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		// Member has invalid type
		string message; char c_message[255];
		message += "Error: Invalid Type Referenc  ";
		message += sTypeName;
		message += " ....";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		return NULL;
	}
*/
	TypeIndex *pTpIndex = new TypeIndex();
	pTpIndex->m_iType = TypeCode;;
	pTpIndex->m_pTypeDesc = pEntity;

	return pTpIndex;
}

int SetOperationName(const char *Name)
{
	CurrOperation->setName(Name);
	return SUCCESS;
}



int AddOperation(OperationDesc *pOperation)
{
    string OperationName=pOperation->getName();
	if (CurrInterfaceEntity->DuplicatedOperationName(OperationName))
	{
		string message; char c_message[255];
		message += "Error: Operation Name ";
		message += OperationName;
		message += " in Interface ";
		message += CurrInterfaceEntity->getName();
		message += " Is Duplicated ... ";

		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}
	CurrInterfaceEntity->AppendOperation(CurrOperation);
	return SUCCESS;
}

int AppendParameter(int Direction, TypeIndex *tp, const char *Name,const char *ParameterDataRange)
{
	OpParamDesc *pParam; int TypeCode;
	string ParamName(Name);
	if (CurrOperation->DuplicatedParamName(ParamName))
	{
		//InComponent为false说明是interface中的方法
		if (InComponent == false)
		{
			string message; char c_message[255];
			message += "Error: Parameter Name ";
			message += ParamName;
			message += " Duplicated in Operation ";
			message += CurrOperation->getName();
			message += " in Interface ";
			message += CurrInterfaceEntity->getName();
			message += " ...";
			strcpy(c_message, message.c_str());
			yyerror(c_message);
		}
		//InComponent为true说明是component中的方法
		if (InComponent == true)
		{
			string message; char c_message[255];
			message += "Error: Parameter Name ";
			message += ParamName;
			message += " Duplicated in Operation ";
			message += CurrOperation->getName();
			message += " in Component ";
			message += CurrComponentEntity->getName();
			message += " ...";
			strcpy(c_message, message.c_str());
			yyerror(c_message);
		}
	}

	TypeCode = tp->m_iType;
	if (  TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		if(InComponent ==false)
		{
			string message; char c_message[255];
			message += "Error: Invalid Parameter Type of ";
			message += ParamName;
			message += " in Operation ";
			message += CurrOperation->getName();
			message += " in Interface ";
			message += CurrInterfaceEntity->getName();
			message += " ...";
			strcpy(c_message, message.c_str());
			yyerror(c_message);
		}
		if (InComponent == true)
		{
			string message; char c_message[255];
			message += "Error: Invalid Parameter Type of ";
			message += ParamName;
			message += " in Operation ";
			message += CurrOperation->getName();
			message += " in Component ";
			message += CurrComponentEntity->getName();
			message += " ...";
			strcpy(c_message, message.c_str());
			yyerror(c_message);
		}
		
	}

	pParam = new OpParamDesc();
	pParam->setDirection(Direction);
	pParam->setTypeIndex(tp);
	pParam->setName(ParamName);


	//增加对参数范围的处理
	//先对range的格式进行判断
	if (ParameterDataRange[0] == '\0')
	{
		CurrOperation->AppendParam(pParam);
		return SUCCESS;
	}
	else
	{
		if (pParam->RangeFormatCheck(ParameterDataRange) == ERR_FATAL)
		{
			if (InComponent == false)
			{
				string message; char c_message[255];
				message += "Error: Invalid Parameter Range Format ";
				message += ParamName;
				message += "  in Operation ";
				message += CurrOperation->getName();
				message += " in Interface ";
				message += CurrInterfaceEntity->getName();
				message += " ...";
				strcpy(c_message, message.c_str());
				yyerror(c_message);
				return ERR_FATAL;
			}

			if (InComponent == true)
			{
				string message; char c_message[255];
				message += "Error:Invalid Parameter Range Format ";
				message += ParamName;
				message += "  in Operation ";
				message += CurrOperation->getName();
				message += " in Component ";
				message += CurrComponentEntity->getName();
				message += " ...";
				strcpy(c_message, message.c_str());
				yyerror(c_message);
				return ERR_FATAL;
			}
		}
		else
		{
			//简单数据类型
			if (tp->m_pTypeDesc == NULL)
			{
				string lower, upper;
				string strtemp(ParameterDataRange);
				size_t pos1 = strtemp.find('[');
				size_t pos2 = strtemp.find(',');
				size_t pos3 = strtemp.find(']');

				BasicRange *pBasicRange = new BasicRange();
				pBasicRange->rangeType = Basic;
				pBasicRange->lower = strtemp.substr(pos1 + 1, pos2 - pos1 - 1);
				pBasicRange->upper = strtemp.substr(pos2 + 1, pos3 - pos2 - 1);
				//进行范围内容的检查
				if (pParam->BasicRangeCheck(pParam->getTypeIndex()->m_iType, pBasicRange) == SUCCESS)
				{
					pParam->valueRange.push_back(pBasicRange);
				}
				else
				{
					if (InComponent == false)
					{
						string message; char c_message[255];
						message += "Error:Invalid Parameter RangeValue ";
						message += ParamName;
						message += "  in Operation ";
						message += CurrOperation->getName();
						message += " in Interface ";
						message += CurrInterfaceEntity->getName();
						message += " ...";
						strcpy(c_message, message.c_str());
						yyerror(c_message);
					}
					if (InComponent == true)
					{
						string message; char c_message[255];
						message += "Error:Invalid Parameter RangeValue ";
						message += ParamName;
						message += "  in Operation ";
						message += CurrOperation->getName();
						message += " in Component ";
						message += CurrComponentEntity->getName();
						message += " ...";
						strcpy(c_message, message.c_str());
						yyerror(c_message);
					}
					
				}
			}
			//复杂数据类型
			else
			{
				//提供一个层数和对应的ComplexRange的容器
				map<int, ComplexRange*> mapFloor;
				BasicRange *currBasicRange;
				//在解析字符串时，numFloor代表当前层，numFloor-1为上一层
				int numFloor = 0;
				int numBasic = 0;
				while (*ParameterDataRange)
				{
					//左括号层数加一
					if (*ParameterDataRange == '(')
					{
						if (++numFloor > 1)
						{
							//将层数和对应的复杂类型放入map
							ComplexRange *pComplexRange = new ComplexRange();
							pComplexRange->rangeType = Complex;
							mapFloor[numFloor] = pComplexRange;
						}
					}
					//右括号表示完成当前层解析，并将填充完的当前层从map中找出，存在外层，并从map中删除当前层，因为当前层已经解析完毕
					if (*ParameterDataRange == ')')
					{
						if (numFloor == 1)
							break;
						map<int, ComplexRange*>::const_iterator it = mapFloor.find(numFloor);
						if ((numFloor - 1) == 1)
							pParam->valueRange.push_back(it->second);
						else
							(mapFloor.find(numFloor - 1))->second->m_listRange.push_back(it->second);
						mapFloor.erase(mapFloor.find(numFloor));
						numFloor--;
					}
					//在（）之间解析当前层内容，并填充当前层的vector
					if (*ParameterDataRange == '[')
					{
						string strTemp = "";
						while (*(++ParameterDataRange) != ',')
							strTemp.append(1, *ParameterDataRange);

						currBasicRange = new BasicRange();
						currBasicRange->rangeType = Basic;
						currBasicRange->lower = strTemp;

						strTemp.clear();
						while (*(++ParameterDataRange) != ']')
							strTemp.append(1, *ParameterDataRange);
						currBasicRange->upper = strTemp;
						++numBasic;

						if (pParam->ComplexRangeCheck(pParam->getTypeIndex()->m_iType, currBasicRange, numBasic) == SUCCESS)
						{
							if (numFloor == 1)
								pParam->valueRange.push_back(currBasicRange);
							else
							{
								//找出当前层并填充
								map<int, ComplexRange*>::iterator it = mapFloor.find(numFloor);
								it->second->m_listRange.push_back(currBasicRange);
							}
						}
						else
						{
							if (InComponent == false)
							{
								string message; char c_message[255];
								message += "Error:Invalid Parameter RangeValue ";
								message += ParamName;
								message += "  in Operation ";
								message += CurrOperation->getName();
								message += " in Interface ";
								message += CurrInterfaceEntity->getName();
								message += " ...";
								strcpy(c_message, message.c_str());
								yyerror(c_message);
							}
							if (InComponent ==true)
							{
								string message; char c_message[255];
								message += "Error:Invalid Parameter RangeValue ";
								message += ParamName;
								message += "  in Operation ";
								message += CurrOperation->getName();
								message += " in Component ";
								message += CurrComponentEntity->getName();
								message += " ...";
								strcpy(c_message, message.c_str());
								yyerror(c_message);
							}
							
						}
					}
					ParameterDataRange++;
				}

			}
			CurrOperation->AppendParam(pParam);
			return SUCCESS;
		}
	}
	
}

int SetOperationReturnType(TypeIndex *tp)
{
	CurrOperation->setReturnType(tp);
	int TypeCode = tp->m_iType;
	if (TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		string message; char c_message[255];
		message += "Error: Invalid Return Type of ";
		message += tp->m_pTypeDesc->getName();
		message += " in Operation ";
		message += CurrOperation->getName();
		message += " in Interface ";
		message += CurrInterfaceEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	return SUCCESS;
}

int CreateComponentEntity(const char *Name)
{
	if (cdl_file.DuplicatedCDLEntity(Name))
	{
		string message;
		char c_message[255];

		message += "Error: Name of Component Type ";
		message += string(Name);
		message += " Is Duplicated ... ";
		strcpy(c_message , message.c_str());
		yyerror(c_message);
	}
    CurrComponentEntity = new ComponentEntity();
	CurrComponentEntity->setName(Name);
	CurrComponentEntity->setPackageName(CurrPackage);
	CurrComponentEntity->setType(T_COMPONENT);

	InterfaceEntity *pInterface = new InterfaceEntity();
	pInterface->setName("DefaultInterEntity");
	pInterface->setPackageName(CurrPackage);
	pInterface->setType(T_INTERFACE);

	ComponentInterfaceDesc *temp = new ComponentInterfaceDesc();
	temp->setName("DefaultComInterface");
	temp->setIsLocal(M_NON_LOCAL);
	temp->setRole(M_PROVIDE);
	temp->setInterfaceEntity(pInterface);
	CurrComponentEntity->set_pDefaultInterface(temp);

	cdl_file.AppendCDLEntity(CurrComponentEntity);

	return SUCCESS;
}

void setComOpFlag(bool flag)
{
	InComponent = flag;
}
//ui的设置
void setComFlag(int flag)
{
	CurrComponentEntity->set_UI_ServiceFlag(flag);
}

int AddFunToDefaultInterface(OperationDesc *pOperation)
{
	string opName = pOperation->getName();
	string OperationName = pOperation->getName();
	if (CurrComponentEntity->get_pDefaultInterface()->getInterfaceEntity()->DuplicatedOperationName(OperationName))
	{
		string message; char c_message[255];
		message += "Error: Operation Name ";
		message += OperationName;
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " Is Duplicated ... ";

		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}
	CurrComponentEntity->get_pDefaultInterface()->getInterfaceEntity()->AppendOperation(CurrOperation);
	return SUCCESS;

}


/*

int AppendSimpleParam(int Type, const char *Name)
{
	if (CurrComponentEntity->DuplicatedParam(Name))
	{
		string message; char c_message[255];

		message += "Error: Parameter Name ";
		message += string(Name);
		message += " is Duplicated in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	ComponentParamDesc *cp = new ComponentParamDesc();
	cp->setName(Name);
	TypeIndex *tp = new TypeIndex();
	tp->m_iType = Type;
	cp->setType(tp);
	CurrComponentEntity->AppendParam(cp);

	return SUCCESS;
}

int AppendComplexParam(const char *TypeName, const char *ParamName)
{
	if (CurrComponentEntity->DuplicatedParam(ParamName))
	{
		string message; char c_message[255];

		message += "Error: Parmeter Name ";
		message += string(ParamName);
		message += " is Duplicated in Component ";
		message += CurrComponentEntity->getName();
		message += " ....";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	ComponentParamDesc *cp = new ComponentParamDesc();
	cp->setName(ParamName);

	string sTypeName(TypeName);
	CDLEntity *pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message; char c_message[255];
		message += "Error: Type Name ";
		message += sTypeName;
		message += " is Not exist, in Parameter Declaration ";
		message += string(ParamName);
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		delete cp;
		return ERR_FATAL;
	}

	int TypeCode = pEntity->getType();
	if (  TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		string message; char c_message[255];
		message += "Error: Invalid Parameter Type of ";
		message += ParamName;
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	TypeIndex *tp = new TypeIndex();
	tp->m_iType = pEntity->getType();
	tp->m_pTypeDesc =pEntity;

	cp->setType(tp);
	CurrComponentEntity->AppendParam(cp);

	return SUCCESS;

}

int AppendSimpleAttr(int Type, const char *AttrName)
{
	if (CurrComponentEntity->DuplicatedAttr(AttrName))
	{
		string message; char c_message[255];

		message += "Error: Attribute Name ";
		message += string(AttrName);
		message += " is Duplicated in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	ComponentAttrDesc *ca = new ComponentAttrDesc();
	ca->setName(AttrName);
	TypeIndex *tp = new TypeIndex();
	tp->m_iType = Type;
	ca->setType(tp);
	CurrComponentEntity->AppendAttr(ca);

	return SUCCESS;
}

int AppendComplexAttr(const char *TypeName, const char *AttrName)
{
	if (CurrComponentEntity->DuplicatedAttr(AttrName))
	{
		string message; char c_message[255];

		message += "Error: Attribute Name ";
		message += string(AttrName);
		message += " is Duplicated in Component ";
		message += CurrComponentEntity->getName();
		message += " ....";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	ComponentAttrDesc *cp = new ComponentAttrDesc();
	cp->setName(AttrName);

	string sTypeName(TypeName);
	CDLEntity *pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message; char c_message[255];
		message += "Error: Type Name ";
		message += sTypeName;
		message += " is Not exist, in Attribute Declaration ";
		message += string(AttrName);
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		delete cp;
		return ERR_FATAL;
	}

	int TypeCode = pEntity->getType();
	if (  TypeCode == T_PORT || TypeCode == T_INTERFACE || TypeCode == T_COMPONENT)
	{
		string message; char c_message[255];
		message += "Error: Invalid Attribute Type of ";
		message += string(AttrName);
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	TypeIndex *tp = new TypeIndex();
	tp->m_iType = pEntity->getType();
	tp->m_pTypeDesc =pEntity;

	cp->setType(tp);
	CurrComponentEntity->AppendAttr(cp);

	return SUCCESS;
}
*/


int AppendPortDesc(int PubSub, int IsLocal, const char *PortTypeName, const char *PortName)
{
	if (CurrComponentEntity->DuplicatedPort(PortName))
	{
		string message; char c_message[255];

		message += "Error: Port Name ";
		message += string(PortName);
		message += " is Duplicated in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	ComponentPortDesc *cp = new ComponentPortDesc();
	cp->setName(PortName);
	cp->setPubSub(PubSub);
	cp->setIsLocal(IsLocal);

	string sTypeName(PortTypeName);
	CDLEntity *pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message; char c_message[255];
		message += "Error: Type Name ";
		message += sTypeName;
		message += " is Not exist, in Port Declaration ";
		message += string(PortName);
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		delete cp;
		return ERR_FATAL;
	}

	if (pEntity->getType() != T_PORT)
	{
		string message; char c_message[255];
		message += "Error: Type Name ";
		message += sTypeName;
		message += " MUST be Port Type, in Port Declaration ";
		message += string(PortName);
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	cp->setPortEntity((PortEntity *)pEntity);
	CurrComponentEntity->AppendPort(cp);

	return SUCCESS;
}

int AppendInterfaceDesc(int Role, int IsLocal, const char *InterfaceTypeName, const char *InterfaceName)
{
	if (CurrComponentEntity->DuplicatedInterface(InterfaceName))
	{
		string message; char c_message[255];

		message += "Error: Interface Name ";
		message += string(InterfaceName);
		message += " is Duplicated in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	ComponentInterfaceDesc *cp = new ComponentInterfaceDesc();
	cp->setName(InterfaceName);
	cp->setRole(Role);
	cp->setIsLocal(IsLocal);

	string sTypeName(InterfaceTypeName);
	CDLEntity *pEntity = cdl_file.FindEntityIndex(sTypeName);
	if (pEntity == NULL)
	{
		string message; char c_message[255];
		message += "Error: Type Name ";
		message += sTypeName;
		message += " is Not exist, in Interface Declaration ";
		message += string(InterfaceName);
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);

		delete cp;
		return ERR_FATAL;
	}

	if (pEntity->getType() != T_INTERFACE)
	{
		string message; char c_message[255];
		message += "Error: Type Name ";
		message += sTypeName;
		message += " MUST be Interface Type, in Interface Declaration ";
		message += string(InterfaceName);
		message += " in Component ";
		message += CurrComponentEntity->getName();
		message += " ...";
		strcpy(c_message, message.c_str());
		yyerror(c_message);
	}

	cp->setInterfaceEntity((InterfaceEntity *)pEntity);
	CurrComponentEntity->AppendInterface(cp);

	return SUCCESS;
}
