#include "Symbols.hpp"

Symbol::Symbol(int type, string text) {
  this->type = type;
  this->text = text;
}

int Symbol::get_type() { return this->type; }
string Symbol::get_text() { return this->text; }
