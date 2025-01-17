#pragma once
#include <string>
#include <map>
using namespace std;


#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LIT_INTEGER 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4

#define SYMBOL_VAR 5
#define SYMBOL_FUNC 6
#define SYMBOL_VEC 7
#define SYMBOL_PARAM 8
#define SYMBOL_LABEL 13

#define DATA_TYPE_INT 9
#define DATA_TYPE_CHAR 10
#define DATA_TYPE_STRING 11
#define DATA_TYPE_BOOL 12

class Symbol {

public:
  int type;
  int data_type;
  int param_count;
  int vector_size;

  string text;
  Symbol() : type(0), text("") {}
  Symbol(int type, string text);

  int get_type();
  void set_type(int type);
  int get_data_type();
  void set_data_type(int data_type);
  string get_text();
  static Symbol* makeTemp();
  static Symbol* makeTemp(int data_type);
  static Symbol* makeLabel();
};
extern map<string, Symbol> symbols_table;