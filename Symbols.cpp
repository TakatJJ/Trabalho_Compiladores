#include "Symbols.hpp"

Symbol::Symbol(int type, string text) {
  this->type = type;
  this->text = text;
  this->param_count = -1;
  this->vector_size = -1;

  if (type == SYMBOL_LIT_INTEGER)
    this->data_type = DATA_TYPE_INT;
  else if (type == SYMBOL_LIT_CHAR)
    this->data_type = DATA_TYPE_CHAR;
  else if (type == SYMBOL_LIT_STRING)
    this->data_type = DATA_TYPE_STRING;
  else
    this->data_type = 0;
}

int Symbol::get_type() { return this->type; }
int Symbol::get_data_type() { return this->data_type; }
string Symbol::get_text() { return this->text; }

void Symbol::set_type(int type) { this->type = type; }
void Symbol::set_data_type(int data_type) { this->data_type = data_type; }