
target : run
	run.exe input.txt
run :  lex.yy.o main.o
	g++ main.o lex.yy.o -o run

lex.yy.o : lex.yy.cpp
	g++  lex.yy.cpp -c

main.o : main.cpp
	g++ main.cpp -c

lex.yy.cpp : scanner.l
	flex  scanner.l
	ren lex.yy.c lex.yy.cpp
	del lex.yy.c

clean :
	del *.o run.exe lex.yy.cpp