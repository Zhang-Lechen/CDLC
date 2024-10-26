
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "cdl.y"

/****************************************************************************
CDL_08.y

YACC file defined by WU Jian .

Date: April 29, 2014
****************************************************************************/

/* Line 189 of yacc.c  */
#line 24 "cdl.y"


#include "cdl.h"
#include "Parse.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#define YYDEBUG 1

int yylex();
int yyerror(char *msg);



/* Line 189 of yacc.c  */
#line 101 "cdl_tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     Identifier = 258,
     LOCAL = 259,
     ONEWAY = 260,
     CDL = 261,
     NUMBER = 262,
     NAME_DELIMITER = 263,
     IMPORT = 264,
     VOID = 265,
     IN = 266,
     OUT = 267,
     INOUT = 268,
     SHORT = 269,
     UNSIGNEDSHORT = 270,
     LONG = 271,
     UNSIGNEDLONG = 272,
     LONGLONG = 273,
     UNSIGNEDLONGLONG = 274,
     FLOAT = 275,
     DOUBLE = 276,
     CHAR = 277,
     BOOLEAN = 278,
     OCTET = 279,
     STRING = 280,
     CONSUME = 281,
     PUBLISH = 282,
     PROVIDE = 283,
     REQUIRE = 284,
     UI = 285,
     SERVICE = 286,
     PARAMETER = 287,
     ATTRIBUTE = 288,
     PORT = 289,
     INTERFACE = 290,
     COMPONENT = 291,
     STRUCT = 292,
     UNION = 293,
     ENUM = 294,
     TREE = 295,
     VECTOR = 296,
     VECNUM = 297
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 41 "cdl.y"

  char StrVal[255];
  int IntVal;
  double DoubleVal;
  TypeIndex *pTypeIndex;
  OperationDesc *pOperation;



