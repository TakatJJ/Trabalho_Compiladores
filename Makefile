
run :  asm.o tacs.o SemanticAnalyzer.o Symbols.o AST.o parser.tab.o lex.yy.o main.o 
	g++ main.o lex.yy.o parser.tab.o Symbols.o AST.o SemanticAnalyzer.o tacs.o asm.o -o run 
	

lex.yy.o : lex.yy.cpp
	g++  lex.yy.cpp -c

asm.o : asm.cpp
	g++ asm.cpp -c

tacs.o : tacs.cpp
	g++ tacs.cpp -c

SemanticAnalyzer.o : SemanticAnalyzer.cpp
	g++ SemanticAnalyzer.cpp -c

symbols.o : symbols.cpp
	g++ symbols.cpp -c

AST.o : AST.cpp
	g++ AST.cpp -c

main.o : main.cpp
	g++ main.cpp parser.tab.cpp  -c
lex.yy.cpp : scanner.l
	flex scanner.l
	ren lex.yy.c lex.yy.cpp


parser.tab.cpp : parser.ypp
	bison -d -v --debug -o parser.tab.cpp parser.ypp
	g++ -c parser.tab.cpp

clean :
	del *.o lex.yy.c lex.yy.cpp parser.tab.cpp parser.tab.hpp parser.output run.exe