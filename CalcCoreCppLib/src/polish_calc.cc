#include "polish_calc.h"

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

#include "expression.h"
#include "shanting_yard.h"

namespace s21 {

void PolishCalc::calculate(const char *expression, const char *x_value) {
  ShantingYard polish_expression(expression, x_value);
  if (polish_expression.isValid() == false) {
    status_ = Status::kInvalidExpression;
    return;
  }
  status_ = Status::kOk;
  std::list<Lexem> polish(polish_expression.data());
  std::stack<double> stack;

  while (!polish.empty() && status_ == Status::kOk) {
    const auto lexem = polish.front();
    polish.pop_front();

    switch (lexem.type) {
    case Lexem::Type::kNumber:
      if (lexem.str == "e") {
        stack.push(std::exp(1.0));
      } else {
        stack.push(std::stod(lexem.str));
      }
      break;
    case Lexem::Type::kOperator:
      if (lexem.is_unary) {
        unaryCalc(stack, lexem.str);
      } else {
        operatorCalc(stack, lexem.str[0]);
      }
      break;
    case Lexem::Type::kFunction:
      functionCalc(stack, lexem.str);
      break;
    default:
      status_ = Status::kInvalidExpression;
      break;
    }
  }
  if (status_ == Status::kOk) {
    expression_ = polish_expression.getExpressionString();
    reverse_polish_ = polish_expression.getReversePolishString();
  } else {
    expression_.clear();
    reverse_polish_.clear();
  }
  result_ = (status_ == Status::kOk) ? stack.top() : 0;
}

void PolishCalc::unaryCalc(std::stack<double> &stack,
                           const std::string &operation) {
  if (stack.empty()) {
    status_ = Status::kInvalidExpression;
    return;
  }
  if (operation == "-") {
    double num = stack.top() * -1;
    stack.pop();
    stack.push(num);
  } else if (operation != "+") {
    status_ = Status::kErrIntoUnaryCalc;
  }
}

void PolishCalc::operatorCalc(std::stack<double> &stack, char operand) {
  if (stack.size() < 2) {
    status_ = Status::kInvalidExpression;
    return;
  }
  const double r_num = stack.top();
  stack.pop();
  const double l_num = stack.top();
  stack.pop();

  switch (operand) {
  case '^':
    stack.push(pow(l_num, r_num));
    break;
  case '%':
    stack.push(fmod(l_num, r_num));
    break;
  case '*':
    stack.push(l_num * r_num);
    break;
  case '/':
    stack.push(l_num / r_num);
    break;
  case '+':
    stack.push(l_num + r_num);
    break;
  case '-':
    stack.push(l_num - r_num);
    break;
  default:
    status_ = Status::kErrIntoOperatorCalc;
    break;
  }
}

void PolishCalc::functionCalc(std::stack<double> &stack,
                              const std::string &func) {
  if (stack.empty()) {
    status_ = Status::kInvalidExpression;
    return;
  }
  const double num = stack.top();
  stack.pop();

  if (func == "sin") {
    stack.push(sin(num));
  } else if (func == "cos") {
    stack.push(cos(num));
  } else if (func == "tan") {
    stack.push(tan(num));
  } else if (func == "asin") {
    stack.push(asin(num));
  } else if (func == "acos") {
    stack.push(acos(num));
  } else if (func == "atan") {
    stack.push(atan(num));
  } else if (func == "sqrt") {
    stack.push(sqrt(num));
  } else if (func == "ln") {
    stack.push(log(num));
  } else if (func == "log") {
    stack.push(log10(num));
  } else {
    status_ = Status::kInvalidExpression;
  }
}

} // namespace s21