/* Line 214 of yacc.c  */
#line 189 "cdl_tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 201 "cdl_tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNRULES -- Number of states.  */
#define YYNSTATES  192

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,    51,     2,     2,    49,    54,    45,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
      43,     2,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    30,    31,    34,    39,    43,
      44,    47,    50,    53,    56,    59,    62,    65,    68,    71,
      77,    79,    81,    83,    87,    89,    95,   101,   109,   117,
     119,   125,   127,   133,   135,   137,   140,   144,   148,   154,
     160,   162,   167,   169,   171,   173,   174,   178,   180,   184,
     190,   194,   196,   198,   201,   207,   209,   211,   214,   220,
     224,   226,   227,   229,   231,   233,   235,   237,   238,   240,
     244,   249,   251,   253,   255,   257,   264,   266,   268,   270,
     272,   274,   277,   279,   282,   285,   287,   292,   294,   296,
     298,   299,   301,   306,   308,   310,   312,   314
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    14,    -1,    15,    -1,    16,    -1,    17,
      -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,    22,
      -1,    23,    -1,    24,    -1,    25,    -1,    58,    61,    -1,
      -1,    58,    59,    -1,     9,    43,    60,    44,    -1,     3,
      45,     6,    -1,    -1,    61,    62,    -1,    63,    46,    -1,
      68,    46,    -1,    70,    46,    -1,    72,    46,    -1,    76,
      46,    -1,    85,    46,    -1,    78,    46,    -1,    98,    46,
      -1,    39,    64,    47,    65,    48,    -1,     3,    -1,    66,
      -1,    67,    -1,    66,    49,    67,    -1,     3,    -1,    41,
      43,    56,    44,    69,    -1,    41,    43,   112,    44,    69,
      -1,    41,    43,    56,    49,    42,    44,    69,    -1,    41,
      43,   112,    49,    42,    44,    69,    -1,     3,    -1,    37,
      71,    47,    74,    48,    -1,     3,    -1,    38,    73,    47,
      74,    48,    -1,     3,    -1,    75,    -1,    74,    75,    -1,
      56,     3,    46,    -1,   112,     3,    46,    -1,    40,    43,
      56,    44,    77,    -1,    40,    43,   112,    44,    77,    -1,
       3,    -1,    34,    79,    80,    81,    -1,     3,    -1,    56,
      -1,   112,    -1,    -1,    50,    82,    51,    -1,    83,    -1,
      82,    49,    83,    -1,    52,    84,    49,    84,    53,    -1,
      50,    82,    51,    -1,     7,    -1,    54,    -1,    54,     7,
      -1,    35,    86,    47,    87,    48,    -1,     3,    -1,    88,
      -1,    87,    88,    -1,    89,    50,    94,    51,    46,    -1,
      91,    93,    90,    -1,     3,    -1,    -1,     5,    -1,    56,
      -1,   112,    -1,    92,    -1,    10,    -1,    -1,    95,    -1,
      94,    49,    95,    -1,    97,    92,    96,    81,    -1,     3,
      -1,    11,    -1,    12,    -1,    13,    -1,    99,    36,   100,
      47,   101,    48,    -1,    30,    -1,    31,    -1,     3,    -1,
     102,    -1,   103,    -1,   102,   103,    -1,   104,    -1,   105,
      46,    -1,   109,    46,    -1,    88,    -1,   107,   108,   112,
     106,    -1,     3,    -1,    26,    -1,    27,    -1,    -1,     4,
      -1,   111,   108,   112,   110,    -1,     3,    -1,    28,    -1,
      29,    -1,     3,    -1,   112,     8,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   104,   107,   108,   111,   114,   116,
     117,   119,   120,   121,   122,   123,   124,   125,   126,   131,
     133,   138,   140,   141,   143,   149,   153,   159,   163,   171,
     177,   179,   185,   187,   192,   193,   196,   200,   207,   211,
     218,   225,   232,   237,   241,   248,   249,   251,   252,   254,
     255,   257,   258,   259,   263,   265,   270,   271,   273,   275,
     281,   288,   291,   297,   304,   318,   322,   330,   331,   332,
     334,   341,   346,   350,   354,   360,   362,   367,   373,   378,
     380,   381,   383,   384,   385,   387,   389,   394,   399,   403,
     409,   412,   418,   423,   428,   432,   438,   442
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Identifier", "LOCAL", "ONEWAY", "CDL",
  "NUMBER", "NAME_DELIMITER", "IMPORT", "VOID", "IN", "OUT", "INOUT",
  "SHORT", "UNSIGNEDSHORT", "LONG", "UNSIGNEDLONG", "LONGLONG",
  "UNSIGNEDLONGLONG", "FLOAT", "DOUBLE", "CHAR", "BOOLEAN", "OCTET",
  "STRING", "CONSUME", "PUBLISH", "PROVIDE", "REQUIRE", "UI", "SERVICE",
  "PARAMETER", "ATTRIBUTE", "PORT", "INTERFACE", "COMPONENT", "STRUCT",
  "UNION", "ENUM", "TREE", "VECTOR", "VECNUM", "'<'", "'>'", "'.'", "';'",
  "'{'", "'}'", "','", "'('", "')'", "'['", "']'", "'-'", "$accept",
  "fundamental_type_name", "CDL_declare", "Import_list", "Import_File",
  "File_Name", "CDO_type_decl_list", "CDO_type_decl", "enumeration_decl",
  "enum_name", "enumeration_body", "enum_member_list", "enum_value",
  "vector_decl", "vector_name", "struct_decl", "struct_name", "union_decl",
  "union_name", "data_member_list", "data_member", "tree_decl",
  "tree_name", "port_decl", "port_type_name", "port_data_type",
  "data_range", "range_list", "range", "number_and_hyphen",
  "interface_decl", "interface_type_name", "operation_list", "operation",
  "operation_head", "operation_name", "one_way_option", "type_specifier",
  "return_type", "parameter_list", "parameter", "parameter_name",
  "in_out_specifier", "component_decl", "component_specifier",
  "component_name", "component_body", "op_port_interface_list",
  "op_port_interface", "op_member", "port_member", "port_name",
  "pub_sub_specifier", "local_option", "interface_member",
  "interface_name", "role_specifier", "qualified_type_name", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    60,    62,    46,    59,   123,   125,    44,
      40,    41,    91,    93,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    57,    58,    58,    59,    60,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    63,
      64,    65,    66,    66,    67,    68,    68,    68,    68,    69,
      70,    71,    72,    73,    74,    74,    75,    75,    76,    76,
      77,    78,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    84,    84,    85,    86,    87,    87,    88,    89,
      90,    91,    91,    92,    92,    93,    93,    94,    94,    94,
      95,    96,    97,    97,    97,    98,    99,    99,   100,   101,
     102,   102,   103,   103,   103,   104,   105,   106,   107,   107,
     108,   108,   109,   110,   111,   111,   112,   112
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     2,     4,     3,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     5,
       1,     1,     1,     3,     1,     5,     5,     7,     7,     1,
       5,     1,     5,     1,     1,     2,     3,     3,     5,     5,
       1,     4,     1,     1,     1,     0,     3,     1,     3,     5,
       3,     1,     1,     2,     5,     1,     1,     2,     5,     3,
       1,     0,     1,     1,     1,     1,     1,     0,     1,     3,
       4,     1,     1,     1,     1,     6,     1,     1,     1,     1,
       1,     2,     1,     2,     2,     1,     4,     1,     1,     1,
       0,     1,     4,     1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      15,     0,    19,     1,     0,    16,    14,     0,    86,    87,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
       0,    65,     0,    41,     0,    43,     0,    30,     0,     0,
       0,    21,    22,    23,    24,    25,    27,    26,    28,     0,
       0,    17,   106,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    53,    55,    54,    71,     0,
       0,     0,     0,     0,     0,     0,    88,     0,    18,     0,
      51,     0,    72,    71,    66,     0,     0,     0,     0,    44,
       0,     0,    34,     0,    31,    32,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,    57,   107,    64,    67,
      77,    76,    73,    75,     0,    74,     0,    40,    45,     0,
      42,    29,     0,    50,    48,    49,    39,    35,     0,    36,
       0,    98,    99,   104,   105,    95,     0,    71,    90,    92,
       0,   100,     0,   100,     0,    61,    62,     0,     0,    56,
      82,    83,    84,     0,    78,     0,    70,    69,    46,    47,
      33,     0,     0,    85,    91,    93,   101,     0,    94,     0,
      60,    63,     0,    58,     0,     0,     0,    37,    38,     0,
       0,     0,    79,    68,    81,    55,    97,    96,   103,   102,
      59,    80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    87,     1,     2,     5,    28,     6,    17,    18,    38,
      93,    94,    95,    19,   127,    20,    34,    21,    36,    88,
      89,    22,   124,    23,    30,    66,    80,   105,   106,   147,
      24,    32,    83,   135,    85,   157,    86,   113,   114,   153,
     154,   185,   155,    25,    26,    77,   136,   137,   138,   139,
     140,   187,   141,   167,   142,   189,   143,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -100
