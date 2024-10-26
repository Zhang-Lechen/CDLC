#include "cdl.h"
#include <iostream>
using namespace std;

TypeIndex::TypeIndex()
{
	m_pTypeDesc = NULL;

}

TypeIndex::~TypeIndex()
{
}

DataMember::DataMember()
{
	m_pTypeIndex = NULL;
}

DataMember::~DataMember()
{
	if (m_pTypeIndex != NULL) delete m_pTypeIndex;
}

int CDLEntity::getType()
{
	return m_iType;
}

void CDLEntity::setType(int tp)
{
	m_iType = tp;
};

void CDLEntity::setName(const string Name)
{
	m_sName = Name;
}

int CDLEntity::setName(const char * Name)
{
	if (Name == NULL) return ERR_NULL_POINTER;
	m_sName.assign(Name);
	return SUCCESS;
}

string CDLEntity::getName()
{
	return m_sName;
}

void  CDLEntity::setPackageName(const string Name)
{
	m_sPackagePath = Name;
}

int  CDLEntity::setPackageName(const char *Name)
{
	if (Name == NULL) return ERR_NULL_POINTER;
	m_sPackagePath.assign(Name);
	return SUCCESS;
}

string  CDLEntity::GetQualifiedName()
{
	string resStr;

	resStr = m_sPackagePath;
	resStr += "::" ;
	resStr += m_sName;

	return resStr;
}

bool CDLEntity::MatchQualifiedName(const string Name)
{
	string Str1;

	if (CurrPackage.size() == 0)
		Str1 = Name;
	else
		Str1 = CurrPackage + "::" +Name;

	// Seperate pure name from Str1
	string PureName;
	int pos = Str1.rfind(":");
	if (pos == string::npos) // Not found
	     { PureName = Name; Str1.clear(); }
	else
	     { PureName = Str1.substr(pos+1); Str1.erase(pos-1); }

	pos = Str1.find(m_sPackagePath);
	if (pos == 0 && m_sName == PureName) return true;
	return false;
}

int S_U_Entity::AppendMember(DataMember *Member)
{
	if (Member == NULL) return ERR_NULL_POINTER;

	if (DuplicatedMemberName(Member->m_sName))
		return ERR_DUPLICATED_NAME;

	m_listMember.push_back(Member);

	return SUCCESS;
}

bool S_U_Entity::DuplicatedMemberName(const char *Name)
{
	if (Name == NULL) return true; // Should return false ?
	string sTmpName = Name;
	for (vector <DataMember *>::iterator it = m_listMember.begin(); it != m_listMember.end(); ++it)
	{
		if ((*it)->m_sName == sTmpName) return true;
	}
	return false;
}

bool S_U_Entity::DuplicatedMemberName(const string Name)
{
	for (vector <DataMember *>::iterator it = m_listMember.begin(); it != m_listMember.end(); ++it)
	{
		if ((*it)->m_sName == Name) return true;
	}
	return false;
}
void S_U_Entity::Destroy()
{
	for (vector <DataMember *>::iterator it = m_listMember.begin(); it != m_listMember.end(); ++it)
		delete *it;
}

StructEntity::~StructEntity()
{
	Destroy();
}

UnionEntity::~UnionEntity()
{
	Destroy();
}

int ENumEntity::AppendValueName(const string Name)
{
	if (DuplicatedValueName(Name)) return ERR_DUPLICATED_NAME;
	m_listValueName.push_back(Name);
	return SUCCESS;
}

int ENumEntity::AppendValueName(const char * Name)
{
	string tmpStr;

	if (Name == NULL) return ERR_NULL_POINTER;

	tmpStr = Name;

	if (DuplicatedValueName(tmpStr)) return ERR_DUPLICATED_NAME;
	m_listValueName.push_back(tmpStr);
	return SUCCESS;
}

bool ENumEntity::DuplicatedValueName(const string Name)
{
	for (vector<string>::iterator it = m_listValueName.begin(); it != m_listValueName.end(); ++it)
		if ( *it == Name ) return true;
	return false;
}

void ENumEntity::Destroy()
{}

ENumEntity::~ENumEntity()
{
	Destroy();
}

void VectorEntity::Destory()
{
	if (m_iType != NULL)
	{
		delete m_type;
		m_type = NULL;
	}
}

void VectorEntity::SetLength(int len)
{
	length = len;
}

int VectorEntity::GetLength()
{
	return length;
}
TypeIndex* VectorEntity::GetVectorType()
{
	return m_type;
}
void VectorEntity::SetVectorType(TypeIndex *t)
{
	m_type = t;
}

VectorEntity::~VectorEntity()
{
	Destory();
}
void TreeEntity::Destroy()
{
	if (m_type != NULL)
	{
		delete m_type;
		m_type = NULL;
	}
}

void TreeEntity::SetTreeType(TypeIndex* t)
{
	m_type = t;
}
TypeIndex* TreeEntity::GetTreeType()
{
	return m_type;
}
TreeEntity::~TreeEntity()
{
	Destroy();
}

void PortEntity::setTypeIndex(TypeIndex *typeIndex)
{
	//if (m_DataDesc.m_pTypeDesc != NULL) free(m_DataDesc.m_pTypeDesc);
	m_DataDesc = typeIndex;
}

TypeIndex *PortEntity::getTypeIndex()
{
	return m_DataDesc;
}

PortEntity::PortEntity()
{
	m_DataDesc = NULL ;
}

void PortEntity::Destroy()
{
	if (m_DataDesc != NULL) delete m_DataDesc;
}

PortEntity::~PortEntity()
{
	Destroy();
}


int PortEntity::BasicRangeCheck(int NumType, BasicRange* pBasicRange)
{

	if (NumType == T_STRING)
	{
		if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
		{
			cout << getName() << "STRING类型不匹配" << endl;
			return ERR_FATAL;
		}
	}
	if (NumType == T_CHAR)
	{
		if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
		{
			cout << getName() << "CHAR" << endl;
		}
		return ERR_FATAL;
	}
	return SUCCESS;
}


