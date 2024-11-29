#include "interp.hpp"

namespace metnum {
LagrangePol::LagrangePol(LagPolInput& in) {
  this->x_i = in.x_i;
  this->y_i = in.y_i;
} 

int LagrangePol::getGrade() {
  return this->y_i.size() - 1;
}

double LagrangePol::L_i(double x, int i) {
  double out = 1;
  for (int j = 0; j <= getGrade(); ++j) {
    if (i == j)
      continue;
    out *= (x - x_i[j])/(x_i[i]-x_i[j]);
  }
  return out;
}

double LagrangePol::operator()(double x) {
  double out = 0;
  for (int i = 0; i <= getGrade(); ++i)
    out += L_i(x, i)*y_i[i];
  return out;
}

void LagrangePol::printExpr(void) {
  std::vector<double> coefs(getGrade()+1);
  std::vector<std::vector<double>> displ(getGrade()+1);

  for (int i = 0; i <= getGrade(); ++i) {
    double l_i = 1;
    for (int j = 0; j <= getGrade(); ++j) {
      if (i == j)
        continue;
      l_i /= (x_i[i]-x_i[j]);
    }
    coefs[i] = l_i*y_i[i];
  }

  for (int i = 0; i <= getGrade(); ++i)
    for (int j = 0; j <= getGrade(); ++j)
      if (&x_i[i] != &x_i[j])
        displ[i].push_back(x_i[j]);

  std::cout << "f(x) = ";
  for (int i = 0; i <= getGrade(); ++i) {
    if (coefs[i] == 0)
      continue;
    for (auto& val : displ[i]) {
      if (val == 0)
        std::cout << "(x)";
      else {
        std::cout << "(x ";
        if (val < 0)
          std::cout << "+ " << val*-1;
        else
          std::cout << "- " << val;
        std::cout << ")";
      }
    }
    std::cout << "(" << coefs[i] << ")";
    if (i != getGrade())
      std::cout << " + ";
    else 
      std::cout << std::endl;
  }
}
}
