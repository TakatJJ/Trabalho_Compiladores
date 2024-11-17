#pragma once
#include <string>
using namespace std;

#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LIT_INTEGER 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4

#define SYMBOL_VAR 5
#define SYMBOL_FUNC 6
#define SYMBOL_VEC 7
#define SYMBOL_PARAM 8

#define DATA_TYPE_INT 9
#define DATA_TYPE_CHAR 10
#define DATA_TYPE_BOOL 11


class Symbol {


  

public:
  int type;
  int data_type;
  string text;
  Symbol() : type(0), text("") {}
  Symbol(int type, string text);

  int get_type();
  void set_type(int type);
  int get_data_type();
  void set_data_type(int data_type);
  string get_text();
};