//由ComplexRangeCheck递归调用
int TypeRecursion(CDLEntity *pCDLEntity,int &num,int numBasic)
{
	if (pCDLEntity->getType() == T_STRUCT)
	{
		StructEntity *pStruct = dynamic_cast<StructEntity*>(pCDLEntity);
		for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
		{
			CDLEntity *pCdl = (*it)->m_pTypeIndex->m_pTypeDesc;
			int TypeNum = (*it)->m_pTypeIndex->m_iType;
			//简单数据类型处理
			if (pCdl == NULL)
			{
				if (++num == numBasic)
				{
					if (TypeNum == T_SHORT) { return T_SHORT; }
					if (TypeNum == T_UNSINGED_SHORT) { return T_UNSINGED_SHORT; }
					if (TypeNum == T_LONG) { return T_LONG; }
					if (TypeNum == T_UNSIGNED_LONG) { return T_UNSIGNED_LONG; }
					if (TypeNum == T_LONG_LONG) { return T_LONG_LONG; }
					if (TypeNum == T_UNSIGNED_LONG_LONG) { return T_UNSIGNED_LONG_LONG; }
					if (TypeNum == T_FLOAT) { return T_FLOAT; }
					if (TypeNum == T_DOUBLE) { return T_DOUBLE; }
					if (TypeNum == T_CHAR) { return T_CHAR; }
					if (TypeNum == T_STRING) { return T_STRING; }
					if (TypeNum == T_OCTET) { return T_OCTET; }
					if (TypeNum == T_BOOLEAN) { return T_BOOLEAN; }
				}
			}
			else
			{
				int temp=TypeRecursion(pCdl,num,numBasic);
				if (num == numBasic)
					return temp;
			}
		}
		//return 0;
	}
	if (pCDLEntity->getType() == T_UNION)
	{
		UnionEntity *pUnion = dynamic_cast<UnionEntity*>(pCDLEntity);
		for (vector <DataMember *>::iterator it = pUnion->get_listmember().begin(); it != pUnion->get_listmember().end(); it++)
		{
			CDLEntity *pCdl = (*it)->m_pTypeIndex->m_pTypeDesc;
			int TypeNum = (*it)->m_pTypeIndex->m_iType;
			//简单数据类型处理
			if (pCdl == NULL)
			{
				if (++num == numBasic)
				{
					if (TypeNum == T_SHORT) { return T_SHORT; }
					if (TypeNum == T_UNSINGED_SHORT) { return T_UNSINGED_SHORT; }
					if (TypeNum == T_LONG) { return T_LONG; }
					if (TypeNum == T_UNSIGNED_LONG) { return T_UNSIGNED_LONG; }
					if (TypeNum == T_LONG_LONG) { return T_LONG_LONG; }
					if (TypeNum == T_UNSIGNED_LONG_LONG) { return T_UNSIGNED_LONG_LONG; }
					if (TypeNum == T_FLOAT) { return T_FLOAT; }
					if (TypeNum == T_DOUBLE) { return T_DOUBLE; }
					if (TypeNum == T_CHAR) { return T_CHAR; }
					if (TypeNum == T_STRING) { return T_STRING; }
					if (TypeNum == T_OCTET) { return T_OCTET; }
					if (TypeNum == T_BOOLEAN) { return T_BOOLEAN; }
				}
			}
			else
			{
				int temp = TypeRecursion(pCdl, num, numBasic);
				if (num == numBasic)
					return temp;
			}
		}
		//return 0;
	}
	if (pCDLEntity->getType() == T_TREE)
	{
		TreeEntity *pTree = dynamic_cast<TreeEntity*>(pCDLEntity);
		CDLEntity *TreeBindType = pTree->GetTreeType()->m_pTypeDesc;
		int TypeNum = pTree->GetTreeType()->m_iType;
		if(TreeBindType==NULL)
		{
			if (++num == numBasic)
			{
				if (TypeNum == T_SHORT) { return T_SHORT; }
				if (TypeNum == T_UNSINGED_SHORT) { return T_UNSINGED_SHORT; }
				if (TypeNum == T_LONG) { return T_LONG; }
				if (TypeNum == T_UNSIGNED_LONG) { return T_UNSIGNED_LONG; }
				if (TypeNum == T_LONG_LONG) { return T_LONG_LONG; }
				if (TypeNum == T_UNSIGNED_LONG_LONG) { return T_UNSIGNED_LONG_LONG; }
				if (TypeNum == T_FLOAT) { return T_FLOAT; }
				if (TypeNum == T_DOUBLE) { return T_DOUBLE; }
				if (TypeNum == T_CHAR) { return T_CHAR; }
				if (TypeNum == T_STRING) { return T_STRING; }
				if (TypeNum == T_OCTET) { return T_OCTET; }
				if (TypeNum == T_BOOLEAN) { return T_BOOLEAN; }
			}
		}
		else
		{ 
			int temp = TypeRecursion(TreeBindType, num, numBasic);
			if (num == numBasic)
				return temp;
		}
	}
	if (pCDLEntity->getType() == T_VECTOR)
	{
		VectorEntity *pVector = dynamic_cast<VectorEntity*>(pCDLEntity);
		CDLEntity *VectorBindType = pVector->GetVectorType()->m_pTypeDesc;
		int TypeNum = pVector->GetVectorType()->m_iType;
		if (VectorBindType == NULL)
		{
			if (++num == numBasic)
			{
				if (TypeNum == T_SHORT) { return T_SHORT; }
				if (TypeNum == T_UNSINGED_SHORT) { return T_UNSINGED_SHORT; }
				if (TypeNum == T_LONG) { return T_LONG; }
				if (TypeNum == T_UNSIGNED_LONG) { return T_UNSIGNED_LONG; }
				if (TypeNum == T_LONG_LONG) { return T_LONG_LONG; }
				if (TypeNum == T_UNSIGNED_LONG_LONG) { return T_UNSIGNED_LONG_LONG; }
				if (TypeNum == T_FLOAT) { return T_FLOAT; }
				if (TypeNum == T_DOUBLE) { return T_DOUBLE; }
				if (TypeNum == T_CHAR) { return T_CHAR; }
				if (TypeNum == T_STRING) { return T_STRING; }
				if (TypeNum == T_OCTET) { return T_OCTET; }
				if (TypeNum == T_BOOLEAN) { return T_BOOLEAN; }
			}
		}
		else
		{
			int temp = TypeRecursion(VectorBindType, num, numBasic);
			if (num == numBasic)
				return temp;
		}
		//return 0;
	}
	if (pCDLEntity->getType() == T_ENUM)
	{
		if (++num == numBasic)
			return T_ENUM;
	}
}

//一参要匹配的数据类型都是基本数据类型，二参存储range表示，散参表示对应port的第n个基本数据类型，递归计数用

