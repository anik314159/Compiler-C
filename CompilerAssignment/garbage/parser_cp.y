%{
#include "header.h"
void yyerror(const char*);
extern int yylex();
struct symtab
{
	int int_vbltable[1600];
	float flt_vbltable[1600];
};
%}
%union
{
	int intVal;
	float floatVal;
	int vblno;		

}
%token FLTIDENT
%token INTIDENT
%token FLTCONST
%token INTCONST
%token ADD
%token SUB
%token DIV
%token MUL
%token ASSIGN
%token EXPOP
%token GT
%token GTE
%token LT
%token LTE
%token EQ
%token NE
%token IF
%token ELSE
%token WHILE
%token UNKWN

%right ASSIGN
%right EXPOP
%left GTE LTE EQ NE GT LT
%left ADD SUB
%left MUL DIV

%nonassoc IFX
%nonassoc ELSE
%type <intVal> INTCONST intexpr
%type <floatVal> FLTCONST fltexpr

%%
program : stmt
|
;

stmt : ';'
|assignment
|WHILE '(' expr ')' stmt
|IF '(' expr ')' stmt %prec IFX
|IF '(' expr ')' stmt ELSE stmt
|'{' stmt_list '}'
;

stmt_list: stmt
|stmt_list stmt
;

assignment: FLTIDENT ASSIGN fltexpr ';'
|INTIDENT ASSIGN intexpr ';'
;


expr:fltexpr
|intexpr
|expr ADD expr
|expr SUB expr
|expr MUL expr
|expr DIV expr 
|expr GT expr
|expr GTE expr
|expr LT expr
|expr LTE expr
|expr NE expr
|expr EQ expr
|'(' expr ')'
;

fltexpr : FLTCONST
|FLTIDENT
{
	$$ = flt_vbltable
}
;

intexpr : INTCONST
|INTIDENT
;
%%

void yyerror(const char* str)
{
	printf("%s\n",str);
	exit(-1);

}
