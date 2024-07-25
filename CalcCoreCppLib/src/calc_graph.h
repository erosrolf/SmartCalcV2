#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_CALC_GRAPH_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_CALC_GRAPH_H_

#include <vector>

#include "polish_calc.h"

/**
 * @brief The task of the PolishCalc class is to calculate the coordinates of
 * the points on the function graph.
 */
namespace s21 {
class CalcGraph : PolishCalc {
 public:
  /**
   * @brief main class method
   *
   * @param expression is a math function
   * @param x_begin is beginning of the function graph
   * @param x_end is end of the function ghaph
   */
  void calcVectorsWithPoints(const char* expression, double x_begin,
                             double x_end);

  /**
   * @return vector of coordinates along the X axis after calculating the main
   * class function
   */
  std::vector<double>& getVectorX() { return x_; }
  /**
   * @return vector of coordinates along the Y axis after calculating the main
   * class function
   */
  std::vector<double>& getVectorY() { return y_; }

 private:
  std::vector<double> x_;
  std::vector<double> y_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_CALC_GRAPH_H_