int PortEntity::ComplexRangeCheck(int NumType, BasicRange *pBasicRange, int numBasic)
{
	int num = 0;
	//获得port绑定的实体
	CDLEntity *pcdlEntity = m_DataDesc->m_pTypeDesc;
	int TypeNum = pcdlEntity->getType();
	//绑定的struct实体，遍历vector
	if (TypeNum == T_STRUCT)
	{
		StructEntity *pStruct = dynamic_cast<StructEntity*>(pcdlEntity);
		for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
		{
			CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
			int DataType = (*it)->m_pTypeIndex->m_iType;
			//简单数据类型处理
			if (pCdlEntity == NULL)
			{
				//递归遍历所有的基本类型并计数与numBasic比较
				if (++num == numBasic)
				{
					if (DataType == T_STRING)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else {}
							
					}
					if (DataType == T_CHAR)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
						}
					}
					if (DataType == T_BOOLEAN) 
					{ 
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
						}
					}
					if (DataType == T_SHORT) { }
					if (DataType == T_UNSINGED_SHORT) {  }
					if (DataType == T_LONG) {  }
					if (DataType == T_UNSIGNED_LONG) {  }
					if (DataType == T_LONG_LONG) {  }
					if (DataType == T_UNSIGNED_LONG_LONG) {  }
					if (DataType == T_FLOAT) {  }
					if (DataType == T_DOUBLE) { }
					if (DataType == T_OCTET) { }
					
					return SUCCESS;
				}
			}
			else
			{
				int type = TypeRecursion(pCdlEntity, num, numBasic);
				if (type == T_ENUM)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					   return SUCCESS;
				}
				if (type == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_BOOLEAN) {
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_SHORT) {
					return SUCCESS;
				}
				if (type == T_UNSINGED_SHORT) {
					return SUCCESS;
				}
				if (type == T_LONG) {
					return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG) {
					return SUCCESS;
				}
				if (type == T_LONG_LONG) {
					return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG_LONG) {
					return SUCCESS;
				}
				if (type == T_FLOAT) {
					 return SUCCESS;
				}
				if (type == T_DOUBLE) {
					return SUCCESS;
				}
				if (type == T_OCTET) {
					 return SUCCESS;
				}
				

			}
		}
	}
	if (TypeNum == T_UNION)
	{
		UnionEntity *pUnion = dynamic_cast<UnionEntity*>(pcdlEntity);
		for (vector <DataMember *>::iterator it = pUnion->get_listmember().begin(); it != pUnion->get_listmember().end(); it++)
		{
			CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
			int DataType = (*it)->m_pTypeIndex->m_iType;
			//简单数据类型处理
			if (pCdlEntity == NULL)
			{
				//递归遍历所有的基本类型并计数与numBasic比较
				if (++num == numBasic)
				{
					if (DataType == T_STRING)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
						}
					}
					if (DataType == T_CHAR)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout <<getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
						}
					}
					if (DataType == T_BOOLEAN)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
						}
					}
					if (DataType == T_SHORT) { }
					if (DataType == T_UNSINGED_SHORT) {}
					if (DataType == T_LONG) {  }
					if (DataType == T_UNSIGNED_LONG) { }
					if (DataType == T_LONG_LONG) {  }
					if (DataType == T_UNSIGNED_LONG_LONG) { }
					if (DataType == T_FLOAT) { }
					if (DataType == T_DOUBLE) { }
					if (DataType == T_OCTET) {}
					return SUCCESS;
				}
			}
			else
			{
				int type = TypeRecursion(pCdlEntity, num, numBasic);
				if (type == T_ENUM)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout <<  getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
						 return SUCCESS;
				}
				if (type == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_BOOLEAN) {
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_SHORT) {
					 return SUCCESS;
				}
				if (type == T_UNSINGED_SHORT) {
					 return SUCCESS;
				}
				if (type == T_LONG) {
					 return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG) {
					 return SUCCESS;
				}
				if (type == T_LONG_LONG) {
					 return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG_LONG) {
					 return SUCCESS;
				}
				if (type == T_FLOAT) {
					 return SUCCESS;
				}
				if (type == T_DOUBLE) {
					 return SUCCESS;
				}
				if (type == T_OCTET) {
					 return SUCCESS;
				}	
			}
		}
	}
	if (TypeNum == T_TREE)
	{
		TreeEntity *pTree = dynamic_cast<TreeEntity*>(pcdlEntity);
		CDLEntity *pBindType = pTree->GetTreeType()->m_pTypeDesc;
		int BindTypeNum = pTree->GetTreeType()->m_iType;
		if (pBindType == NULL)
		{
			if (++num == numBasic)
			{
				if (BindTypeNum == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout <<  getName() << " "  << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
					}
				}
				if (BindTypeNum == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " "  << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
					}
				}
				if (BindTypeNum == T_SHORT) {  }
				if (BindTypeNum == T_UNSINGED_SHORT) {  }
				if (BindTypeNum == T_LONG) { }
				if (BindTypeNum == T_UNSIGNED_LONG) {  }
				if (BindTypeNum == T_LONG_LONG) {}
				if (BindTypeNum == T_UNSIGNED_LONG_LONG) {  }
				if (BindTypeNum == T_FLOAT) { }
				if (BindTypeNum == T_DOUBLE) {}
				if (BindTypeNum == T_OCTET) {  }
				if (BindTypeNum == T_BOOLEAN) { }
				return SUCCESS;
			}
		}
		else
		{
			int type = TypeRecursion(pBindType, num, numBasic);
			if (type == T_ENUM)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_STRING)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					return SUCCESS;
			}
			if (type == T_CHAR)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout <<getName() << " " << "数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_BOOLEAN) {
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << "数据范围错误 ";
					return ERR_FATAL;
				}
				else
					return SUCCESS;
			}
			if (type == T_SHORT) {
				 return SUCCESS;
			}
			if (type == T_UNSINGED_SHORT) {
				 return SUCCESS;
			}
			if (type == T_LONG) {
				 return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG) {
				 return SUCCESS;
			}
			if (type == T_LONG_LONG) {
				 return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG_LONG) {
				 return SUCCESS;
			}
			if (type == T_FLOAT) {
				 return SUCCESS;
			}
			if (type == T_DOUBLE) {
				 return SUCCESS;
			}
			if (type == T_OCTET) {
				 return SUCCESS;
			}
			

		}
		return SUCCESS;
	}
	if (TypeNum == T_VECTOR) 
	{
		VectorEntity *pVector = dynamic_cast<VectorEntity*>(pcdlEntity);
		CDLEntity *pBindType = pVector->GetVectorType()->m_pTypeDesc;
		int BindTypeNum = pVector->GetVectorType()->m_iType;
		if (pBindType == NULL)
		{
			if (++num == numBasic)
			{
				if (BindTypeNum == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " "  << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{ }
				}
				if (BindTypeNum == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout  << getName() << " " << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
					}
				}
				if (BindTypeNum == T_BOOLEAN)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
					}
				}
				if (BindTypeNum == T_SHORT) {  }
				if (BindTypeNum == T_UNSINGED_SHORT) {  }
				if (BindTypeNum == T_LONG) {  }
				if (BindTypeNum == T_UNSIGNED_LONG) { }
				if (BindTypeNum == T_LONG_LONG) { }
				if (BindTypeNum == T_UNSIGNED_LONG_LONG) { }
				if (BindTypeNum == T_FLOAT) { }
				if (BindTypeNum == T_DOUBLE) {  }
				if (BindTypeNum == T_OCTET) {  }
				
				return SUCCESS;
			}
		}
		else
		{
			int type = TypeRecursion(pBindType, num, numBasic);
			if (type == T_ENUM)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_STRING)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout  << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_CHAR)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << "数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_BOOLEAN)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << "数据范围错误 ";
					return ERR_FATAL;
				}
				else
					return SUCCESS;
			}
			if (type == T_SHORT) {
				 return SUCCESS;
			}
			if (type == T_UNSINGED_SHORT) {
				 return SUCCESS;
			}
			if (type == T_LONG) {
				 return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG) {
				return SUCCESS;
			}
			if (type == T_LONG_LONG) {
				 return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG_LONG) {
				return SUCCESS;
			}
			if (type == T_FLOAT) {
				 return SUCCESS;
			}
			if (type == T_DOUBLE) {
				return SUCCESS;
			}
			if (type == T_OCTET) {
				 return SUCCESS;
			}
			
		}
		return SUCCESS;
	}
	if (TypeNum == T_ENUM) 
	{
		ENumEntity *pEnum = dynamic_cast<ENumEntity*>(pcdlEntity);
		if (++num == numBasic)
		{
			if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
			{
				cout  << getName() << " " << " 数据范围错误 ";
				return ERR_FATAL;
			}
			else
				 return SUCCESS;
		}
	}
}


