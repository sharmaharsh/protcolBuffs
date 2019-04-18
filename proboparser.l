%{
#include <stdio.h>
#include <string.h>
#include "proboparser.tab.hpp"

extern "C" {
  int yylex();
}
%}

%%
message                   return MESSAGE;
int32                     return INT32;
int16                     return INT16;
int8                      return INT8;
string\[[0-9]+\]          return STRING_DECL;
\{                        return OBRACE;
\}                        return EBRACE;
=                         return EQUALS;
[0-9]+                    yylval.num=strtoll(yytext, NULL, 10); return NUMBER;
[a-zA-Z][a-zA-Z0-9]*      yylval.str=strdup(yytext); return IDENTIFIER;
;                         return SEMICOLON;
\n                        /* ignore EOL */
[ \t]+                    /* ignore whitespace */
%%
