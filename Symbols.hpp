#pragma once
#include <string>
using namespace std;
class Symbol {

  private:
    int type;
    string text;

  public:
    Symbol() : type(0), text("") {}
    Symbol(int type, string text) {
      this->type = type;
      this->text = text;
    }

    int get_type() { return this->type; }
    string get_text() { return this->text; }
  };

  