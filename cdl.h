//labled by yhw

#ifndef CDL_H
#define CDL_H

#ifdef CDL_MAIN
#define EXTERN        
#else
#define EXTERN extern
#endif

#define T_SHORT						(-1)
#define T_UNSINGED_SHORT			(-2)
#define T_LONG						(-3)
#define T_UNSIGNED_LONG				(-4)
#define T_LONG_LONG					(-5)
#define T_UNSIGNED_LONG_LONG		(-6)
#define T_FLOAT						(-7)
#define T_DOUBLE					(-8)
#define T_CHAR						(-9)
#define T_BOOLEAN					(-10)
#define T_OCTET						(-11)
#define T_STRING					(-12)

//#define T_VECTOR                    (-13)

#define T_VOID						(-15)

/* define complex type name as integer */
#define T_FUNDAMENTAL		1
#define T_STRUCT			2
#define T_UNION				3
#define T_PORT				4
#define T_INTERFACE			5
#define T_ENUM				6
#define T_COMPONENT			7
#define T_TREE				8
#define T_VECTOR            9

#define M_ONEWAY			2
#define M_NON_ONEWAY		1

#define M_LOCAL				2
#define M_NON_LOCAL			1

#define M_IN				3
#define M_OUT				1
#define M_INOUT				2

#define M_CONSUME			2
#define M_PUBLISH			1

#define M_PROVIDE			2
#define M_REQUIRE			1

#define M_UI			2
#define M_SERVICE			1

#define SUCCESS							0

#define ERR_DUPLICATED_NAME				1
#define ERR_NULL_POINTER				2
#define ERR_FATAL	3



#include <string>
#include <vector>

using namespace std;



class CDLEntity
{
protected:
	string m_sPackagePath;
	string m_sName;
	int m_iType;
	//vector <DataMember *>& m_listmember;
	virtual void Destroy() {}

public:
	int getType();
	void setType(int tp);
	void setName(const string Name);
	int setName(const char * Name);
	string getName();
	void setPackageName(const string Name);
	int setPackageName(const char *Name);
	string GetQualifiedName();
	bool MatchQualifiedName(const string Name);
	void *FindEntityIndex(const string Name);
	//djc add IDL
	virtual void CodeGeneration(FILE *fpHeader, FILE *fpSource,FILE *fpIDL) = 0;
	//vector <DataMember *>& get_listmember();
	//virtual ~CDLEntity() = 0;
};
struct TypeIndex
{
	int m_iType;
	CDLEntity * m_pTypeDesc;

	TypeIndex();
	~TypeIndex();
};
struct DataMember
{
	string m_sName;
	TypeIndex *m_pTypeIndex;

	DataMember();
	~DataMember();
};
//lian add 
class FundmemtalEntity : public CDLEntity
{
public:
	void CodeGeneration(FILE *fpHeader, FILE *fpSource,FILE *fpIDL);
};







//2016.5.5 range处理
enum RangeType { Basic, Complex };
class RangeDesc
{
public:
	RangeType rangeType;
};
class BasicRange : public RangeDesc
{
public:
	string lower;
	string upper;
};
class ComplexRange : public RangeDesc
{
public:
	vector<RangeDesc *> m_listRange;
};

typedef vector<RangeDesc *> ValueRange;

class S_U_Entity : public CDLEntity
{
protected:
	vector <DataMember *> m_listMember;
	void Destroy();

public:
	int AppendMember(DataMember *Member);
//	void AppendMember(int type, void *Member);
	bool DuplicatedMemberName(const char *Name);
	bool DuplicatedMemberName(const string Name);
	vector <DataMember *>& get_listmember() { return m_listMember; }
	void CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL) ;

};

class StructEntity : public S_U_Entity
{
public:
	~StructEntity();
};

class UnionEntity : public S_U_Entity
{
public:
	~UnionEntity();
};

class ENumEntity : public CDLEntity
{
private:
	vector <string> m_listValueName;
	void Destroy();

public:
	int AppendValueName(const string Name);
	int AppendValueName(const char * Name);
	bool DuplicatedValueName(const string Name);

	void CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL);

	~ENumEntity();
};


class VectorEntity : public CDLEntity
{
private:
	int length;
	TypeIndex *m_type;
	void Destory();
public:
	void SetLength(int len);
	int GetLength();
	void SetVectorType(TypeIndex* t);
	TypeIndex* GetVectorType();
	~VectorEntity();
	void CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL);
};


