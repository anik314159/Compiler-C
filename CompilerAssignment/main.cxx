#include "header_ast.h"
extern FILE* yyin;
extern int yyparse();
extern int yylex();
extern int yylineno;
extern char* yytext;
extern void yyerror(const char*);
#include "parser.tab.h"

std::vector<identifier* > symtab;
char *strdup(char *src)
{
	int len = strlen(src);
	char *retStr = (char*) malloc((len+1) *sizeof(char));
	strcpy(retStr,src);
	return retStr;
}

int main(int argc, char*argv[])
{
	if (argc > 1)
	{
		yyin = fopen(argv[1],"r");
	}
	else
	{
		yyin = stdin;
	}


	yyparse();
	return 0;
}

void assignaction(char *name, EvalType* val)
{
	identifier* id = new identifier(name,val);
	symtab.push_back(id);

};

expr* create_int(int val)
{
	EvalType *evl = new EvalType(val);
	constant* con = new constant(evl);
	return con;
}
expr* create_flt(float val)
{
	EvalType *evl = new EvalType(val);
	constant *con = new constant(evl);
	return con;
}

expr* verifyVal(char *name)
{
	for(std::vector<identifier*>::iterator it = symtab.begin(); it != symtab.end() ; ++it)
	{
		if(strcmp((*it)->getName(),name) == 0)
			return *it;

	}

	return NULL;
}

expr* operation_control(expr *lhs,expr *rhs, opType op)
{
	return new bin_expr(lhs,rhs,op);
}
