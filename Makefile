CXX = g++
CXXFLAGS = -std=c++11 -Wall

target: etapa3

etapa2: symbols.o ast.o parser.tab.o lex.yy.o main.o
	$(CXX) $(CXXFLAGS) -o etapa3 symbols.o ast.o parser.tab.o lex.yy.o main.o

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -o parser.tab.cpp parser.ypp -d

lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f etapa2 lex.yy.cpp parser.tab.cpp parser.tab.hpp *.o