class TreeEntity : public CDLEntity
{
private:
	TypeIndex* m_type;
	void Destroy();
public:
	void SetTreeType(TypeIndex* t);
	TypeIndex* GetTreeType();
	~TreeEntity();
	void CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL);
};

class PortEntity : public CDLEntity
{
private:
	TypeIndex *m_DataDesc;
	void Destroy();
public:
	//增加了range记录范围
	ValueRange valueRange;	
	void setTypeIndex(TypeIndex *typeIndex);
	TypeIndex *getTypeIndex();
	PortEntity();
	~PortEntity();
	//一参要匹配的数据类型都是基本数据类型，二参存储range表示，散参表示对应port的第n个基本数据类型，递归计数用
	int ComplexRangeCheck(int NumType, BasicRange*, int numBasic);
	int BasicRangeCheck(int NumType,BasicRange*);
	int RangeFormatCheck(const char *source);

	void CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL) ;
};

class OpParamDesc
{
private:
	string m_sName;
	int m_iDirection;
	TypeIndex *m_Type;
public:
	//增加对方法参数范围的记录
	ValueRange valueRange;	

	int setName(const string Name);
	int setName(const char * Name);
	string getName();

	void setDirection(int Direction);
	int getDirection();

	void setTypeIndex(TypeIndex *typeIndex);
	TypeIndex *getTypeIndex();
	//对范围内容的判断
	int ComplexRangeCheck(int NumType, BasicRange*, int numBasic);
	int BasicRangeCheck(int NumType, BasicRange*);
	//对范围格式的判断
	int RangeFormatCheck(const char *source);
	OpParamDesc();
	~OpParamDesc();
	
};

class OperationDesc
{
private:
	string m_sName;
	int    m_iOneWayOption;
	TypeIndex *m_ReturnType;
	vector <OpParamDesc *> m_listParam;
public:
	
	OperationDesc();
	~OperationDesc();
	int setName(const string Name);
	int setName(const char * Name);
	string getName();
	void setOneWayOption(int OneWayOption);
	int  getOneWayOption();

	void setReturnType(TypeIndex *tp);
	TypeIndex *getReturntype();

	bool DuplicatedParamName(const string Name);
	bool DuplicatedParamName(const char * Name);

	int AppendParam(OpParamDesc *Param);
	//增加CodeGeneration的参数 FILE *fpIDL DJC
	void CodeGeneration(FILE *fpHeader, FILE *fpSource,FILE *fpIDL) ;
	void CodeGeneration(FILE *fpHeader) ;
	void CodeGeneration2(FILE *fpHeader, const char *ComName, const char *InterfaceName) ;
	//lian add 2016.8.24
	void OpMethParGeneration(FILE *fpHeader);//接口下命名空间MethodsParams下函数代码的生成函数
	void OpProvideMethodsGeneration(FILE *fpHeader,const char *InterfaceName);//接口下命名空间Prioide下Methods命名空间C++代码
	void OpProvideMethodsCallOp(FILE *fpSource, const string InterfaceName);//provide下Methods命名空间下的每个操作类中Call函数
	void OpRequireOperationCpp(FILE *fpSource, const string ComponentName, const string ComInterfaceName,const string MethodName);//require下接口类的每个函数的实现Cpp
	void OpComProvideOpCpp(FILE *fpSource, const string ComponentName, const string ComInterfaceName);//构件cpp文件中provide接口中操作的C++代码
	void onRequestOpParamCpp(FILE *fpSource,const string MethodName);//为on_request_available中的params赋值
	
	//得到函数的参数列表
	vector <OpParamDesc *> GetOpParamList()const;
};

class InterfaceEntity : public CDLEntity
{
private:
	void Destroy();
public:
	
	vector <OperationDesc *> m_listOperation;

	bool DuplicatedOperationName(const string Name);
	bool DuplicatedOperationName(const char * Name);

	int AppendOperation(OperationDesc *Operation);

	void CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL) ;
	//lian add 2016.8.25
	void ProvideGeneration(FILE *fpSource);//provide命名空间下cpp文件
	~InterfaceEntity();
};


/* 5.9日 component去掉attribute和parameter

class ComponentParamDesc
{
private:
	string m_sName;
	TypeIndex *m_Type;
public:
	int setName(string Name);
	int setName(char * Name);
	string getName();

	int setType(TypeIndex *Type);
	TypeIndex *getType( );

	ComponentParamDesc();
	~ComponentParamDesc();
};

class ComponentAttrDesc
{
private:
	string m_sName;
	TypeIndex *m_Type;
public:
	int setName(string Name);
	int setName(char * Name);
	string getName();

	int setType(TypeIndex *Type);
	TypeIndex *getType( );

	ComponentAttrDesc();
	~ComponentAttrDesc();
};

*/



