%{
/****************************************************************************
CDL_08.y

YACC file defined by WU Jian .

Date: April 29, 2014
****************************************************************************/
%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

// place any declarations here

%start CDL_declare

%token Identifier LOCAL ONEWAY CDL NUMBER NAME_DELIMITER IMPORT
%token VOID IN OUT INOUT
%token SHORT UNSIGNEDSHORT LONG UNSIGNEDLONG LONGLONG UNSIGNEDLONGLONG FLOAT DOUBLE CHAR BOOLEAN OCTET STRING SEQUENCE 
%token CONSUME PUBLISH PROVIDE REQUIRE UI SERVICE
%token PARAMETER ATTRIBUTE PORT INTERFACE COMPONENT STRUCT UNION ENUM TREE VECNUM

%{

#include "cdl.h"
#include "Parse.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#define YYDEBUG 1

int yylex();
int yyerror(char *msg);

%}

%union
{
  char StrVal[255];
  int IntVal;
  double DoubleVal;
  TypeIndex *pTypeIndex;
  OperationDesc *pOperation;
}

%type <StrVal> Identifier
%type <IntVal> fundamental_type_name
%type <StrVal> qualified_type_name
%type <StrVal> NUMBER

%type <pOperation> operation
%type <pOperation> one_way_option
%type <pOperation> operation_head
%type <pTypeIndex> type_specifier
%type <pTypeIndex> return_type

%type <IntVal> in_out_specifier
%type <StrVal> parameter_name

%type <IntVal> component_specifier
%type <StrVal> port_name

%type <StrVal> data_range
%type <StrVal> range_list
%type <StrVal> range
%type <StrVal> number_and_hyphen

%type <IntVal> pub_sub_specifier
%type <IntVal> local_option
%type <IntVal> role_specifier

%type <StrVal> interface_name

%type <IntVal> VECNUM


%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your YACC rules here (there must be at least one)

///////// Fundamental type declaration ////////////////
fundamental_type_name : SHORT                 { $$ = T_SHORT; }
                      | UNSIGNEDSHORT         { $$ = T_UNSINGED_SHORT; }
		              | LONG                  { $$ = T_LONG; }
		              | UNSIGNEDLONG          { $$ = T_UNSIGNED_LONG; }
		              | LONGLONG              { $$ = T_LONG_LONG; }
		              | UNSIGNEDLONGLONG      { $$ = T_UNSIGNED_LONG_LONG; }
		              | FLOAT                 { $$ = T_FLOAT; }
		              | DOUBLE                { $$ = T_DOUBLE; }
		              | CHAR                  { $$ = T_CHAR; }
		              | BOOLEAN               { $$ = T_BOOLEAN; }
		              | OCTET                 { $$ = T_OCTET; }
		              | STRING                { $$ = T_STRING; }
					  | SEQUENCE			  { $$ = T_VECTOR; }
		              ;



CDL_declare : Import_list CDO_type_decl_list
            ;
			
Import_list	:
			|	Import_list Import_File
			;
			
Import_File	:	IMPORT '<' File_Name '>'
			;

File_Name	:	Identifier '.' CDL
			;
CDO_type_decl_list :
				   | CDO_type_decl_list CDO_type_decl
				   ;
CDO_type_decl : enumeration_decl ';'
 //             | vector_decl ';'
              | struct_decl ';'
	          | union_decl ';'
	          | tree_decl ';'
	          | interface_decl ';'
	          | port_decl ';'
	          | component_decl ';'
	          ;

///////////////////// Enumeration declaration below ////////////////

enumeration_decl : ENUM enum_name '{' enumeration_body '}'
                 ;
enum_name : Identifier
			{
				CreateENumEntity($1);
			}
          ;
enumeration_body : enum_member_list
                 ;
enum_member_list : enum_value   /* enum_member found */
                 | enum_member_list ',' enum_value
				 ;
enum_value : Identifier
			 {
				 AppendValueName($1);
			 }
           ;
///////////////////// Vector declaration below ////////////////
vector_decl : SEQUENCE '<' fundamental_type_name'>' vector_name 
              {
				 RecordVectorSimpleType($3);
			  }
		    | SEQUENCE '<' qualified_type_name'>' vector_name 
              {
				  int res;
				  res=RecordVectorComplexType($3);
				  if(res==ERR_FATAL) return ERR_FATAL;
			  }
			| SEQUENCE '<'fundamental_type_name ',' VECNUM '>' vector_name 
              {
				 RecordVectorSimpleType($3,$5);
			  }
			| SEQUENCE '<' qualified_type_name ',' VECNUM'>' vector_name 
              {
				  int res;
				  res=RecordVectorComplexType($3,$5);
				  if(res==ERR_FATAL) return ERR_FATAL;
			  }
            ;
	
vector_name : Identifier
              {
				  CreateVectorEntity($1);
			  }
			; 
//////////// Structure declaration below ///////////
struct_decl : STRUCT struct_name '{' data_member_list '}'
            ;
struct_name : Identifier
			  {
				  CreateStructEntity($1);
			  }
            ;
//////////// Union declaration below ///////////
union_decl : UNION union_name '{' data_member_list '}'
            ;
union_name : Identifier
			  {
				  CreateUnionEntity($1);
			  }
           ;
data_member_list : data_member
                 | data_member_list data_member
                 ;

data_member : fundamental_type_name Identifier ';'
			  {
				  AddFundamentalDataMember($1, $2);
			  }
            | qualified_type_name Identifier ';'
			  {
				  int res;
				  res = AddComplexDataMember($1, $2);
				  if (res == ERR_FATAL) return ERR_FATAL;
			  }
            ;
tree_decl : TREE '<' fundamental_type_name '>' tree_name
			{
			      RecordTreeSimpleType($3);
			}
          | TREE '<' qualified_type_name '>' tree_name
            {
			      int res;
			      res = RecordTreeComplexType($3);
			      if (res == ERR_FATAL) return res;
			}
			;
tree_name : Identifier
			  {
				  CreateTreeEntity($1);
			  }
            ;

//////////// (Data_port declaration below ///////////
port_decl : PORT port_type_name  port_data_type data_range  
            {
				int res;
				res=LoadPortDataRange($4);
				if(res == ERR_FATAL) return res;
			}
          ;
port_type_name : Identifier
				 {
					 CreatePortEntity($1);
				 }
               ;
port_data_type : fundamental_type_name
				 {
					 RecordPortSimpleType($1);
				 }
               | qualified_type_name
			     {
					 int res;
					 res = RecordPortComplexType($1);
					 if (res == ERR_FATAL) return res;
			     }
               ;
data_range :                        {strcpy_s($$,"");}
		   | '(' range_list ')'     {string str="("+string($2)+")";strcpy_s($$,str.c_str());}
           ;
range_list : range                  {strcpy_s($$,$1);}
           | range_list ',' range   {string str=string($1)+","+string($3);strcpy_s($$,str.c_str());}
           ;
range : '[' number_and_hyphen ',' number_and_hyphen ']'     {string str="["+string($2)+","+string($4)+"]"; strcpy_s($$,str.c_str());}
	  | '(' range_list ')'         {string str="("+string($2)+")";strcpy_s($$,str.c_str());}
	  ;
number_and_hyphen : NUMBER         {strcpy_s($$,$1);}
				  | '-'            {strcpy_s($$,"-");}
				  | '-' NUMBER     {string str="-"+string($2); strcpy_s($$,str.c_str());}
				  ;

/////////////// Interface declaration below ///////////////////
interface_decl : INTERFACE interface_type_name '{' operation_list '}'
               ;
interface_type_name : Identifier
				 {
					 CreateInterfaceEntity($1);
				 }
               ;
operation_list : operation                   {AddOperation($1);}
               | operation_list operation    {AddOperation($2);}
               ;
operation : operation_head  '(' parameter_list ')' ';' {$$=$1;}
          ;
operation_head : one_way_option return_type operation_name
				 {
					 SetOperationReturnType($2);
					 $$=$1;
				 }
			   ;
operation_name : Identifier
				 {
					 SetOperationName($1);
					 /* At the same time, operation is appended to CurrInterfaceEntity */
				 }
               ;
one_way_option :
				 {
					 $$=CreateOperation(M_NON_ONEWAY);
				 }
               | ONEWAY
			     {
					 $$=CreateOperation(M_ONEWAY);
			     }
               ;

type_specifier : fundamental_type_name
				 {
					 TypeIndex *tp;
					 tp = new TypeIndex();
					 tp->m_iType = $1;
					 $$ = tp;
				 }
               | qualified_type_name
			     {
					 TypeIndex *tp;;
					 tp = CreateTypeIndex($1);
					 if (tp == NULL) 
						 {
							 delete CurrOperation;
							 return ERR_FATAL;
					     }
					 $$ = tp;
					 /* Attention: Cannot attach type index to current operation's return type */
			     }  
               ;

return_type : type_specifier
			  {
				  $$ = $1;
			  }
            | VOID
			  {
				  TypeIndex *tp;
				  tp = new TypeIndex();
				  tp->m_iType = T_VOID;
				  $$ = tp;
			  }
            ;
parameter_list :
               | parameter
               | parameter_list ',' parameter
               ;
parameter : in_out_specifier type_specifier parameter_name data_range
			{
				int res;
				res=AppendParameter($1, $2, $3, $4);
				if(res==ERR_FATAL)return ERR_FATAL;
			}
          ;
parameter_name : Identifier
				 {
					 strcpy($$ , $1);
				 }
               ;
in_out_specifier : IN
				   {
					   $$ = M_IN;
				   }
                 | OUT
				   {
					   $$ = M_OUT;
				   }
                 | INOUT
				   {
					   $$ = M_INOUT;
				   }
                 ;

component_decl : component_specifier COMPONENT component_name '{' component_body '}'{setComFlag($1);setComOpFlag(false);}
               ;
component_specifier : UI
				      {
						  setComOpFlag(true);
					      $$ = M_UI;
				      }
                    | SERVICE
				      {
						  setComOpFlag(true);
					      $$ = M_SERVICE;
				      }
                    ;
component_name : Identifier
				 {
					 CreateComponentEntity($1);
				 }
               ;
component_body : op_port_interface_list
               ;
op_port_interface_list : op_port_interface
                       | op_port_interface_list op_port_interface
                       ;
op_port_interface : op_member /*此处不要需要分号；，在operation规约时已经考虑*/
                  | port_member ';'
                  | interface_member ';'
               ;
op_member : operation    {AddFunToDefaultInterface($1);}
          ; 
port_member : pub_sub_specifier local_option qualified_type_name port_name 
			  {
				  AppendPortDesc($1, $2, $3, $4);
			  }
            ; 
port_name : Identifier
			{
				strcpy($$, $1);
			}
          ;
pub_sub_specifier : CONSUME
					{
						$$ = M_CONSUME;
					}
                  | PUBLISH
					{
						$$ = M_PUBLISH;
					}
                  ;
local_option :
				  {
					  $$ = M_NON_LOCAL;
				  }
             | LOCAL
				  {
					  $$ = M_LOCAL;
				  }
             ;

interface_member : role_specifier local_option qualified_type_name interface_name
				  {
					  AppendInterfaceDesc($1, $2, $3, $4);
				   }
                 ;
interface_name : Identifier
			{
				strcpy($$, $1);
			}
          ;
role_specifier : PROVIDE
					{
						$$ = M_PROVIDE;
					}
               | REQUIRE
					{
						$$ = M_REQUIRE;
					}
               ;
/////////  name_post_option declaration  , 2011.09.18 ////////////
qualified_type_name : Identifier
					  {
						  strcpy($$, $1);
					  }
                   | qualified_type_name NAME_DELIMITER Identifier
				     {
						 strcat($$, "::");
						 strcat($$, $3);
				     }
                   ;

%%

