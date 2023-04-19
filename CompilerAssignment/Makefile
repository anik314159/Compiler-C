all: comp

comp: lex.yy.c parser.tab.c parser.tab.h header_ast.h Types.h main.cxx
	g++ -g parser.tab.c main.cxx lex.yy.c -o comp -std=c++98

lex.yy.c: tokenizer.l parser.tab.h
	flex tokenizer.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

clean:
	rm comp parser.tab.c parser.tab.h lex.yy.c 




