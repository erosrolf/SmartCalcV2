#include "expression.h"

#include <algorithm>
#include <string>

#include "lexems.h"

namespace s21 {

Expression::Expression(const char* expression)
    : data(ConcatinationExpression(expression)), is_valid(ExpressionIsValid()) {
  if (is_valid == false) {
    data.clear();
  } else {
    removeSpacesInPlace();
    toLowerCase();
    replaceCommasWithDots();
  }
}

Expression::Expression(const char* expression, const char* x_expression)
    : data(ConcatinationExpression(expression, x_expression)),
      is_valid(ExpressionIsValid()) {
  if (is_valid == false) {
    data.clear();
  } else {
    removeSpacesInPlace();
    toLowerCase();
    replaceCommasWithDots();
  }
}

void Expression::toLowerCase() {
  std::transform(data.begin(), data.end(), data.begin(), ::tolower);
}

void Expression::removeSpacesInPlace() {
  data.erase(std::remove_if(data.begin(), data.end(), ::isspace), data.end());
}

void Expression::replaceCommasWithDots() {
  std::replace(data.begin(), data.end(), ',', '.');
}

bool Expression::bracketsIsCorrect() {
  int open_br = 0;
  int close_br = 0;
  bool broken_br = false;
  for (char& c : data) {
    if (c == '(') {
      if (*(&c + 1) == ')') {
        broken_br = true;
      }
      ++open_br;
    } else if (c == ')') {
      ++close_br;
      if (close_br > open_br) {
        broken_br = true;
      }
    }
  }
  return open_br == close_br && !broken_br;
}

bool Expression::ExpressionIsValid() {
  if (data.size() < 1 || data.size() > 255) {
    return false;
  }
  return bracketsIsCorrect() && StringWithEIsValid(data);
}

bool Expression::StringWithEIsValid(const std::string& str) {
  for (std::size_t i = 0; i < str.length(); ++i) {
    if (str[i] == 'e' || str[i] == 'E') {
      if (i + 1 < str.length() && std::isdigit(str[i + 1])) {
        if (i == 0 || !std::isdigit(str[i - 1])) {
          return false;
        }
      }
    }
  }
  return true;
}

std::string Expression::ConcatinationExpression(const char* expression,
                                                const char* x_expression) {
  std::string result;
  while (*expression != 0x00) {
    if (*expression == 'x' || *expression == 'X') {
      if (Lexems::isNumeric(result.back())) {
        result += '*';
      }
      result += x_expression;
    } else {
      result.push_back(*expression);
    }
    ++expression;
  }
  return result;
}

}  // namespace s21
