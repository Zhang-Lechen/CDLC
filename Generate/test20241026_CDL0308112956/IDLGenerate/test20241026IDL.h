

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from test20241026IDL.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef test20241026IDL_140137780_h
#define test20241026IDL_140137780_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *HelloWorldTYPENAME;

}

struct HelloWorldSeq;
#ifndef NDDS_STANDALONE_TYPE
class HelloWorldTypeSupport;
class HelloWorldDataWriter;
class HelloWorldDataReader;
#endif

class HelloWorld 
{
  public:
    typedef struct HelloWorldSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef HelloWorldTypeSupport TypeSupport;
    typedef HelloWorldDataWriter DataWriter;
    typedef HelloWorldDataReader DataReader;
    #endif

    DDS_Char *   msg ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* HelloWorld_get_typecode(void); /* Type code */

DDS_SEQUENCE(HelloWorldSeq, HelloWorld);                                        

NDDSUSERDllExport
RTIBool HelloWorld_initialize(
    HelloWorld* self);

NDDSUSERDllExport
RTIBool HelloWorld_initialize_ex(
    HelloWorld* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool HelloWorld_initialize_w_params(
    HelloWorld* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void HelloWorld_finalize(
    HelloWorld* self);

NDDSUSERDllExport
void HelloWorld_finalize_ex(
    HelloWorld* self,RTIBool deletePointers);

NDDSUSERDllExport
void HelloWorld_finalize_w_params(
    HelloWorld* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void HelloWorld_finalize_optional_members(
    HelloWorld* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool HelloWorld_copy(
    HelloWorld* dst,
    const HelloWorld* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *PostDataTYPENAME;

}

struct PostDataSeq;
#ifndef NDDS_STANDALONE_TYPE
class PostDataTypeSupport;
class PostDataDataWriter;
class PostDataDataReader;
#endif

class PostData 
{
  public:
    typedef struct PostDataSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef PostDataTypeSupport TypeSupport;
    typedef PostDataDataWriter DataWriter;
    typedef PostDataDataReader DataReader;
    #endif

    DDS_Long   a ;
    DDS_Long   b ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* PostData_get_typecode(void); /* Type code */

DDS_SEQUENCE(PostDataSeq, PostData);                                        

NDDSUSERDllExport
RTIBool PostData_initialize(
    PostData* self);

NDDSUSERDllExport
RTIBool PostData_initialize_ex(
    PostData* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool PostData_initialize_w_params(
    PostData* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void PostData_finalize(
    PostData* self);

NDDSUSERDllExport
void PostData_finalize_ex(
    PostData* self,RTIBool deletePointers);

NDDSUSERDllExport
void PostData_finalize_w_params(
    PostData* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void PostData_finalize_optional_members(
    PostData* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool PostData_copy(
    PostData* dst,
    const PostData* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *add_retTYPENAME;

}

struct add_retSeq;
#ifndef NDDS_STANDALONE_TYPE
class add_retTypeSupport;
class add_retDataWriter;
class add_retDataReader;
#endif

class add_ret 
{
  public:
    typedef struct add_retSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef add_retTypeSupport TypeSupport;
    typedef add_retDataWriter DataWriter;
    typedef add_retDataReader DataReader;
    #endif

    DDS_Double   result ;
    HelloWorld   a ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* add_ret_get_typecode(void); /* Type code */

DDS_SEQUENCE(add_retSeq, add_ret);                                        

NDDSUSERDllExport
RTIBool add_ret_initialize(
    add_ret* self);

NDDSUSERDllExport
RTIBool add_ret_initialize_ex(
    add_ret* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool add_ret_initialize_w_params(
    add_ret* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void add_ret_finalize(
    add_ret* self);

NDDSUSERDllExport
void add_ret_finalize_ex(
    add_ret* self,RTIBool deletePointers);

NDDSUSERDllExport
void add_ret_finalize_w_params(
    add_ret* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void add_ret_finalize_optional_members(
    add_ret* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool add_ret_copy(
    add_ret* dst,
    const add_ret* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *add_paramsTYPENAME;

}

struct add_paramsSeq;
#ifndef NDDS_STANDALONE_TYPE
class add_paramsTypeSupport;
class add_paramsDataWriter;
class add_paramsDataReader;
#endif

class add_params 
{
  public:
    typedef struct add_paramsSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef add_paramsTypeSupport TypeSupport;
    typedef add_paramsDataWriter DataWriter;
    typedef add_paramsDataReader DataReader;
    #endif

    HelloWorld   a ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* add_params_get_typecode(void); /* Type code */

DDS_SEQUENCE(add_paramsSeq, add_params);                                        

NDDSUSERDllExport
RTIBool add_params_initialize(
    add_params* self);

NDDSUSERDllExport
RTIBool add_params_initialize_ex(
    add_params* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool add_params_initialize_w_params(
    add_params* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void add_params_finalize(
    add_params* self);

NDDSUSERDllExport
void add_params_finalize_ex(
    add_params* self,RTIBool deletePointers);

NDDSUSERDllExport
void add_params_finalize_w_params(
    add_params* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void add_params_finalize_optional_members(
    add_params* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool add_params_copy(
    add_params* dst,
    const add_params* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *minus_retTYPENAME;

}

struct minus_retSeq;
#ifndef NDDS_STANDALONE_TYPE
class minus_retTypeSupport;
class minus_retDataWriter;
class minus_retDataReader;
#endif

class minus_ret 
{
  public:
    typedef struct minus_retSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef minus_retTypeSupport TypeSupport;
    typedef minus_retDataWriter DataWriter;
    typedef minus_retDataReader DataReader;
    #endif

    DDS_Double   result ;
    DDS_Double   b ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* minus_ret_get_typecode(void); /* Type code */

DDS_SEQUENCE(minus_retSeq, minus_ret);                                        

NDDSUSERDllExport
RTIBool minus_ret_initialize(
    minus_ret* self);

NDDSUSERDllExport
RTIBool minus_ret_initialize_ex(
    minus_ret* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool minus_ret_initialize_w_params(
    minus_ret* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void minus_ret_finalize(
    minus_ret* self);

NDDSUSERDllExport
void minus_ret_finalize_ex(
    minus_ret* self,RTIBool deletePointers);

NDDSUSERDllExport
void minus_ret_finalize_w_params(
    minus_ret* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void minus_ret_finalize_optional_members(
    minus_ret* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool minus_ret_copy(
    minus_ret* dst,
    const minus_ret* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
extern "C" {

    extern const char *minus_paramsTYPENAME;

}

struct minus_paramsSeq;
#ifndef NDDS_STANDALONE_TYPE
class minus_paramsTypeSupport;
class minus_paramsDataWriter;
class minus_paramsDataReader;
#endif

class minus_params 
{
  public:
    typedef struct minus_paramsSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef minus_paramsTypeSupport TypeSupport;
    typedef minus_paramsDataWriter DataWriter;
    typedef minus_paramsDataReader DataReader;
    #endif

    DDS_Double   a ;
    DDS_Double   b ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* minus_params_get_typecode(void); /* Type code */

DDS_SEQUENCE(minus_paramsSeq, minus_params);                                        

NDDSUSERDllExport
RTIBool minus_params_initialize(
    minus_params* self);

NDDSUSERDllExport
RTIBool minus_params_initialize_ex(
    minus_params* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool minus_params_initialize_w_params(
    minus_params* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void minus_params_finalize(
    minus_params* self);

NDDSUSERDllExport
void minus_params_finalize_ex(
    minus_params* self,RTIBool deletePointers);

NDDSUSERDllExport
void minus_params_finalize_w_params(
    minus_params* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void minus_params_finalize_optional_members(
    minus_params* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool minus_params_copy(
    minus_params* dst,
    const minus_params* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* test20241026IDL */

