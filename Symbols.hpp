#pragma once
#include <string>
using namespace std;
class Symbol {

private:
  int type;
  string text;

public:
  Symbol() : type(0), text("") {}
  Symbol(int type, string text);

  int get_type();
  string get_text();
};