void FormatCheckRecursion(CDLEntity*pCDLEntity, string &strRange)
{
	int TypeNum = pCDLEntity->getType();
	if (TypeNum == T_STRUCT||TypeNum==T_UNION)
	{
		if (TypeNum == T_STRUCT)
		{
			StructEntity *pStruct = dynamic_cast<StructEntity*>(pCDLEntity);
			for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
			{
				CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
				int TypeNum = (*it)->m_pTypeIndex->m_iType;
				if (pCdlEntity == NULL)
				{
					strRange += "[-,-],";
				}
				else
				{
					strRange += "(";
					FormatCheckRecursion(pCdlEntity, strRange);
					if (strRange[strRange.length() - 1] == ',')
					{
						strRange.erase(strRange.end() - 1);
						strRange += "),";
					}

				}
			}
		}
			
		else
		{
			UnionEntity *pUnion = dynamic_cast<UnionEntity*>(pCDLEntity);
			for (vector <DataMember *>::iterator it = pUnion->get_listmember().begin(); it != pUnion->get_listmember().end(); it++)
			{
				CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
				int TypeNum = (*it)->m_pTypeIndex->m_iType;
				if (pCdlEntity == NULL)
				{
					strRange += "[-,-],";
				}
				else
				{
					strRange += "(";
					FormatCheckRecursion(pCdlEntity, strRange);
					if (strRange[strRange.length() - 1] == ',')
					{
						strRange.erase(strRange.end() - 1);
						strRange += "),";
					}

				}
			}
		}			
		
	}
	if (TypeNum == T_VECTOR) 
	{
		VectorEntity *pVector = dynamic_cast<VectorEntity*>(pCDLEntity);
		CDLEntity *pCdlEntity = pVector->GetVectorType()->m_pTypeDesc;
		int NumType = pVector->GetVectorType()->m_iType;
		if (pCdlEntity == NULL)
			strRange += "[-,-],";
		else
		{
			strRange += "(";
			FormatCheckRecursion(pCdlEntity, strRange);
			if (strRange[strRange.length() - 1] == ',')
			{
				strRange.erase(strRange.end() - 1);
				strRange += "),";
			}
		}
	}
	if (TypeNum ==T_ENUM) 
	{
		strRange += "[-,-],";
	}
}


int PortEntity::RangeFormatCheck(const char *SourceChar)
{ 
	//先按数据结构生成正确的范围格式存在strrange中 然后再与source比对
	string strRange = "(";
	CDLEntity *pCdlEntity = m_DataDesc->m_pTypeDesc;
	int typeNum = m_DataDesc->m_iType;
	if (pCdlEntity == NULL)
	{
		strRange += "[-,-])";
		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);
		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		//廉伟杰
		//while(SourceRange[num]!='\0') //原来我用的是‘\0’来判断字符串结尾 
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format"<<StandardRange << endl;
			return ERR_FATAL;
		}

		
	}
	if (typeNum == T_STRUCT || typeNum == T_UNION)
	{
		if (typeNum == T_STRUCT)
		{
			StructEntity *pStruct = dynamic_cast<StructEntity*>(pCdlEntity);
			for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
			{
				CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
				int TypeNum = (*it)->m_pTypeIndex->m_iType;
				if (pCdlEntity == NULL)
				{
					strRange += "[-,-],";
				}
				else
				{
					strRange += "(";
					FormatCheckRecursion(pCdlEntity, strRange);
					if (strRange[strRange.length() - 1] == ',')
					{
						strRange.erase(strRange.end() - 1);
						strRange += "),";
					}
				}

			}
		}
		else
		{
			UnionEntity *pStruct = dynamic_cast<UnionEntity*>(pCdlEntity);
			for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
			{
				CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
				int TypeNum = (*it)->m_pTypeIndex->m_iType;
				if (pCdlEntity == NULL)
				{
					strRange += "[-,-],";
				}
				else
				{
					strRange += "(";
					FormatCheckRecursion(pCdlEntity, strRange);
					if (strRange[strRange.length() - 1] == ',')
					{
						strRange.erase(strRange.end() - 1);
						strRange += "),";
					}
				}

			}
		}

		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";

		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		int length=SourceRange.length();
		string temp1 = "-";
		string temp2 = ",-";
		//while (num<SourceRange.length())
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}

	}
	if (typeNum == T_TREE)
	{
		TreeEntity *pTree = dynamic_cast<TreeEntity*>(pCdlEntity);
		CDLEntity *TreeBindType = pTree->GetTreeType()->m_pTypeDesc;
		int BindTypeNum = pTree->GetTreeType()->m_iType;
		if(TreeBindType==NULL)
			strRange += "[-,-],";
		else
		{
			strRange += "(";
			FormatCheckRecursion(TreeBindType, strRange);
			if (strRange[strRange.length() - 1] == ',')
			{
				strRange.erase(strRange.end() - 1);
				strRange += "),";
			}
		}
		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";

		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}

	}
	if (typeNum == T_VECTOR) 
	{
		VectorEntity *pVector = dynamic_cast<VectorEntity*>(pCdlEntity);
		CDLEntity *VectorBindType = pVector->GetVectorType()->m_pTypeDesc;
		int BindTypeNum = pVector->GetVectorType()->m_iType;
		if (VectorBindType == NULL)
			strRange += "[-,-],";
		else
		{
			strRange += "(";
			FormatCheckRecursion(VectorBindType, strRange);
			if (strRange[strRange.length() - 1] == ',')
			{
				strRange.erase(strRange.end() - 1);
				strRange += "),";
			}
		}
		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";

		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}
	}
	if (typeNum == T_ENUM) 
	{
		ENumEntity *pEnum = dynamic_cast<ENumEntity*>(pCdlEntity);

		strRange += "[-,-],";
		//处理最后多余的标点符号
		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";
		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}
	}
}
int OpParamDesc::setName(const string Name)
{
	m_sName = Name;
	return SUCCESS;
}

int OpParamDesc::setName(const char * Name)
{
	if (Name == NULL) return ERR_NULL_POINTER;
	m_sName.assign(Name);
	return SUCCESS;
}

string OpParamDesc::getName()
{
	return m_sName;
}

void OpParamDesc::setDirection(int Direction)
{
	m_iDirection = Direction;
}

int OpParamDesc::getDirection()
{
	return m_iDirection;
}

void OpParamDesc::setTypeIndex(TypeIndex *typeIndex)
{
	//if (m_Type.m_pTypeDesc != NULL) free(m_Type.m_pTypeDesc); // Mention free
	m_Type = typeIndex;
}

TypeIndex *OpParamDesc::getTypeIndex()
{
	return m_Type;
}


