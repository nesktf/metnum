#include "metnum.hpp"

static void ode_test() {
  auto p1 = [](metnum::ODESolverMethods method) -> void {
    metnum::ODESolverInput in;
    in.syst = {
      [](const metnum::MultiVarFuncArg& y) {return 3*y[0] - 2*y[1];},
      [](const metnum::MultiVarFuncArg& y) {return 5*y[0] - 4*y[1];}
    };
    in.init = {3, 6};
    in.h = 0.2;
    in.x_max = 2;

    std::cout << "Ejercicio 1): "; 

    if (method == metnum::EULER_SIMPLE) {
      std::cout << "Euler Simple" << std::endl;
      metnum::ODESolverEulerSimple out(in);
      out.calculate();
      out.print();
      out.plot();
    }
    else if (method == metnum::RUNGE_KUTTA_4) {
      std::cout << "Runge Kutta 4" << std::endl;
      metnum::ODESolverRungeKutta4 out(in);
      out.calculate();
      out.print();
      out.plot();
    }
  };

  auto p2 = [](metnum::ODESolverMethods method) -> void {
    metnum::ODESolverInput in;
    in.syst = {
      [](const metnum::MultiVarFuncArg& y) {return y[2];},
      [](const metnum::MultiVarFuncArg& y) {return 2*exp(y[0]) - 2*y[1] - y[2];}
    };
    in.h = 0.1;
    in.x_max = 2;
    in.init = {0, 1};

    std::cout << "Ejercicio 2): "; 

    if (method == metnum::EULER_SIMPLE) {
      std::cout << "Euler Simple" << std::endl;
      metnum::ODESolverEulerSimple out(in);
      out.calculate();
      out.print();
      out.plot();
    }
    else if (method == metnum::RUNGE_KUTTA_4) {
      std::cout << "Runge Kutta 4" << std::endl;
      metnum::ODESolverRungeKutta4 out(in);
      out.calculate();
      out.print();
      out.plot();
    }
  };
  
  p1(metnum::EULER_SIMPLE);
  p1(metnum::RUNGE_KUTTA_4);
  p2(metnum::EULER_SIMPLE);
  p2(metnum::RUNGE_KUTTA_4);
}

static void integral_test() {
  const double res = M_PI_2; // La integral vale pi/2

  auto p1 = []() -> double {
    metnum::IntegrInput in;
    in.a = -1;
    in.b = 1;
    in.n = 2;
    in.f = [](const double x){return 1/(1+(x*x));};

    metnum::IntegrSimp13Mult I(in);
    //std::cout << "1)" << std::endl;
    //std::cout << "I = " << I.getVal() << std::endl;
    return I.getVal();
  };

  auto p2 = []() -> double {
    metnum::IntegrInput in;
    in.a = -1;
    in.b = 1;
    in.n = 4;
    in.f = [](const double x){return 1/(1+(x*x));};

    metnum::IntegrSimp13Mult I(in);
    //std::cout << "2)" << std::endl;
    //std::cout << "I = " << I.getVal() << std::endl;
    return I.getVal();
  };

  std::cout << "3)" << std::endl;
  std::cout << "Valor verdadero de la integral: " << res << std::endl;
  std::cout << "Error relativo punto 1): " << metnum::err(p1(), res)*100 << "%" << std::endl;
  std::cout << "Error relativo punto 2): " << metnum::err(p2(), res)*100 << "%" << std::endl;
}


int main() {
  std::cout << "== ODE test ==\n";
  ode_test();
  std::cout << std::endl;

  std::cout << "== Integral test ==\n";
  integral_test();
  std::cout << std::endl;

  return 0;
}
