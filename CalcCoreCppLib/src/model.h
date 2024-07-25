#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_MODEL_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_MODEL_H_

#include "calc_graph.h"
#include "polish_calc.h"

namespace s21 {
class Model {
 public:
  void calculate(const char* expression, const char* x_value = "0") {
    calc_.calculate(expression, x_value);
  }

  double result() { return calc_.result(); }

  Status status() { return calc_.status(); }

  std::string getExpression() { return calc_.getExpression(); }

  std::string getReversePolish() { return calc_.getReversePolish(); }

  void calcVectorsWithPoints(const char* expression, double x_begin,
                             double x_end) {
    graph_.calcVectorsWithPoints(expression, x_begin, x_end);
  }

  std::vector<double>& getVectorX() { return graph_.getVectorX(); }

  std::vector<double>& getVectorY() { return graph_.getVectorY(); }

  void calcReset() { calc_.reset(); }

 private:
  PolishCalc calc_;
  CalcGraph graph_;
};
};  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_MODEL_H_