int OpParamDesc::RangeFormatCheck(const char *SourceChar)
{
	//先按数据结构生成正确的范围格式存在strrange中 然后再与source比对
	string strRange = "(";
	CDLEntity *pCdlEntity = m_Type->m_pTypeDesc;
	int typeNum = m_Type->m_iType;
	if (pCdlEntity == NULL)
	{
		strRange += "[-,-])";
		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);
		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		//while (num<SourceRange.length())
	    while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}

	}
	if (typeNum == T_STRUCT || typeNum == T_UNION)
	{
		if (typeNum == T_STRUCT)
		{
			StructEntity *pStruct = dynamic_cast<StructEntity*>(pCdlEntity);
			for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
			{
				CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
				int TypeNum = (*it)->m_pTypeIndex->m_iType;
				if (pCdlEntity == NULL)
				{
					strRange += "[-,-],";
				}
				else
				{
					strRange += "(";
					FormatCheckRecursion(pCdlEntity, strRange);
					if (strRange[strRange.length() - 1] == ',')
					{
						strRange.erase(strRange.end() - 1);
						strRange += "),";
					}
				}

			}
		}
		else
		{
			UnionEntity *pStruct = dynamic_cast<UnionEntity*>(pCdlEntity);
			for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
			{
				CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
				int TypeNum = (*it)->m_pTypeIndex->m_iType;
				if (pCdlEntity == NULL)
				{
					strRange += "[-,-],";
				}
				else
				{
					strRange += "(";
					FormatCheckRecursion(pCdlEntity, strRange);
					if (strRange[strRange.length() - 1] == ',')
					{
						strRange.erase(strRange.end() - 1);
						strRange += "),";
					}
				}

			}
		}

		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";

		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}

	}
	if (typeNum == T_TREE)
	{
		TreeEntity *pTree = dynamic_cast<TreeEntity*>(pCdlEntity);
		CDLEntity *TreeBindType = pTree->GetTreeType()->m_pTypeDesc;
		int BindTypeNum = pTree->GetTreeType()->m_iType;
		if (TreeBindType == NULL)
			strRange += "[-,-],";
		else
		{
			strRange += "(";
			FormatCheckRecursion(TreeBindType, strRange);
			if (strRange[strRange.length() - 1] == ',')
			{
				strRange.erase(strRange.end() - 1);
				strRange += "),";
			}
		}
		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";

		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}

	}
	if (typeNum == T_VECTOR)
	{
		VectorEntity *pVector = dynamic_cast<VectorEntity*>(pCdlEntity);
		CDLEntity *VectorBindType = pVector->GetVectorType()->m_pTypeDesc;
		int BindTypeNum = pVector->GetVectorType()->m_iType;
		if (VectorBindType == NULL)
			strRange += "[-,-],";
		else
		{
			strRange += "(";
			FormatCheckRecursion(VectorBindType, strRange);
			if (strRange[strRange.length() - 1] == ',')
			{
				strRange.erase(strRange.end() - 1);
				strRange += "),";
			}
		}
		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";

		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}
	}
	if (typeNum == T_ENUM)
	{
		ENumEntity *pEnum = dynamic_cast<ENumEntity*>(pCdlEntity);

		strRange += "[-,-],";
		//处理最后多余的标点符号
		if (strRange[strRange.length() - 1] == ',')
			strRange.erase(strRange.end() - 1);
		strRange += ")";
		string StandardRange = strRange;
		//cout << "标准格式 " << StandardRange << endl;
		//cout << "原格式  " << SourceChar << endl;
		string SourceRange(SourceChar);

		//首先对原串中的数据进行替换全部换为默认-，然后再与标准的格式相比较
		int num = 0;
		string temp1 = "-";
		string temp2 = ",-";
		while (num<SourceRange.length())
		{
			if (SourceRange[num] == '[')
			{
				++num;
				while (SourceRange[num] != ',')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp1);
				++num;
				while (SourceRange[num] != ']')
				{
					SourceRange.erase(num, 1);
				}
				SourceRange.insert(num, temp2);
				++num;
			}
			else
			{
				++num;
			}
		}
		//cout << "改完：" << SourceRange << endl;

		if (SourceRange == StandardRange)
		{
			//cout << "格式正确" << endl;
			return SUCCESS;
		}
		else
		{
			cout << "Wrong Format ! Standard Format" << StandardRange << endl;
			return ERR_FATAL;
		}
	}
}

