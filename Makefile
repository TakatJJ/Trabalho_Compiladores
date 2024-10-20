
run :  parser.tab.cpp lex.yy.o main.o
	g++ main.o lex.yy.o -o run 

lex.yy.o : lex.yy.cpp
	g++  lex.yy.cpp -c

main.o : main.cpp
	g++ main.cpp parser.tab.cpp  -c
lex.yy.cpp : scanner.l
	flex scanner.l
	ren lex.yy.c lex.yy.cpp
	del lex.yy.c

parser.tab.cpp : parser.ypp
	bison -d -v --debug -o parser.tab.cpp parser.ypp

clean :
	del *.o run.exe lex.yy.cpp parser.tab.cpp parser.tab.hpp parser.output