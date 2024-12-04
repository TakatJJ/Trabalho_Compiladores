CXX = g++
CXXFLAGS = -std=c++11 -Wall

target: etapa5

etapa5: tacs.o SemanticAnalyzer.o Symbols.o AST.o parser.tab.o lex.yy.o main.o
	$(CXX) $(CXXFLAGS) -o etapa5 tacs.o SemanticAnalyzer.o Symbols.o AST.o parser.tab.o lex.yy.o main.o -g

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -o parser.tab.cpp parser.ypp -d

lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -g $<

clean:
	rm -f etapa5 lex.yy.cpp parser.tab.cpp parser.tab.hpp *.o
