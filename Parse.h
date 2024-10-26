#ifndef PARSE_H
#define PARSE_H

#include <string>
// ZLC MODIFIED 
#include <string.h>
// ZLC MODIFIED END
#include <map>
#include "CDL.h"

EXTERN ENumEntity *CurrENumEntity;
EXTERN S_U_Entity *CurrS_UEntity;
EXTERN VectorEntity *CurrVectorEntity;
EXTERN TreeEntity *CurrTreeEntity;
EXTERN PortEntity *CurrPortEntity;
EXTERN InterfaceEntity *CurrInterfaceEntity;
EXTERN OperationDesc *CurrOperation;

EXTERN ComponentEntity *CurrComponentEntity;
//��Ϊ������interface�еķ�������component�еķ���
int Initialize();

int PushCurrPackage(const char * PackageName);
int PopCurrPackage();

int CreateENumEntity(const char * Name);
int AppendValueName(const char * Name);


int CreateVectorEntity(const char * Name);
int RecordVectorSimpleType(int FundType, int len = 0);
int RecordVectorComplexType(const char *TypeName, int len = 0);


int CreateTreeEntity(const char * Name);
int RecordTreeSimpleType(int FundType);
int RecordTreeComplexType(const char * TypeName);

int CreateStructEntity(const char *Name);
int CreateUnionEntity(const char *Name);
int AddFundamentalDataMember(int FundType, const char *Name);
int AddComplexDataMember(const char *TypeName, const char *MemberName);

int CreatePortEntity(const char *Name);
int RecordPortSimpleType(int type);
int RecordPortComplexType(const char *Name);
//�������ݷ�Χ�Ĵ���,���ڴ˺������жϷ�Χ�����������Ƿ�ƥ��
int LoadPortDataRange(const char *Range);



int CreateInterfaceEntity(const char *Name);
OperationDesc* CreateOperation(int OneWayOption);

TypeIndex *CreateTypeIndex(const char *Name);
int SetOperationName(const char *Name);
int AddOperation(OperationDesc *pOperation);
int AppendParameter(int Direction, TypeIndex *tp, const char *Name, const char *ParameterDataRange);
int SetOperationReturnType(TypeIndex *tp);

int CreateComponentEntity(const char *Name);
void setComOpFlag(bool flag);
void setComFlag(int flags);//��ΰ��
int AddFunToDefaultInterface(OperationDesc *pOperation);
//int AppendSimpleParam(int Type, const char *ParamName);
//int AppendComplexParam(const char *TypeName, const char *ParamName);
//int AppendSimpleAttr(int Type, const char *AttrName);
//int AppendComplexAttr(const char *TypeName, const char *AttrName);
int AppendPortDesc(int PubSub, int IsLocal, const char *PortTypeName, const char *PortName);
int AppendInterfaceDesc(int Role, int IsLocal, const char *InterfaceTypeName, const char *InterfaceName);



#endif