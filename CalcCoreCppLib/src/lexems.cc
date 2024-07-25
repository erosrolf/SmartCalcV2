#include "lexems.h"

#include <iostream>
#include <list>
#include <string>

#include "expression.h"

namespace s21 {

// CONSTUCTOR
Lexems::Lexems(const char *input, const char *x_input)
    : input_(input, x_input), is_valid_(input_.is_valid), lexems_() {
  std::string input_copy(input_.data);
  inputSeparateOnLexems(input_copy);
  addMultiplication();
  is_valid_ = lexlemsIsValid();
}

// STATIC METODS
bool Lexems::isNumeric(const char val) noexcept {
  return (val >= '0' && val <= '9') || val == '.' || val == 'e';
}

bool Lexems::isOperator(const char val) noexcept {
  return val == '-' || val == '+' || val == '/' || val == '*' || val == '(' ||
         val == ')' || val == '^' || val == '%';
}

bool Lexems::isFunction(std::string::const_iterator it) noexcept {
  return !isNumeric(*it) && (functionSize(it) > 1);
}

int Lexems::functionSize(std::string::const_iterator &val) {
  if (isNumeric(*val)) {
    return 0;
  }
  int word_size = isOperator(*val);
  while (*val != 0x00 && !isOperator(*val) && !isNumeric(*val)) {
    word_size++;
    ++val;
  }
  return word_size;
}

// METODS
Lexem Lexems::operatorToLexem(const char ch) {
  Lexem::Type type = Lexem::Type::kUnknown;
  int priority = -1;
  bool right_associative = false;
  bool unary = false;
  std::string str;
  if (ch == '(') {
    type = Lexem::Type::kOpenBracket;
    str = "(";
  } else if (ch == ')') {
    type = Lexem::Type::kCloseBracket;
    str = ")";
  } else if (ch == '^') {
    type = Lexem::Type::kOperator;
    right_associative = true;
    priority = 4;
    str = "^";
  } else if (ch == '%') {
    type = Lexem::Type::kOperator;
    right_associative = true;
    priority = 3;
    str = "%";
  } else if (ch == '/') {
    type = Lexem::Type::kOperator;
    priority = 3;
    str = "/";
  } else if (ch == '*') {
    type = Lexem::Type::kOperator;
    priority = 3;
    str = "*";
  } else if (ch == '+') {
    type = Lexem::Type::kOperator;
    if (lexems_.empty() || lexems_.back().type == Lexem::Type::kOpenBracket) {
      unary = true;
      str = "+";
      priority = 5;
    } else {
      priority = 2;
      str = "+";
    }
  } else if (ch == '-') {
    type = Lexem::Type::kOperator;
    if (lexems_.empty() || lexems_.back().type == Lexem::Type::kOpenBracket ||
        lexems_.back().type == Lexem::Type::kFunction ||
        lexems_.back().priority == 3) {
      unary = true;
      str = "-";
      priority = 5;
    } else {
      priority = 2;
      str = "-";
    }
  }
  return Lexem{type, str, priority, right_associative, unary};
}

void Lexems::inputSeparateOnLexems(const std::string &input_copy) {
  size_t begin_of_insert = 0;
  for (auto it = input_copy.cbegin(); it != input_copy.cend();) {
    if (*it == 0x00) {
      ++it;
    } else if (Lexems::isNumeric(*it)) {
      begin_of_insert = it - input_copy.cbegin();
      lexems_.push_back(
          Lexem{Lexem::Type::kNumber,
                input_copy.substr(begin_of_insert, numericSize(it))});
    } else if (Lexems::isFunction(it)) {
      begin_of_insert = it - input_copy.cbegin();
      lexems_.push_back(
          Lexem{Lexem::Type::kFunction,
                input_copy.substr(begin_of_insert, functionSize(it)), 4});
    } else if (Lexems::isOperator(*it)) {
      lexems_.push_back(operatorToLexem(*it));
      ++it;
    } else {
      is_valid_ = false;
      return;
    }
  }
}

int Lexems::numericSize(std::string::const_iterator &val) {
  int num_size = 0;
  while (*val != 0x00 && isNumeric(*val)) {
    if (*val == 'e' && isNumeric(*(val - 1)) &&
        (*(val + 1) == '-' || *(val + 1) == '+')) {
      num_size += 2;
      ++val;
      ++val;
    } else {
      ++val;
      ++num_size;
    }
  }
  return num_size;
}

void Lexems::printAllLexems() const {
  for (auto it = lexems_.cbegin(); it != lexems_.cend(); ++it) {
    std::cout << it->str << "\tpriority " << it->priority << "\ttype"
              << static_cast<int>(it->type) << std::endl;
  }
}

bool Lexems::lexlemWithFunctionIsValid(const std::string &func) const {
  if (func.size() > 4) {
    return false;
  }
  return (func == "sin" || func == "cos" || func == "tan" || func == "asin" ||
          func == "acos" || func == "atan" || func == "sqrt" || func == "ln" ||
          func == "log");
}

bool Lexems::lexlemWithNumberIsValid(const std::string &number) const {
  bool is_valid = true;
  int dot_count = 0;
  int e_count = 0;
  int sign_count = 0;

  for (auto it = number.cbegin(); it != number.cend() && is_valid; ++it) {
    if (*it == '.') {
      ++dot_count;
    } else if (*it == 'e') {
      ++e_count;
    } else if (*it == '-' || *it == '+') {
      ++sign_count;
    }
    is_valid = dot_count <= 1 && e_count <= 1 && sign_count <= 1 ? true : false;
  }
  return is_valid;
}

bool Lexems::lexlemsIsValid() const {
  bool is_valid = lexems_.size() ? true : false;
  if (lexems_.size() == 1 && lexems_.front().type != Lexem::Type::kNumber) {
    is_valid = false;
  }

  for (auto it = lexems_.cbegin(); it != lexems_.cend() && is_valid; ++it) {
    const std::string &tmp = it->str;
    if (isNumeric(tmp.front())) {
      is_valid = lexlemWithNumberIsValid(tmp);
    } else if (isOperator(tmp.front())) {
      is_valid = tmp.size() == 1 ? true : false;
    } else {
      is_valid = lexlemWithFunctionIsValid(tmp);
    }
  }
  return is_valid;
}

void Lexems::addMultiplication() {
  for (auto it = lexems_.begin(); it != lexems_.end();) {
    if (it->str == "e" || it->type == Lexem::Type::kCloseBracket) {
      ++it;
      if (it != lexems_.end() && (it->type == Lexem::Type::kOpenBracket ||
                                  it->type == Lexem::Type::kFunction ||
                                  it->type == Lexem::Type::kNumber)) {
        lexems_.insert(it, Lexem{Lexem::Type::kOperator, "*", 3});
        ++it;
      }
    } else if (it->type == Lexem::Type::kNumber) {
      ++it;
      if (it != lexems_.end() && (it->type == Lexem::Type::kFunction ||
                                  it->type == Lexem::Type::kOpenBracket)) {
        lexems_.insert(it, Lexem{Lexem::Type::kOperator, "*", 3});
        ++it;
      }
    } else {
      ++it;
    }
  }
}

}  // namespace s21
