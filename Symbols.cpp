#include "Symbols.hpp"

Symbol::Symbol(int type, string text) {
  this->type = type;
  this->text = text;
  this->data_type = this->type == SYMBOL_LIT_INTEGER ? DATA_TYPE_INT : this->type == SYMBOL_LIT_CHAR ? DATA_TYPE_CHAR : 0;
}

int Symbol::get_type() { return this->type; }
int Symbol::get_data_type() { return this->data_type; }
string Symbol::get_text() { return this->text; }

void Symbol::set_type(int type) { this->type = type; }
void Symbol::set_data_type(int data_type) { this->data_type = data_type; }