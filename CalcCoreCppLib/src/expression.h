#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_EXPRESSION_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_EXPRESSION_H_

#include <string>

namespace s21 {

/**
 * @brief performs initial validation and inserts x_value in place of 'x' in
 * math expression.
 */
struct Expression {
  /**
   * @brief
   * Performs initial validation and inserts "0" in place of 'x' in math
   * expression
   *
   * @param expression
   */
  Expression(const char* expression);

  /**
   * @brief
   * Performs initial validation and inserts x_value in place of 'x' in math
   * expression
   *
   * @param expression
   * @param x_expression
   */
  Expression(const char* expression, const char* x_expression);

  void toLowerCase();
  void removeSpacesInPlace();
  void replaceCommasWithDots();

  bool bracketsIsCorrect();

  bool StringWithEIsValid(const std::string& str);
  bool ExpressionIsValid();
  std::string ConcatinationExpression(const char* expression,
                                      const char* x_expression = "0");

  std::string data;  ///< Resulting math expression. Empty if is_valid == false.
  bool is_valid;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_EXPRESSION_H_
