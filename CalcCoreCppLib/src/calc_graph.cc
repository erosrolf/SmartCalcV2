#include "calc_graph.h"

#include <string>

namespace s21 {
void CalcGraph::calcVectorsWithPoints(const char *expression, double x_begin,
                                      double x_end) {
  x_.clear();
  y_.clear();
  double step = (x_end - x_begin) / 800;

  if (x_begin < x_end) {
    for (double i = x_begin; i <= x_end; i += step) {
      calculate(expression, std::to_string(i).c_str());
      if (status() == Status::kOk) {
        x_.push_back(i);
        y_.push_back(result());
      }
    }
  }
}
} // namespace s21