class ComponentPortDesc
{
private:
	string m_sName;
	int m_iPubSub;
	int m_iIsLocal;
	PortEntity *m_pPortEntity;
public:
	ComponentPortDesc();
	~ComponentPortDesc();
	int setName(const string Name);
	int setName(const char * Name);
	string getName();

	void setPubSub(int PubSub);
	int getPubSub();

	void setIsLocal(int IsLocal);
	int getIsLocal();

	int setPortEntity(PortEntity *PortIndex);
	PortEntity *getPortEntity();
};

class ComponentInterfaceDesc
{
private:
	string m_sName;
	int m_iRole;
	int m_iIsLocal;
	InterfaceEntity *m_pInterfaceEntity;
public:
	ComponentInterfaceDesc();
	~ComponentInterfaceDesc();

	int setName(const string Name);
	int setName(const char * Name);
	string getName();

	void setRole(int Role);
	int getRole();

	void setIsLocal(int IsLocal);
	int getIsLocal();

	int setInterfaceEntity(InterfaceEntity *InterfaceIndex);
	InterfaceEntity *getInterfaceEntity();

};

class ComponentEntity : public CDLEntity
{
private:
	//vector <ComponentParamDesc *> m_listParam;
	//vector <ComponentAttrDesc *> m_listAttr;
	vector <ComponentInterfaceDesc *> m_listInterface;
	ComponentInterfaceDesc *pDefaultInterface;
	int UI_ServiceFlag;//廉伟杰  ui构件为2 service构件为1
	void Destroy();
public:
	vector <ComponentPortDesc *> m_listPort;
	~ComponentEntity();
	int set_pDefaultInterface(ComponentInterfaceDesc *p);
	ComponentInterfaceDesc* get_pDefaultInterface();
	//bool DuplicatedParam(const string Name);
	//bool DuplicatedParam(const char * Name);
	//int AppendParam(ComponentParamDesc *ParamDesc);

	//bool DuplicatedAttr(const string Name);
	//bool DuplicatedAttr(const char * Name);
	//int AppendAttr(ComponentAttrDesc *AttrDesc);

	bool DuplicatedPort(const string Name);
	bool DuplicatedPort(const char * Name);
	int AppendPort(ComponentPortDesc *PortDesc);

	bool DuplicatedInterface(const string Name);
	bool DuplicatedInterface(const char * Name);
	int AppendInterface(ComponentInterfaceDesc *InterfaceDesc);
	void set_UI_ServiceFlag(int flag);//廉伟杰 
	int get_UI_ServiceFlag();//廉伟杰 
	void CodeGeneration(FILE *fpHeader, FILE *fpSource, FILE *fpIDL);
	//lian add 2016.8.25
	void ComHeardGeneration(FILE *fpHeader);//服务构件头文件的C++代码
	void ComSourceGeneration(FILE *fpSource);//服务构件源程序cpp的c++代码
	//void UiComHeardGeneration(FILE *fpHeader);//界面构件头文件的C++代码
	//void UiComSourceGeneration(FILE *fpSource);//界面构件源程序cpp的c++代码
	void ComSourceOnDdsEventGeneration(FILE *fpSource);//构件源程序cpp中OnMsgEvent函数c++代码
	//自己添加的函数
	vector <ComponentInterfaceDesc *> GetInterfaceList()const;
};





class CDLFile
{
private:
	vector <CDLEntity *> m_listCDLEntity;
public:
	~CDLFile ( );

	bool DuplicatedCDLEntity(const string Name);
	bool DuplicatedCDLEntity(const char * Name);

	CDLEntity *FindEntityIndex(const string Name);

	int AppendCDLEntity(CDLEntity *Entity);
	//djc add IDL
	void GenerateBasicEntity(FILE *fpHeader, FILE *fpSource,FILE *IDL);
	void GenerateComponentEntity(string ComDir);
	//lian add
	vector <CDLEntity *> GetCDLEntityList()const;
	void ClearCdlEntityList(){
		m_listCDLEntity.clear();
	}
};

/**************** Define Global Variables Below ****************************/
EXTERN CDLFile cdl_file;

EXTERN string CurrPackage;

EXTERN bool InComponent;

#endif