int OpParamDesc::ComplexRangeCheck(int NumType, BasicRange* pBasicRange, int numBasic)
{

	int num = 0;
	//获得port绑定的实体
	CDLEntity *pcdlEntity = m_Type->m_pTypeDesc;
	int TypeNum = pcdlEntity->getType();
	//绑定的struct实体，遍历vector
	if (TypeNum == T_STRUCT)
	{
		StructEntity *pStruct = dynamic_cast<StructEntity*>(pcdlEntity);
		for (vector <DataMember *>::iterator it = pStruct->get_listmember().begin(); it != pStruct->get_listmember().end(); it++)
		{
			CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
			int DataType = (*it)->m_pTypeIndex->m_iType;
			//简单数据类型处理
			if (pCdlEntity == NULL)
			{
				//递归遍历所有的基本类型并计数与numBasic比较
				if (++num == numBasic)
				{
					if (DataType == T_STRING)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
							//cout << num << ": string " << endl;
						}
					}
					if (DataType == T_CHAR)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
							//cout << num << ": char " << endl;
						}
					}
					if (DataType == T_BOOLEAN) 
					{ 
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
							//cout << num << ": char " << endl;
						}
					}
					if (DataType == T_SHORT) {  }
					if (DataType == T_UNSINGED_SHORT) {  }
					if (DataType == T_LONG) {  }
					if (DataType == T_UNSIGNED_LONG) { }
					if (DataType == T_LONG_LONG) {  }
					if (DataType == T_UNSIGNED_LONG_LONG) { }
					if (DataType == T_FLOAT) {  }
					if (DataType == T_DOUBLE) {  }
					if (DataType == T_OCTET) {  }
					
					return SUCCESS;
				}
			}
			else
			{
				int type = TypeRecursion(pCdlEntity, num, numBasic);
				if (type == T_ENUM)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
						return SUCCESS;
					}
				}
				if (type == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_BOOLEAN) {
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_SHORT) {
					return SUCCESS;
				}
				if (type == T_UNSINGED_SHORT) {
					return SUCCESS;
				}
				if (type == T_LONG) {
					return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG) {
					return SUCCESS;
				}
				if (type == T_LONG_LONG) {
					return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG_LONG) {
					return SUCCESS;
				}
				if (type == T_FLOAT) {
					return SUCCESS;
				}
				if (type == T_DOUBLE) {
				    return SUCCESS;
				}
				if (type == T_OCTET) {
					return SUCCESS;
				}
				

			}
		}
	}
	if (TypeNum == T_UNION)
	{
		UnionEntity *pUnion = dynamic_cast<UnionEntity*>(pcdlEntity);
		for (vector <DataMember *>::iterator it = pUnion->get_listmember().begin(); it != pUnion->get_listmember().end(); it++)
		{
			CDLEntity *pCdlEntity = (*it)->m_pTypeIndex->m_pTypeDesc;
			int DataType = (*it)->m_pTypeIndex->m_iType;
			//简单数据类型处理
			if (pCdlEntity == NULL)
			{
				//递归遍历所有的基本类型并计数与numBasic比较
				if (++num == numBasic)
				{
					if (DataType == T_STRING)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
							//cout << num << ": string " << endl;
						}
					}
					if (DataType == T_CHAR)
					{
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
							//cout << num << ": char " << endl;
						}
							
					}
					if (DataType == T_BOOLEAN)
					{ 
						if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
						{
							cout << getName() << ": " << (*it)->m_sName << " 数据范围错误 ";
							return ERR_FATAL;
						}
						else
						{
							//cout << num << ": char " << endl;
						}
							
					}
					if (DataType == T_SHORT) { }
					if (DataType == T_UNSINGED_SHORT) {  }
					if (DataType == T_LONG) {}
					if (DataType == T_UNSIGNED_LONG) {  }
					if (DataType == T_LONG_LONG) {  }
					if (DataType == T_UNSIGNED_LONG_LONG) {  }
					if (DataType == T_FLOAT) {  }
					if (DataType == T_DOUBLE) {  }
					if (DataType == T_OCTET) {  }
					
					return SUCCESS;
				}
			}
			else
			{
				int type = TypeRecursion(pCdlEntity, num, numBasic);
				if (type == T_ENUM)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
						return SUCCESS;
					}
				}
				if (type == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_pTypeIndex->m_pTypeDesc->getName() << " " << (*it)->m_sName << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}
				if (type == T_BOOLEAN) 
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << (*it)->m_sName << "数据范围错误 ";
						return ERR_FATAL;
					}
					else
						return SUCCESS;
				}

				if (type == T_SHORT) {
					return SUCCESS;
				}
				if (type == T_UNSINGED_SHORT) {
					 return SUCCESS;
				}
				if (type == T_LONG) {
					 return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG) {
					 return SUCCESS;
				}
				if (type == T_LONG_LONG) {
					 return SUCCESS;
				}
				if (type == T_UNSIGNED_LONG_LONG) {
					 return SUCCESS;
				}
				if (type == T_FLOAT) {
					return SUCCESS;
				}
				if (type == T_DOUBLE) {
					 return SUCCESS;
				}
				if (type == T_OCTET) {
					 return SUCCESS;
				}
				if (type == T_BOOLEAN) {
					 return SUCCESS;
				}

			}
		}
	}
	if (TypeNum == T_TREE)
	{
		TreeEntity *pTree = dynamic_cast<TreeEntity*>(pcdlEntity);
		CDLEntity *pBindType = pTree->GetTreeType()->m_pTypeDesc;
		int BindTypeNum = pTree->GetTreeType()->m_iType;
		if (pBindType == NULL)
		{
			if (++num == numBasic)
			{
				if (BindTypeNum == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout <<  getName() << ": "  << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
						//cout << num << ": string " << endl;
					}
				}
				if (BindTypeNum == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << ": " <<" 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
					}
				}
				if (BindTypeNum == T_BOOLEAN) 
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << ": "  << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
					}
				}
				if (BindTypeNum == T_SHORT) {  }
				if (BindTypeNum == T_UNSINGED_SHORT) {  }
				if (BindTypeNum == T_LONG) {  }
				if (BindTypeNum == T_UNSIGNED_LONG) { }
				if (BindTypeNum == T_LONG_LONG) {  }
				if (BindTypeNum == T_UNSIGNED_LONG_LONG) {  }
				if (BindTypeNum == T_FLOAT) {  }
				if (BindTypeNum == T_DOUBLE) { }
				if (BindTypeNum == T_OCTET) {  }
				return SUCCESS;
			}
		}
		else
		{
			int type = TypeRecursion(pBindType, num, numBasic);
			if (type == T_ENUM)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_STRING)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					return SUCCESS;
			}
			if (type == T_CHAR)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << "数据范围错误 ";
					return ERR_FATAL;
				}
				else
					return SUCCESS;
			}
			if (type == T_BOOLEAN)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << "数据范围错误 ";
					return ERR_FATAL;
				}
				else
					return SUCCESS;
			}
			if (type == T_SHORT) {
				 return SUCCESS;
			}
			if (type == T_UNSINGED_SHORT) {
				 return SUCCESS;
			}
			if (type == T_LONG) {
				return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG) {
				 return SUCCESS;
			}
			if (type == T_LONG_LONG) {
			    return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG_LONG) {
				 return SUCCESS;
			}
			if (type == T_FLOAT) {
				 return SUCCESS;
			}
			if (type == T_DOUBLE) {
			 return SUCCESS;
			}
			if (type == T_OCTET) {
				 return SUCCESS;
			}
		}
		return SUCCESS;
	}
	if (TypeNum == T_VECTOR)
	{
		VectorEntity *pVector = dynamic_cast<VectorEntity*>(pcdlEntity);
		CDLEntity *pBindType = pVector->GetVectorType()->m_pTypeDesc;
		int BindTypeNum = pVector->GetVectorType()->m_iType;
		if (pBindType == NULL)
		{
			if (++num == numBasic)
			{
				if (BindTypeNum == T_STRING)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout  << getName() << " " << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else {}
						
				}
				if (BindTypeNum == T_CHAR)
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " "  << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{ }
				}
				if (BindTypeNum == T_BOOLEAN) 
				{
					if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
					{
						cout << getName() << " " << " 数据范围错误 ";
						return ERR_FATAL;
					}
					else
					{
					}
				}
				if (BindTypeNum == T_SHORT) { }
				if (BindTypeNum == T_UNSINGED_SHORT) {  }
				if (BindTypeNum == T_LONG) {  }
				if (BindTypeNum == T_UNSIGNED_LONG) { }
				if (BindTypeNum == T_LONG_LONG) {  }
				if (BindTypeNum == T_UNSIGNED_LONG_LONG) { }
				if (BindTypeNum == T_FLOAT) {  }
				if (BindTypeNum == T_DOUBLE) {  }
				if (BindTypeNum == T_OCTET) {  }
				
				return SUCCESS;
			}
		}
		else
		{
			int type = TypeRecursion(pBindType, num, numBasic);
			if (type == T_ENUM)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					return SUCCESS;
			}
			if (type == T_STRING)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << num << ": " << getName() << " " << " 数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_CHAR)
			{
				if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
				{
					cout << num << ": " << getName() << " " << "数据范围错误 ";
					return ERR_FATAL;
				}
				else
					 return SUCCESS;
			}
			if (type == T_SHORT) {
				 return SUCCESS;
			}
			if (type == T_UNSINGED_SHORT) {
				 return SUCCESS;
			}
			if (type == T_LONG) {
				return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG) {
				 return SUCCESS;
			}
			if (type == T_LONG_LONG) {
				return SUCCESS;
			}
			if (type == T_UNSIGNED_LONG_LONG) {
				 return SUCCESS;
			}
			if (type == T_FLOAT) {
				return SUCCESS;
			}
			if (type == T_DOUBLE) {
				return SUCCESS;
			}
			if (type == T_OCTET) {
				 return SUCCESS;
			}
			if (type == T_BOOLEAN) {
				return SUCCESS;
			}

		}
		return SUCCESS;
	}
	if (TypeNum == T_ENUM)
	{
		ENumEntity *pEnum = dynamic_cast<ENumEntity*>(pcdlEntity);
		if (++num == numBasic)
		{
			if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
			{
				cout <<getName() << " " << " 数据范围错误 ";
				return ERR_FATAL;
			}
			else
			   return SUCCESS;
		}
	}
}
int OpParamDesc::BasicRangeCheck(int NumType, BasicRange* pBasicRange)
{
	if (NumType == T_STRING)
	{
		if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
		{
			cout << getName() << endl;
			return ERR_FATAL;
		}
	}
	if (NumType == T_CHAR)
	{
		if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
		{
			cout << getName()  << endl;
		}
		return ERR_FATAL;
	}
	if (NumType == T_BOOLEAN)
	{
		if (pBasicRange->lower != "-" || pBasicRange->upper != "-")
		{
			cout << getName() << endl;
		}
		return ERR_FATAL;
	}
	return SUCCESS;

}


OpParamDesc::OpParamDesc()
{
	m_Type = NULL;
}

OpParamDesc::~OpParamDesc()
{
	// if (m_Type.m_pTypeDesc != NULL) free(m_Type.m_pTypeDesc);  
	// Mention the free call, maybe use switch to process different case
	if (m_Type != NULL) delete m_Type;
}

OperationDesc::OperationDesc()
{
	m_ReturnType = NULL;
}

OperationDesc::~OperationDesc()
{
	if (m_ReturnType != NULL) delete m_ReturnType;  
	for (vector<OpParamDesc *>::iterator it = m_listParam.begin(); it != m_listParam.end(); ++it)
	{
		delete *it;
	}
}

