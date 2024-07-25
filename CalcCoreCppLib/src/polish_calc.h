#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_POLISH_CALC_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_POLISH_CALC_H_

#include <stack>
#include <string>

namespace s21 {

/**
 * @brief status of calculation
 */
enum class Status {
  kOk = 0,
  kInvalidExpression,
  kDivByZero,
  kErrIntoUnaryCalc,
  kErrIntoOperatorCalc,
  kErrIntoFunctionCalc,
};

/**
 * @brief performs calculations of mathematical expressions. contains
 * information about the last calculation
 */
class PolishCalc {
 public:
  PolishCalc()
      : result_(0), status_(Status::kOk), expression_(), reverse_polish_() {}

  void calculate(const char* expression, const char* x_value = "0");
  double result() { return result_; }
  Status status() { return status_; }
  std::string getExpression() { return expression_; }
  std::string getReversePolish() { return reverse_polish_; }
  void reset() { result_ = 0, status_ = Status::kOk; }

 private:
  void unaryCalc(std::stack<double>& stack, const std::string& operation);
  void operatorCalc(std::stack<double>& stack, char operand);
  void functionCalc(std::stack<double>& stack, const std::string& func);

  double result_;
  Status status_;
  std::string expression_;
  std::string reverse_polish_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_POLISH_CALC_H_
