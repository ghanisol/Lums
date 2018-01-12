/* PHP Lexer */

/* Mubeen Zulfiqar	18100211 */
/* Muhammad Faizan Ul Ghani	18100279 */


%{
    #include "php.tab.h"
%}

%%

"if"                { return _IF; }
"elseif"            { return _ELSEIF; }
"else"              { return _ELSE; }
"do"                { return _DO; }
"while"             { return _WHILE; }
"echo"              { return _ECHO; }
"function"          { return _FUNCTION; }
"array"				{ return _ARRAY; }
[0-9]+              { /*yylval = atoi(yytext);*/ return _NUMBER; }
"$"[a-zA-Z0-9]+     { return _ID; }
["][^\n\r]*["]      { return _STRING; }
[a-z][a-zA-Z0-9]*   { yylval.str = strdup(yytext); return _FUNCNAME; }
"+"                 { return _ADD; }
"-"                 { return _SUB; }
"*"                 { return _MUL; }
"/"                 { return _DIV; }
"%"                 { return _MOD; }
">"                 { return _GT; }
"<"                 { return _LT; }
"=="                { return _EEQ; }
"="                 { return _EQ; }
"!="                { return _NEQ; }
"("                 { return _OP; }
")"                 { return _CP; }
"{"                 { return _OB; }
"}"                 { return _CB; }
"["					{ return _OT; }
"]"					{ return _CT; }
","                 { return _COMMA; }
";"                 { return _SEMICOLON; }
[ \t\n]             { /* ignore whitespace */ }
.                   { printf("Mystery character %c\n", *yytext); }

%%