int OperationDesc::setName(const string Name)
{
	m_sName = Name;
	return SUCCESS;
}

int OperationDesc::setName(const char * Name)
{
	if (Name == NULL) return ERR_NULL_POINTER;
	m_sName.assign(Name);
	return SUCCESS;
}

string OperationDesc::getName()
{
	return m_sName;
}

void OperationDesc::setOneWayOption(int OneWayOption)
{
	m_iOneWayOption = OneWayOption;
}

int  OperationDesc::getOneWayOption()
{
	return m_iOneWayOption;
}

void OperationDesc::setReturnType(TypeIndex *tp)
{
	if (m_ReturnType != NULL) delete m_ReturnType;
	m_ReturnType = tp;
}

TypeIndex * OperationDesc::getReturntype()
{
	return m_ReturnType;
}

bool OperationDesc::DuplicatedParamName(const string Name)
{
	for (vector<OpParamDesc *>::iterator it = m_listParam.begin();
										 it != m_listParam.end(); ++it)
		if ((*it)->getName() == Name) return true;
	return false;
}

bool OperationDesc::DuplicatedParamName(const char * Name)
{
	string tmpName;

	if (Name == NULL) return true ; // Maybe should return false 
	tmpName.assign(Name);

	for (vector<OpParamDesc *>::iterator it = m_listParam.begin();
										 it != m_listParam.end(); ++it)
		if ((*it)->getName() == tmpName) return true;
	return false;
}
int OperationDesc::AppendParam(OpParamDesc *Param)
{
	string ParamName;

	if (Param == NULL) return ERR_NULL_POINTER;

	ParamName = Param->getName();

	if ( DuplicatedParamName(ParamName)) return ERR_DUPLICATED_NAME;
	m_listParam.push_back(Param);

	return SUCCESS;
}

bool InterfaceEntity::DuplicatedOperationName(const string Name)
{
	for (vector<OperationDesc *>::iterator it = m_listOperation.begin();
										   it != m_listOperation.end(); ++it)
	{
		OperationDesc *Operation;  Operation = *it;
		if (Name == Operation->getName()) return true;
	}
	return false;
}

bool InterfaceEntity::DuplicatedOperationName(const char * Name)
{
	string OperationName;

	if (Name == NULL) return true; // ??
	OperationName.assign(Name);

	for (vector<OperationDesc *>::iterator it = m_listOperation.begin();
										   it != m_listOperation.end(); ++it)
	{
		OperationDesc *Operation;  Operation = *it;
		if (OperationName == Operation->getName()) return true;
	}
	return false;
}

int InterfaceEntity::AppendOperation(OperationDesc *Operation)
{
	if (Operation == NULL) return ERR_NULL_POINTER; 
	if (DuplicatedOperationName(Operation->getName())) 
		return ERR_DUPLICATED_NAME;
	m_listOperation.push_back(Operation);

	return SUCCESS;
}

void InterfaceEntity::Destroy()
{
	for (vector<OperationDesc *>::iterator it = m_listOperation.begin();
										   it != m_listOperation.end(); ++it)
		delete *it;
}

InterfaceEntity::~InterfaceEntity()
{
	Destroy();
}



/*

int ComponentParamDesc::setName(string Name)
{
	m_sName = Name;
	return SUCCESS;
}

int ComponentParamDesc::setName(char * Name)
{
	if (Name == NULL) return ERR_NULL_POINTER;
	m_sName.assign(Name);
	return SUCCESS;
}

string ComponentParamDesc::getName()
{
	return m_sName;
}

int ComponentParamDesc::setType(TypeIndex *Type)
{
	if (Type == NULL) return ERR_NULL_POINTER;
	m_Type = Type;
	return SUCCESS;
}

TypeIndex *ComponentParamDesc::getType( )
{
	return m_Type;
}

ComponentParamDesc::ComponentParamDesc()
{
	m_Type = NULL;
}

ComponentParamDesc::~ComponentParamDesc()
{
	if (m_Type != NULL) delete m_Type;
}

ComponentAttrDesc::ComponentAttrDesc()
{
	m_Type = NULL;
}

ComponentAttrDesc::~ComponentAttrDesc()
{
	if (m_Type != NULL) delete m_Type;
}

int ComponentAttrDesc::setName(string Name)
{
	m_sName = Name;
	return SUCCESS;
}

int ComponentAttrDesc::setName(char * Name)
{
	if (Name == NULL) 	return ERR_NULL_POINTER;
	m_sName.assign(Name);
	return SUCCESS;
}

string ComponentAttrDesc::getName()
{
	return m_sName;
}

int ComponentAttrDesc::setType(TypeIndex *Type)
{
	if (Type == NULL) return ERR_NULL_POINTER;
	m_Type = Type;
	return SUCCESS;
}

TypeIndex *ComponentAttrDesc::getType( )
{
	return m_Type;
}

*/

ComponentPortDesc::ComponentPortDesc()
{
	m_pPortEntity = NULL;
}

ComponentPortDesc::~ComponentPortDesc()
{
	if (m_pPortEntity != NULL) delete m_pPortEntity;
}


int ComponentPortDesc::setName(const string Name)
{
	m_sName = Name;
	return SUCCESS;
}

int ComponentPortDesc::setName(const char * Name)
{
	if (Name == NULL) return ERR_NULL_POINTER;
	m_sName.assign(Name);
	return SUCCESS;
}

string ComponentPortDesc::getName()
{
	return m_sName;
}


void ComponentPortDesc::setPubSub(int PubSub)
{
	m_iPubSub = PubSub;
}

int ComponentPortDesc::getPubSub()
{
	return m_iPubSub;
}

void ComponentPortDesc::setIsLocal(int IsLocal)
{
	m_iIsLocal = IsLocal;
}

int ComponentPortDesc::getIsLocal()
{
	return m_iIsLocal;
}

int ComponentPortDesc::setPortEntity(PortEntity *PortIndex)
{
	//if (m_pPortEntity != NULL) delete m_pPortEntity;
	if (PortIndex == NULL) return ERR_NULL_POINTER;
	m_pPortEntity = PortIndex;
	return SUCCESS;
}

PortEntity * ComponentPortDesc::getPortEntity()
{
	return m_pPortEntity;
}

ComponentInterfaceDesc::ComponentInterfaceDesc()
{
	m_pInterfaceEntity = NULL;
}

ComponentInterfaceDesc::~ComponentInterfaceDesc()
{
}

int ComponentInterfaceDesc::setName(const string Name)
{
	m_sName = Name;
	return SUCCESS;
}

int ComponentInterfaceDesc::setName(const char * Name)
{
	if (Name == NULL) return ERR_NULL_POINTER;
	m_sName.assign(Name);
	return SUCCESS;
}

string ComponentInterfaceDesc::getName()
{
	return m_sName;
}

void ComponentInterfaceDesc::setRole(int Role)
{
	m_iRole = Role;
}

int ComponentInterfaceDesc::getRole()
{
	return m_iRole;
}

void ComponentInterfaceDesc::setIsLocal(int IsLocal)
{
	m_iIsLocal = IsLocal;
}

int ComponentInterfaceDesc::getIsLocal()
{
	return m_iIsLocal;
}

int ComponentInterfaceDesc::setInterfaceEntity(InterfaceEntity *InterfaceIndex)
{
	if (InterfaceIndex == NULL) return ERR_NULL_POINTER;
	m_pInterfaceEntity = InterfaceIndex;
	return SUCCESS;
}

