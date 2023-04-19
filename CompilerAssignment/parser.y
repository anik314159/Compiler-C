%{
#include "header_ast.h"
void yyerror(const char*);
#define YYERROR_VERBOSE 1
extern int yylex();
extern int yylineno;
//extern char* lineptr;
extern char* yytext;
%}

%define parse.error verbose 

%union
{
	int intVal;
	float floatVal;
	expr *expr_t;
	char *strVal;

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
%token SEM_MISS
%token NOT AND OR

%left GTE LTE EQ NE GT LT
%left ADD SUB
%left MUL DIV
%right EXPOP
%right ASSIGN
%left OR
%left AND
%right NOT

%nonassoc IFX
%nonassoc ELSE
%type <strVal> FLTIDENT INTIDENT
%type <intVal> INTCONST 

%type <floatVal> FLTCONST 
%type <expr_t> expr
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

assignment: FLTIDENT ASSIGN expr ';' 
{
	printf("In flt assign\n");
	EvalType* ptr = $3->evaluate();
	ptr->typecastFloat();
	assignaction($1,ptr);
	ptr->showVal();
	
}

|INTIDENT ASSIGN expr ';'
{
	printf("in int assign\n");
	EvalType* ptr = $3->evaluate();
	/*deliberately not adding a explicit mode typecast*/
	ptr->typecastInt();
	assignaction($1,ptr);
	ptr->showVal();
}

;


expr:FLTIDENT
{
	printf("In fltident rule\n");	
	if (verifyVal($1) == NULL)
	{
		yyerror("This variable does not exist in the table");
	}
	$$ = verifyVal($1);
}
|INTIDENT
{
	printf("In intident\n");
	if (verifyVal($1) == NULL)
	{
		yyerror("This variable does not exist in the table");
	}
	$$ = verifyVal($1);
}
|FLTCONST
{	printf("In fltconst rule\n");
	$$ = create_flt($1);
}
|INTCONST
{
	printf("In intconst rule\n");
	$$ = create_int($1);
}
|expr ADD expr
{
	printf("In Add rule\n");
	$$ = operation_control($1,$3,op_plus);
}
|expr SUB expr
{
	printf("In Sub rule\n");
	$$ = operation_control($1,$3,op_minus);

}
|expr MUL expr
{
	printf("In Mul rule\n");
	$$ = operation_control($1,$3,op_multiply);
}
|expr DIV expr
{
	printf("In Div rule\n");
	$$ = operation_control($1,$3,op_divide);
}
|expr EXPOP expr
{
	printf("In Exp rule\n");
	$$ = operation_control($1,$3,op_exp);
}
|expr GT expr
{
	printf("In GT rule\n");
	$$ = operation_control($1,$3,op_gt);
}
|expr GTE expr
{
	printf("In GTE rule\n");
	$$ = operation_control($1,$3,op_ge);
}
|expr LT expr
{
	printf("In LT rule\n");
	$$ = operation_control($1,$3,op_lt);
}
|expr LTE expr
{
	printf("In LTE rule\n");
	$$ = operation_control($1,$3,op_le);
}
|expr NE expr
{
	printf("In NE rule\n");
	$$ = operation_control($1,$3,op_ne);
}
|expr EQ expr
{
	printf("In EQ rule\n");
	$$ = operation_control($1,$3,op_eq);
}
|NOT expr
{
	$$ = $2;
}
|expr AND expr
|expr OR expr	
| '(' expr ')'
{
	$$ = $2;	
}



%%

void yyerror(const char* str)
{
	printf("error:%s  line no:%i \n ",str,yylineno);
	exit(-1);

}

