#ifndef CDL_TAB_H
#define CDL_TAB_H

#include "cdl.h"
#include "Parse.h"
typedef union
{
  char StrVal[255];
  int IntVal;
  double DoubleVal;
  TypeIndex *pTypeIndex;
  OperationDesc *pOperation;

} YYSTYPE;
#define	Identifier	258
#define	LOCAL	259
#define	ONEWAY	260
#define	CDL	261
#define	NUMBER	262
#define	NAME_DELIMITER	263
#define	IMPORT	264
#define	VOID	265
#define	IN	266
#define	OUT	267
#define	INOUT	268
#define	SHORT	269
#define	UNSIGNEDSHORT	270
#define	LONG	271
#define	UNSIGNEDLONG	272
#define	LONGLONG	273
#define	UNSIGNEDLONGLONG	274
#define	FLOAT	275
#define	DOUBLE	276
#define	CHAR	277
#define	BOOLEAN	278
#define	OCTET	279
#define	STRING	280
#define	CONSUME	281
#define	PUBLISH	282
#define	PROVIDE	283
#define	REQUIRE	284
#define	UI	285
#define	SERVICE	286
#define	PARAMETER	287
#define	ATTRIBUTE	288
#define	PORT	289
#define	INTERFACE	290
#define	COMPONENT	291
#define	STRUCT	292
#define	UNION	293
#define	ENUM	294
#define	TREE	295
#define SEQUENCE  296
#define VECNUM  297
extern YYSTYPE yylval;

#endif