InterfaceEntity * ComponentInterfaceDesc::getInterfaceEntity()
{
	return m_pInterfaceEntity;
}

void ComponentEntity::Destroy()
{
	//for (vector<ComponentParamDesc *>::iterator it = m_listParam.begin(); it != m_listParam.end(); ++it)
		//delete *it; // May be corrected as if ((*it) != NULL) delete *it;

	//for (vector<ComponentAttrDesc *>::iterator it = m_listAttr.begin(); it != m_listAttr.end(); ++it)
		//delete *it;

	for (vector<ComponentPortDesc *>::iterator it = m_listPort.begin(); it != m_listPort.end(); ++it)
		delete *it;

	for (vector<ComponentInterfaceDesc *>::iterator it = m_listInterface.begin(); it != m_listInterface.end(); ++it)
		delete *it;
	delete pDefaultInterface;
}



ComponentEntity::~ComponentEntity()
{
	Destroy();
}

int ComponentEntity::set_pDefaultInterface(ComponentInterfaceDesc *p)
{
	pDefaultInterface = p;
	return SUCCESS;
}
ComponentInterfaceDesc* ComponentEntity::get_pDefaultInterface()
{
	return pDefaultInterface;
}

/*

bool ComponentEntity::DuplicatedParam(const string Name)
{
	for (vector<ComponentParamDesc *>::iterator it = m_listParam.begin(); it != m_listParam.end(); ++it)
		if (((*it)->getName()) == Name) return true;
	return false;
}

bool ComponentEntity::DuplicatedParam(const char * Name)
{
	if (Name == NULL) return true; // ??

	for (vector<ComponentParamDesc *>::iterator it = m_listParam.begin(); it != m_listParam.end(); ++it)
	{
		string tmpStr(Name);

		if (((*it)->getName()) == tmpStr) return true;
	}
	return false;
}


int ComponentEntity::AppendParam(ComponentParamDesc *ParamDesc)
{
	if (ParamDesc == NULL) return ERR_NULL_POINTER;
	if (DuplicatedParam(ParamDesc->getName())) return ERR_DUPLICATED_NAME;
	
	m_listParam.push_back(ParamDesc);
	return SUCCESS;
}

bool ComponentEntity::DuplicatedAttr(const string Name)
{
	for (vector<ComponentAttrDesc *>::iterator it = m_listAttr.begin(); it != m_listAttr.end(); ++it)
		if (((*it)->getName()) == Name) return true;
	return false;
}

bool ComponentEntity::DuplicatedAttr(const char * Name)
{
	if (Name == NULL) return true;

	for (vector<ComponentAttrDesc *>::iterator it = m_listAttr.begin(); it != m_listAttr.end(); ++it)
	{
		string tmpStr(Name);

		if (((*it)->getName()) == tmpStr) return true;
	}
	return false;
}

int ComponentEntity::AppendAttr(ComponentAttrDesc *AttrDesc)
{
	if (AttrDesc == NULL) return ERR_NULL_POINTER;
	if (DuplicatedAttr(AttrDesc->getName())) return ERR_DUPLICATED_NAME;
	
	m_listAttr.push_back(AttrDesc);
	return SUCCESS;
}



*/

bool ComponentEntity::DuplicatedPort(const string Name)
{
	for (vector<ComponentPortDesc *>::iterator it = m_listPort.begin(); it != m_listPort.end(); ++it)
		if (((*it)->getName()) == Name) return true;
	return false;
}

bool ComponentEntity::DuplicatedPort(const char * Name)
{
	if (Name == NULL) return true;
	
	for (vector<ComponentPortDesc *>::iterator it = m_listPort.begin(); it != m_listPort.end(); ++it)
	{
		string tmpStr(Name);

		if (((*it)->getName()) == tmpStr) return true;
	}
	return false;
}

int ComponentEntity::AppendPort(ComponentPortDesc *PortDesc)
{
	if (PortDesc == NULL) return ERR_NULL_POINTER;
	//if (DuplicatedAttr(PortDesc->getName())) return ERR_DUPLICATED_NAME;
	
	m_listPort.push_back(PortDesc);
	return SUCCESS;
}


bool ComponentEntity::DuplicatedInterface(const string Name)
{
	for (vector<ComponentInterfaceDesc *>::iterator it = m_listInterface.begin(); it != m_listInterface.end(); ++it)
		if (((*it)->getName()) == Name) return true;
	return false;
}

bool ComponentEntity::DuplicatedInterface(const char * Name)
{
	if (Name == NULL) return true; // ??

	for (vector<ComponentInterfaceDesc *>::iterator it = m_listInterface.begin(); it != m_listInterface.end(); ++it)
	{
		string tmpStr(Name);

		if (((*it)->getName()) == tmpStr) return true;
	}
	return false;
}

int ComponentEntity::AppendInterface(ComponentInterfaceDesc *InterfaceDesc)
{
	if (InterfaceDesc == NULL) return ERR_NULL_POINTER;
	if (DuplicatedInterface(InterfaceDesc->getName())) return ERR_DUPLICATED_NAME;
	
	m_listInterface.push_back(InterfaceDesc);
	return SUCCESS;
}

//ui
void ComponentEntity::set_UI_ServiceFlag(int flag) 
{
	UI_ServiceFlag=flag;
}
int ComponentEntity::get_UI_ServiceFlag()
{
	return UI_ServiceFlag;
}


CDLFile::~CDLFile()
{
	for (vector<CDLEntity *>::iterator it = m_listCDLEntity.begin(); it != m_listCDLEntity.end(); ++it)
		if ((*it) != NULL) delete *it;
}

bool CDLFile::DuplicatedCDLEntity(const string Name)
{
	for (vector<CDLEntity *>::iterator it = m_listCDLEntity.begin(); it != m_listCDLEntity.end(); ++it)
		if ((*it)->MatchQualifiedName(Name)) return true;
	return false;
}

bool CDLFile::DuplicatedCDLEntity(const char * Name)
{
	if (Name == NULL) return true;

	string tmpStr(Name);

	for (vector<CDLEntity *>::iterator it = m_listCDLEntity.begin(); it != m_listCDLEntity.end(); ++it)
		if ((*it)->MatchQualifiedName(tmpStr)) return true;
	return false;
}

int CDLFile::AppendCDLEntity(CDLEntity *Entity)
{
	if (Entity == NULL) return ERR_NULL_POINTER;
	if (DuplicatedCDLEntity(Entity->getName())) return ERR_DUPLICATED_NAME;

	m_listCDLEntity.push_back(Entity);
	return SUCCESS;
}

CDLEntity *CDLFile::FindEntityIndex(const string Name)
{
	for (vector<CDLEntity *>::iterator it = m_listCDLEntity.begin(); it != m_listCDLEntity.end(); ++it)
		if ((*it)->MatchQualifiedName(Name)) return (*it);
	return NULL;
}



//从CDLFile类中得到所有的CDLEntity信息
vector <CDLEntity *> CDLFile::GetCDLEntityList()const
{
	return m_listCDLEntity;
}
//从ComponentEntity类中得到接口列表
vector <ComponentInterfaceDesc *> ComponentEntity::GetInterfaceList()const
{
	return m_listInterface;
}
//从函数名得到函数的参数列表
vector <OpParamDesc *> OperationDesc::GetOpParamList()const
{
	return m_listParam;
}

//lian add
void  FundmemtalEntity::CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL)
{

}
	