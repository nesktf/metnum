#include <metnum.hpp>
#include <cmath>

double p1(void) {
  metnum::IntegrInput in;
  in.a = -1;
  in.b = 1;
  in.n = 2;
  in.f = [](const double x){return 1/(1+(x*x));};

  metnum::IntegrSimp13Mult I(in);
  //std::cout << "1)" << std::endl;
  //std::cout << "I = " << I.getVal() << std::endl;
  return I.getVal();
}

double p2(void) {
  metnum::IntegrInput in;
  in.a = -1;
  in.b = 1;
  in.n = 4;
  in.f = [](const double x){return 1/(1+(x*x));};

  metnum::IntegrSimp13Mult I(in);
  //std::cout << "2)" << std::endl;
  //std::cout << "I = " << I.getVal() << std::endl;
  return I.getVal();
}

void p3(void) {
  const double res = M_PI_2; // La integral vale pi/2
  std::cout << "3)" << std::endl;
  std::cout << "Valor verdadero de la integral: " << res << std::endl;
  std::cout << "Error relativo punto 1): " << metnum::err(p1(), res)*100 << "%" << std::endl;
  std::cout << "Error relativo punto 2): " << metnum::err(p2(), res)*100 << "%" << std::endl;
}

int main() {
  //p1();
  //p2();
  p3();
}
