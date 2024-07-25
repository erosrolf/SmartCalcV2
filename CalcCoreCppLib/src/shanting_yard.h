#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_SHANTING_YARD_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_SHANTING_YARD_H_

#include <stack>
#include <string>

#include "lexems.h"

namespace s21 {

/**
 * @brief ShantingYard parses an expression into tokens and sorts them into
 * reverse Polish notation
 */
class ShantingYard {
 public:
  ShantingYard(const char* input)
      : lexems_(input), expression_is_valid_(lexems_.isValid()) {
    lexlemsToPolish();
  };
  ShantingYard(const char* input, const char* x_input)
      : lexems_(input, x_input), expression_is_valid_(lexems_.isValid()) {
    lexlemsToPolish();
  };
  ~ShantingYard() = default;

  bool empty() { return reverse_polish_.empty(); }
  size_t size() { return reverse_polish_.size(); }
  void lexlemsToPolish();
  bool isValid() { return expression_is_valid_; }
  const std::list<Lexem> data() { return reverse_polish_; }
  std::string getExpressionString();
  std::string getReversePolishString();

 private:
  std::stack<Lexem> operatorsToStack();

  Lexems lexems_;
  bool expression_is_valid_;
  std::list<Lexem> reverse_polish_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_SHANTING_YARD_H_
