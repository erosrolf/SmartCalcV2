#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_LEXEMS_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_LEXEMS_H_

#include <list>
#include <sstream>
#include <string>

#include "expression.h"

namespace s21 {

/**
 * @brief Lexem is single token of math expression
 */
class Lexem {
 public:
  enum class Type {
    kUnknown,
    kNumber,
    kOperator,
    kFunction,
    kOpenBracket,
    kCloseBracket,
  };

  size_t size() const { return str.size(); }
  char front() const { return str.front(); }
  bool empty() const { return str.empty(); }

  Lexem(Type type, const std::string& s, int priority = -1,
        bool right_associative = false, bool is_unary = false)
      : type(type),
        str(s),
        priority(priority),
        right_associative(right_associative),
        is_unary(is_unary) {}

  const Type type;
  const std::string str;  ///< token value
  const int priority;     ///< priority for shanting yand
  const bool right_associative;
  const bool is_unary;
};

/**
 * @brief Lexems expression divided on tokens
 */
class Lexems {
 public:
  using iterator = std::list<Lexem>::iterator;
  using const_iterator = std::list<Lexem>::const_iterator;

  Lexems(const char* input, const char* x_input = "0");
  Lexems(const std::string& input) : Lexems(input.c_str()){};
  Lexems(const std::string& input, const std::string& x_input)
      : Lexems(input.c_str(), x_input.c_str()){};
  ~Lexems() = default;

  static bool isNumeric(const char val) noexcept;
  static bool isOperator(const char val) noexcept;
  static bool isFunction(std::string::const_iterator it) noexcept;
  static int functionSize(std::string::const_iterator& val);

  size_t size() const { return lexems_.size(); }
  bool isValid() const { return is_valid_; }
  void printAllLexems() const;
  std::list<Lexem>::iterator begin() { return lexems_.begin(); }
  std::list<Lexem>::iterator end() { return lexems_.end(); }
  std::list<Lexem>::const_iterator cbegin() { return lexems_.cbegin(); }
  std::list<Lexem>::const_iterator cend() { return lexems_.cend(); }
  const std::list<Lexem>& data() { return lexems_; }

 private:
  int numericSize(std::string::const_iterator& val);
  void inputSeparateOnLexems(const std::string& input_copy);
  bool lexlemWithNumberIsValid(const std::string& number) const;
  bool lexlemWithFunctionIsValid(const std::string& number) const;
  bool lexlemsIsValid() const;
  void addMultiplication();
  Lexem operatorToLexem(const char ch);

  Expression input_;         /// <input expression
  bool is_valid_;            /// <expression is valid?
  std::list<Lexem> lexems_;  /// <expression divided on tokens
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_LEXEMS_H_
