%{
#include "header_ast.h"
#include "parser.tab.h"
void yyerror(const char*);

char *lineptr = NULL;
    size_t n = 0;
    size_t consumed = 0;
    size_t available = 0;

    size_t min(size_t a, size_t b);
    /*#define min(a,b) (a<b)? a : b
    #define YY_INPUT(buf,result,max_size) {\
        if(available <= 0) {\
            consumed = 0;\
            available = getline(&lineptr, &n, yyin);\
            if (available < 0) {\
                if (ferror(yyin)) { perror("read error:"); }\
                    available = 0;\
                }\
        }\
        result = min(available, max_size);\
        strncpy(buf, lineptr + consumed, result);\
        consumed += result;\
        available -= result;\
    }*/

%}

%option yylineno

%%
[o-z][0-9][0-9] { yylval.strVal = strdup(yytext);return FLTIDENT;}
[a-n][0-9][0-9] { 	yylval.strVal = strdup(yytext);	return INTIDENT;}

[0-9]+[.][0-9][0-9]* { yylval.floatVal = atof(yytext); return FLTCONST;}
[0-9]|[1-9][0-9]+ { yylval.intVal = atoi(yytext); return INTCONST;} 
"+" { return ADD; }
"-" { return SUB; }
"/" { return DIV; }
"*" { return MUL;}
"=" {  return ASSIGN;}
"^" { return EXPOP;}
">" { return GT;}
">=" { return GTE;}
"<" { return LT;}
"<=" { return LTE;}
"==" { return EQ;}
"!=" { return NE;}
"!" { return NOT;}
"&&" { return AND;}
"||" { return OR;}


[{}().;] { return *yytext;}

[\t\n ] 
"if" { ECHO;return IF;}
"else" { ECHO;return ELSE;} 
"while" { return WHILE;}
. { yyerror("UnkownToken"); return UNKWN;}


%%

int yywrap()
{
	printf("Lexing Finish\n");
	return 1;
}
