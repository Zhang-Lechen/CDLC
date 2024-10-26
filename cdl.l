%{
#include <string>
#include <iostream>
#include <stdlib.h>
#include "cdl_tab.h"
using namespace std;
extern string gCurrentHandleFileName;
extern int yyerrornumber;

%}

%option yylineno

%%
[Tt][Rr][Ee][Ee]																{ return TREE; }
[Ss][Ee][Qq][Uu][Ee][Nn][Cc][Ee]												{ return SEQUENCE; }
[Ll][Oo][Cc][Aa][Ll]															{ return LOCAL; }
[Oo][Nn][Ee][Ww][Aa][Yy]														{ return ONEWAY; }
[Uu][Ii]																		{ return UI; }
[Ss][Ee][Rr][Vv][Ii][Cc][Ee]													{ return SERVICE; }
[Ii][Mm][Pp][Oo][Rr][Tt]														{ return IMPORT; }
[Cc][Dd][Ll]																	{ return CDL; }
[Ee][Nn][Uu][Mm]															  	{ return ENUM;}
[Ss][Tt][Rr][Uu][Cc][Tt]														{ return STRUCT; }
[Uu][Nn][Ii][Oo][Nn]															{ return UNION;}
[Pp][Oo][Rr][Tt]																{ return PORT;}
[Ii][Nn][Tt][Ee][Rr][Ff][Aa][Cc][Ee]											{ return INTERFACE;}
[Cc][Oo][Mm][Pp][Oo][Nn][Ee][Nn][Tt]											{ return COMPONENT;}


[Cc][Oo][Nn][Ss][Uu][Mm][Ee]													{ return CONSUME;}
[Pp][Uu][Bb][Ll][Ii][Ss][Hh]													{ return PUBLISH;}
[Pp][Rr][Oo][Vv][Ii][Dd][Ee]													{ return PROVIDE;}
[Rr][Ee][Qq][Uu][Ii][Rr][Ee]													{ return REQUIRE;}
[Ii][Nn]																		{ return IN;}
[Oo][Uu][Tt]																	{ return OUT;}
[Ii][Nn][Oo][Uu][Tt]															{ return INOUT;}


[Ss][Hh][Oo][Rr][Tt]															{ return SHORT;}
[u][n][s][i][g][n][e][d][ ][Ss][Hh][Oo][Rr][Tt]									{ return UNSIGNEDSHORT;}
[Ll][Oo][Nn][Gg]								  								{ return LONG;}
[u][n][s][i][g][n][e][d][ ][Ll][Oo][Nn][Gg]										{ return UNSIGNEDLONG;}
[Ll][Oo][Nn][Gg][ ][Ll][Oo][Nn][Gg]				  								{ return LONGLONG;}
[u][n][s][i][g][n][e][d][ ][Ll][Oo][Nn][Gg][ ][Ll][Oo][Nn][Gg]					{ return UNSIGNEDLONGLONG;}
[Cc][Hh][Aa][Rr]								  								{ return CHAR;}
[Bb][Oo][Oo][Ll][Ee][Aa][Nn]					  								{ return BOOLEAN;}
[Ff][Ll][Oo][Aa][Tt]															{ return FLOAT;}
[Dd][Oo][Uu][Bb][Ll][Ee]														{ return DOUBLE; }
[Oo][Cc][Tt][Ee][Tt]															{ return OCTET;}
[Ss][Tt][Rr][Ii][Nn][Gg]														{ return STRING;}
[Vv][Oo][Ii][Dd]																{ return VOID;}

"::"																			{ return NAME_DELIMITER; }
"{"																				{ return '{';}
"}"																				{ return '}';}
";"																				{ return ';';}
"\\"																			{ return '\\';}
"<"																				{ return '<';}
">"																				{ return '>';}
"\."																			{ return '.';}
","																				{ return ',';}
"("																				{ return '(';}
")"																				{ return ')';}
"="																				{ return '=';}
"["																				{ return '[';}
"]"																				{ return ']';}
"-"																				{ return '-';}

[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?				{
														strcpy(yylval.StrVal,yytext);
														return NUMBER;
													}
[a-zA-Z_][a-zA-Z0-9_]*								{   
														strcpy(yylval.StrVal,yytext);
							
														return Identifier;
													}
[0-9]+/[ \t]*['>']                                  {
	                                                  yylval.IntVal=atoi(yytext);
													   return VECNUM;
                                                    }
[ \t\r\n]			{}
"//".*\n                {}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"	 {}
.													{
														strcpy(yylval.StrVal,yytext);
														return Identifier;
													}


%%

int yywrap(void)
{
   return 1;
}

int yyerror(char *msg)
{
   printf("%s; at %s(%d)\n", msg,gCurrentHandleFileName.c_str(),yylineno);
   yyerrornumber++;
   return 1;
}

int isatty(int x)
{
	return(0);
}