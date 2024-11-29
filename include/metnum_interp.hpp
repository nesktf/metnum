#pragma once
#include <metnum_common.hpp>

namespace metnum {
struct LagPolInput {
  std::vector<double> x_i;
  std::vector<double> y_i;
};

class LagrangePol {
private:
  std::vector<double> x_i;
  std::vector<double> y_i;
  double L_i(double x, int i);
public:
  LagrangePol(LagPolInput& in);
  double operator()(double x);
  int getGrade();
  void printExpr(void);
};
}
