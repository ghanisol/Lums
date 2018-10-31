/* PHP Parser */
/* Muhammad Faizan Ul Ghani	18100279 */
/* Mubeen Zulfiqar	18100211 */



%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>


	extern FILE *yyin;
	extern FILE *yyout;

	char *prev;
	
%}


/* Declare Tokens */

%token _IF _ELSEIF _ELSE _DO _WHILE _ECHO _FUNCTION _ARRAY
%token _NUMBER _ID _STRING 
%token _ADD _SUB _MUL _DIV _MOD
%token _GT _LT _EEQ _EQ _NEQ
%token _OP _CP _OB _CB _OT _CT
%token _COMMA _SEMICOLON

%union {
	char *str;
	int number; 
};

%token <str> _FUNCNAME


%%
/* Grammer Rules */

php : /* nothing */
	| php element
	;

element : stmt 
	;

stmt : _ID _EQ exp _SEMICOLON	
	| _ECHO exp _SEMICOLON	
	| _IF _OP exp _CP _OB stmts _CB		
	| _IF _OP exp _CP _OB stmts _CB _ELSE _OB stmts _CB		
	| _IF _OP exp _CP _OB stmts _CB _ELSEIF _OP exp _CP _OB stmts _CB _ELSE _OB stmts _CB	
	| _DO _OB stmts _CB _WHILE _OP exp _CP	
	| _FUNCTION _FUNCNAME  { prev = $2; } _OP optparams _CP _OB stmts _CB { prev = "main"; }
	| func_call _SEMICOLON
	| _ID _EQ _ARRAY _OP optparams _CP _SEMICOLON	
	| _ID _OT _NUMBER _CT _EQ exp _SEMICOLON
	| arr_access _SEMICOLON	
	;

stmts : /* nothing */
	| stmt stmts
	;

func_call : _FUNCNAME _OP optparams _CP	{ fprintf(yyout, "%s->%s\n", prev, $1); }
	;

optparams : /* nothing */
	| params
	;

params : exp _COMMA params
	| exp
	;

arr_access : _ID _OT _NUMBER _CT
	;

exp: _ID 	
 	| _NUMBER	
	| _STRING
	| func_call	
	| arr_access 
	| exp bop exp 	
 	| exp cop exp 	
 	| _OP exp _CP 	
  	;

 bop : _ADD 	
 	| _SUB		
 	| _MUL		
 	| _DIV		
 	| _MOD		
 	| _GT		
 	| _LT		
 	;

cop : _EEQ		
	| _NEQ	
	;

%%

main(int argc, char **argv)
{
	if (argc == 1)
		yyparse();

	if (argc == 2)
	{
		yyin = fopen(argv[1], "r");
		yyparse();

	}

	if (argc == 3)
	{
		yyin = fopen(argv[1], "r");
		yyout = fopen(argv[2], "w");
	
		prev = "main";
		fprintf(yyout, "digraph {\n");
		yyparse();
		fprintf(yyout, "}\n");
	}
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}