static const yytype_int16 yypact[] =
{
    -100,    14,    18,  -100,    -5,  -100,    46,    52,  -100,  -100,
      75,    90,    94,   109,   111,    72,    73,  -100,    71,    74,
      76,    77,    78,    80,    82,    84,    83,    86,    88,  -100,
     126,  -100,    -3,  -100,    87,  -100,    89,  -100,    91,   126,
     126,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,   115,
     127,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,  -100,  -100,  -100,  -100,  -100,   102,   113,   130,   126,
     126,   150,   110,    -1,   -16,    -2,  -100,   108,  -100,    39,
    -100,   153,  -100,     0,  -100,   107,    85,   155,     1,  -100,
      37,    50,  -100,   112,   114,  -100,   156,   156,   158,   120,
     158,   122,     8,    39,    -4,    41,  -100,  -100,  -100,  -100,
      48,  -100,  -100,  -100,   162,   113,   121,  -100,  -100,   123,
    -100,  -100,   150,  -100,  -100,  -100,  -100,  -100,   124,  -100,
     128,  -100,  -100,  -100,  -100,  -100,   118,     3,  -100,  -100,
     125,   166,   129,   166,    45,  -100,   167,   131,    39,  -100,
    -100,  -100,  -100,    62,  -100,   126,  -100,  -100,  -100,  -100,
    -100,   158,   158,  -100,  -100,  -100,  -100,   170,  -100,   170,
    -100,  -100,    -4,  -100,    48,   132,   173,  -100,  -100,    38,
      49,   133,  -100,  -100,  -100,   102,  -100,  -100,  -100,  -100,
    -100,  -100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -100,   -28,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,  -100,    55,  -100,   -99,  -100,  -100,  -100,  -100,   117,
      -9,  -100,    92,  -100,  -100,  -100,    -6,    79,    33,    11,
    -100,  -100,  -100,   -29,  -100,  -100,  -100,    29,  -100,  -100,
      16,  -100,  -100,  -100,  -100,  -100,  -100,  -100,    51,  -100,
    -100,  -100,  -100,    42,  -100,  -100,  -100,   -30
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -90
static const yytype_int16 yytable[] =
{
      67,   129,    65,   145,    52,    82,    81,    81,    82,    73,
      75,    72,    74,    82,     3,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,     4,    98,   131,
     132,   133,   134,    99,   131,   132,   133,   134,     7,    84,
     119,   186,   100,    97,    68,    81,    81,   101,   108,   117,
     146,   -89,   188,    52,   109,    27,   115,    81,   112,   150,
     151,   152,   177,   178,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     8,     9,    29,   118,
      10,    11,   118,    12,    13,    14,    15,    16,    52,   103,
     148,   104,   149,    31,   148,   111,   170,    33,   120,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,   174,    35,   175,    37,    39,    40,    41,    76,    49,
      42,    81,    43,    44,    45,   115,    46,   112,    47,    52,
      48,    50,    51,    78,    69,    82,    70,   179,    71,   180,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    79,    92,    96,   102,   107,   110,   116,   123,
     121,   126,   128,   122,   130,   156,   163,   158,   161,   159,
     166,   165,   162,    52,   171,   168,   184,   160,   183,   191,
     172,   173,   144,   181,   176,   169,   190,    91,   164,   125,
     182
};

static const yytype_uint8 yycheck[] =
{
      30,   100,    30,     7,     3,     5,     8,     8,     5,    39,
      40,    39,    40,     5,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     9,    44,    26,
      27,    28,    29,    49,    26,    27,    28,    29,    43,    68,
       3,     3,    44,    44,    47,     8,     8,    49,    48,    48,
      54,    48,     3,     3,    83,     3,    86,     8,    86,    11,
      12,    13,   161,   162,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    30,    31,     3,    88,
      34,    35,    91,    37,    38,    39,    40,    41,     3,    50,
      49,    52,    51,     3,    49,    10,    51,     3,    48,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    49,     3,    51,     3,    43,    43,    46,     3,    36,
      46,     8,    46,    46,    46,   155,    46,   155,    46,     3,
      46,    45,    44,     6,    47,     5,    47,   167,    47,   169,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    50,     3,    44,    47,     3,    50,     3,     3,
      48,     3,    42,    49,    42,     3,    48,    46,    44,    46,
       4,    46,    44,     3,     7,    46,     3,   122,    46,   185,
      49,   148,   103,   172,   155,   143,    53,    70,   137,    97,
     174
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    58,     0,     9,    59,    61,    43,    30,    31,
      34,    35,    37,    38,    39,    40,    41,    62,    63,    68,
      70,    72,    76,    78,    85,    98,    99,     3,    60,     3,
      79,     3,    86,     3,    71,     3,    73,     3,    64,    43,
      43,    46,    46,    46,    46,    46,    46,    46,    46,    36,
      45,    44,     3,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    56,    80,   112,    47,    47,
      47,    47,    56,   112,    56,   112,     3,   100,     6,    50,
      81,     8,     5,    87,    88,    89,    91,    56,    74,    75,
     112,    74,     3,    65,    66,    67,    44,    44,    44,    49,
      44,    49,    47,    50,    52,    82,    83,     3,    48,    88,
      50,    10,    56,    92,    93,   112,     3,    48,    75,     3,
      48,    48,    49,     3,    77,    77,     3,    69,    42,    69,
      42,    26,    27,    28,    29,    88,   101,   102,   103,   104,
     105,   107,   109,   111,    82,     7,    54,    84,    49,    51,
      11,    12,    13,    94,    95,    97,     3,    90,    46,    46,
      67,    44,    44,    48,   103,    46,     4,   108,    46,   108,
      51,     7,    49,    83,    49,    51,    92,    69,    69,   112,
     112,    84,    95,    46,     3,    96,     3,   106,     3,   110,
      53,    81
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 88 "cdl.y"
    { (yyval.IntVal) = T_SHORT; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 89 "cdl.y"
    { (yyval.IntVal) = T_UNSINGED_SHORT; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 90 "cdl.y"
    { (yyval.IntVal) = T_LONG; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 91 "cdl.y"
    { (yyval.IntVal) = T_UNSIGNED_LONG; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 92 "cdl.y"
    { (yyval.IntVal) = T_LONG_LONG; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 93 "cdl.y"
    { (yyval.IntVal) = T_UNSIGNED_LONG_LONG; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 94 "cdl.y"
    { (yyval.IntVal) = T_FLOAT; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 95 "cdl.y"
    { (yyval.IntVal) = T_DOUBLE; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 96 "cdl.y"
    { (yyval.IntVal) = T_CHAR; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 97 "cdl.y"
    { (yyval.IntVal) = T_BOOLEAN; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 98 "cdl.y"
    { (yyval.IntVal) = T_OCTET; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 99 "cdl.y"
    { (yyval.IntVal) = T_STRING; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 134 "cdl.y"
    {
				CreateENumEntity((yyvsp[(1) - (1)].StrVal));
			;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 144 "cdl.y"
    {
				 AppendValueName((yyvsp[(1) - (1)].StrVal));
			 ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 150 "cdl.y"
    {
				 RecordVectorSimpleType((yyvsp[(3) - (5)].IntVal));
			  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 154 "cdl.y"
    {
				  int res;
				  res=RecordVectorComplexType((yyvsp[(3) - (5)].StrVal));
				  if(res==ERR_FATAL) return ERR_FATAL;
			  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 160 "cdl.y"
    {
				 RecordVectorSimpleType((yyvsp[(3) - (7)].IntVal),(yyvsp[(5) - (7)].IntVal));
			  ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 164 "cdl.y"
    {
				  int res;
				  res=RecordVectorComplexType((yyvsp[(3) - (7)].StrVal),(yyvsp[(5) - (7)].IntVal));
				  if(res==ERR_FATAL) return ERR_FATAL;
			  ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 172 "cdl.y"
    {
				  CreateVectorEntity((yyvsp[(1) - (1)].StrVal));
			  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 180 "cdl.y"
    {
				  CreateStructEntity((yyvsp[(1) - (1)].StrVal));
			  ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 188 "cdl.y"
    {
				  CreateUnionEntity((yyvsp[(1) - (1)].StrVal));
			  ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 197 "cdl.y"
    {
				  AddFundamentalDataMember((yyvsp[(1) - (3)].IntVal), (yyvsp[(2) - (3)].StrVal));
			  ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 201 "cdl.y"
    {
				  int res;
				  res = AddComplexDataMember((yyvsp[(1) - (3)].StrVal), (yyvsp[(2) - (3)].StrVal));
				  if (res == ERR_FATAL) return ERR_FATAL;
			  ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 208 "cdl.y"
    {
			      RecordTreeSimpleType((yyvsp[(3) - (5)].IntVal));
			;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 212 "cdl.y"
    {
			      int res;
			      res = RecordTreeComplexType((yyvsp[(3) - (5)].StrVal));
			      if (res == ERR_FATAL) return res;
			;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 219 "cdl.y"
    {
				  CreateTreeEntity((yyvsp[(1) - (1)].StrVal));
			  ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 226 "cdl.y"
    {
				int res;
				res=LoadPortDataRange((yyvsp[(4) - (4)].StrVal));
				if(res == ERR_FATAL) return res;
			;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 233 "cdl.y"
    {
					 CreatePortEntity((yyvsp[(1) - (1)].StrVal));
				 ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 238 "cdl.y"
    {
					 RecordPortSimpleType((yyvsp[(1) - (1)].IntVal));
				 ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 242 "cdl.y"
    {
					 int res;
					 res = RecordPortComplexType((yyvsp[(1) - (1)].StrVal));
					 if (res == ERR_FATAL) return res;
			     ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 248 "cdl.y"
    {strcpy_s((yyval.StrVal),"");;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 249 "cdl.y"
    {string str="("+string((yyvsp[(2) - (3)].StrVal))+")";strcpy_s((yyval.StrVal),str.c_str());;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 251 "cdl.y"
    {strcpy_s((yyval.StrVal),(yyvsp[(1) - (1)].StrVal));;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 252 "cdl.y"
    {string str=string((yyvsp[(1) - (3)].StrVal))+","+string((yyvsp[(3) - (3)].StrVal));strcpy_s((yyval.StrVal),str.c_str());;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 254 "cdl.y"
    {string str="["+string((yyvsp[(2) - (5)].StrVal))+","+string((yyvsp[(4) - (5)].StrVal))+"]"; strcpy_s((yyval.StrVal),str.c_str());;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 255 "cdl.y"
    {string str="("+string((yyvsp[(2) - (3)].StrVal))+")";strcpy_s((yyval.StrVal),str.c_str());;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 257 "cdl.y"
    {strcpy_s((yyval.StrVal),(yyvsp[(1) - (1)].StrVal));;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 258 "cdl.y"
    {strcpy_s((yyval.StrVal),"-");;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 259 "cdl.y"
    {string str="-"+string((yyvsp[(2) - (2)].StrVal)); strcpy_s((yyval.StrVal),str.c_str());;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 266 "cdl.y"
    {
					 CreateInterfaceEntity((yyvsp[(1) - (1)].StrVal));
				 ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 270 "cdl.y"
    {AddOperation((yyvsp[(1) - (1)].pOperation));;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 271 "cdl.y"
    {AddOperation((yyvsp[(2) - (2)].pOperation));;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 273 "cdl.y"
    {(yyval.pOperation)=(yyvsp[(1) - (5)].pOperation);;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 276 "cdl.y"
    {
					 SetOperationReturnType((yyvsp[(2) - (3)].pTypeIndex));
					 (yyval.pOperation)=(yyvsp[(1) - (3)].pOperation);
				 ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 282 "cdl.y"
    {
					 SetOperationName((yyvsp[(1) - (1)].StrVal));
					 /* At the same time, operation is appended to CurrInterfaceEntity */
				 ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 288 "cdl.y"
    {
					 (yyval.pOperation)=CreateOperation(M_NON_ONEWAY);
				 ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 292 "cdl.y"
    {
					 (yyval.pOperation)=CreateOperation(M_ONEWAY);
			     ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 298 "cdl.y"
    {
					 TypeIndex *tp;
					 tp = new TypeIndex();
					 tp->m_iType = (yyvsp[(1) - (1)].IntVal);
					 (yyval.pTypeIndex) = tp;
				 ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 305 "cdl.y"
    {
					 TypeIndex *tp;;
					 tp = CreateTypeIndex((yyvsp[(1) - (1)].StrVal));
					 if (tp == NULL) 
						 {
							 delete CurrOperation;
							 return ERR_FATAL;
					     }
					 (yyval.pTypeIndex) = tp;
					 /* Attention: Cannot attach type index to current operation's return type */
			     ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 319 "cdl.y"
    {
				  (yyval.pTypeIndex) = (yyvsp[(1) - (1)].pTypeIndex);
			  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 323 "cdl.y"
    {
				  TypeIndex *tp;
				  tp = new TypeIndex();
				  tp->m_iType = T_VOID;
				  (yyval.pTypeIndex) = tp;
			  ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 335 "cdl.y"
    {
				int res;
				res=AppendParameter((yyvsp[(1) - (4)].IntVal), (yyvsp[(2) - (4)].pTypeIndex), (yyvsp[(3) - (4)].StrVal), (yyvsp[(4) - (4)].StrVal));
				if(res==ERR_FATAL)return ERR_FATAL;
			;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 342 "cdl.y"
    {
					 strcpy((yyval.StrVal) , (yyvsp[(1) - (1)].StrVal));
				 ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 347 "cdl.y"
    {
					   (yyval.IntVal) = M_IN;
				   ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 351 "cdl.y"
    {
					   (yyval.IntVal) = M_OUT;
				   ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 355 "cdl.y"
    {
					   (yyval.IntVal) = M_INOUT;
				   ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 360 "cdl.y"
    {setComFlag((yyvsp[(1) - (6)].IntVal));setComOpFlag(false);;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 363 "cdl.y"
    {
						  setComOpFlag(true);
					      (yyval.IntVal) = M_UI;
				      ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 368 "cdl.y"
    {
						  setComOpFlag(true);
					      (yyval.IntVal) = M_SERVICE;
				      ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 374 "cdl.y"
    {
					 CreateComponentEntity((yyvsp[(1) - (1)].StrVal));
				 ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 387 "cdl.y"
    {AddFunToDefaultInterface((yyvsp[(1) - (1)].pOperation));;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 390 "cdl.y"
    {
				  AppendPortDesc((yyvsp[(1) - (4)].IntVal), (yyvsp[(2) - (4)].IntVal), (yyvsp[(3) - (4)].StrVal), (yyvsp[(4) - (4)].StrVal));
			  ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 395 "cdl.y"
    {
				strcpy((yyval.StrVal), (yyvsp[(1) - (1)].StrVal));
			;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 400 "cdl.y"
    {
						(yyval.IntVal) = M_CONSUME;
					;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 404 "cdl.y"
    {
						(yyval.IntVal) = M_PUBLISH;
					;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 409 "cdl.y"
    {
					  (yyval.IntVal) = M_NON_LOCAL;
				  ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 413 "cdl.y"
    {
					  (yyval.IntVal) = M_LOCAL;
				  ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 419 "cdl.y"
    {
					  AppendInterfaceDesc((yyvsp[(1) - (4)].IntVal), (yyvsp[(2) - (4)].IntVal), (yyvsp[(3) - (4)].StrVal), (yyvsp[(4) - (4)].StrVal));
				   ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 424 "cdl.y"
    {
				strcpy((yyval.StrVal), (yyvsp[(1) - (1)].StrVal));
			;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 429 "cdl.y"
    {
						(yyval.IntVal) = M_PROVIDE;
					;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 433 "cdl.y"
    {
						(yyval.IntVal) = M_REQUIRE;
					;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 439 "cdl.y"
    {
						  strcpy((yyval.StrVal), (yyvsp[(1) - (1)].StrVal));
					  ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 443 "cdl.y"
    {
						 strcat((yyval.StrVal), "::");
						 strcat((yyval.StrVal), (yyvsp[(3) - (3)].StrVal));
				     ;}
    break;



/* Line 1455 of yacc.c  */
#line 2222 "cdl_tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 449 "cdl.y"



