LIB1=-lfl
LIB2=-ly

all: compiler

compiler:
	flex compiler.l
	bison -d compiler.y
	gcc -c ast.c
	gcc compiler.tab.c lex.yy.c ast.o -o compiler $(LIB1) $(LIB2)

clean: clean-compiler

clean-compiler:
	rm -rf *~ lex.yy.c compiler.tab.h compiler.tab.c compiler ast.o