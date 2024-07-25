#include "shanting_yard.h"

#include <iostream>
#include <stack>

#include "lexems.h"

namespace s21 {

void ShantingYard::lexlemsToPolish() {
  if (expression_is_valid_ == false) {
    return;
  }
  std::stack<Lexem> operator_stack = operatorsToStack();
  while (operator_stack.empty() == false) {
    if (operator_stack.top().type == Lexem::Type::kOpenBracket) {
      std::cerr << "In ShantingYard brackets error";
      break;
    }
    reverse_polish_.push_back(operator_stack.top());
    operator_stack.pop();
  }
}

std::stack<Lexem> ShantingYard::operatorsToStack() {
  std::stack<Lexem> operator_stack;
  for (auto lexem : lexems_) {
    switch (lexem.type) {
    case Lexem::Type::kNumber: {
      reverse_polish_.push_back(lexem);
      break;
    }
    case Lexem::Type::kFunction:
    case Lexem::Type::kOperator: {
      const auto current_oper = lexem;
      while (!operator_stack.empty()) {
        const auto top_oper = operator_stack.top();
        if ((!current_oper.right_associative &&
             current_oper.priority <= top_oper.priority) ||
            (current_oper.right_associative &&
             current_oper.priority < top_oper.priority)) {
          reverse_polish_.push_back(top_oper);
          operator_stack.pop();
          continue;
        }
        break;
      }
      operator_stack.push(current_oper);
      break;
    }
    case Lexem::Type::kOpenBracket: {
      operator_stack.push(lexem);
      break;
    }
    case Lexem::Type::kCloseBracket: {
      while (!operator_stack.empty() &&
             operator_stack.top().type != Lexem::Type::kOpenBracket) {
        reverse_polish_.push_back(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.pop();
      break;
    }
    case Lexem::Type::kUnknown:
      std::cerr << "In ShantingYard unvalid lexem";
      expression_is_valid_ = false;
    }
  }
  return operator_stack;
}

std::string ShantingYard::getExpressionString() {
  std::string result;
  for (auto it : lexems_.data()) {
    result += it.str;
  }
  return result;
}

std::string ShantingYard::getReversePolishString() {
  std::string result;
  for (auto it = reverse_polish_.crbegin(); it != reverse_polish_.crend();
       ++it) {
    if (!result.empty()) {
      result += " ";
    }
    result += it->str;
  }

  return result;
}

} // namespace s21
