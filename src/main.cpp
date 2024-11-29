#include "metnum.hpp"

// #define PLOT_THINGS

static void rootfinder_test() {
  /* Metodos cerrados */
  double root_b, root_r;
  metnum::ClosedRootInput in;
  in.a = 0.8;
  in.b = 1.2;
  in.err = 0.0001;
  in.iter = 12;

  auto f = [](double x) -> double { return (std::cos(4*x - 2) + std::exp(1-x)); };
  auto g = [](double x) -> double { return (x*x + 10*std::cos(x)); };
  auto h = [](double x) -> double { return std::acos(-x*x/10.); };


  if (metnum::rootBisecc(f, in, root_b) == 0) {
    // Raíz de f(x)
    std::cout << "Bisección" << std::endl;
    std::cout << root_b << std::endl;
  }
  std::cout << std::endl;

  if (metnum::rootRegFal(f, in, root_r) == 0) {
    // Raíz de f(x)
    std::cout << "Regula falsi" << std::endl;
    std::cout << root_r << std::endl;
  }
  std::cout << std::endl;
  

  /* Metodos abiertos */
  double root_pf, root_n, root_s;
  metnum::OpenRootInput in2;
  in2.x0 = 1.5;
  in2.iter = 10;
  in2.err = 0.0000007;

  if (metnum::rootPtFijo(h, in2, root_pf) == 0) {
    // Raíz de h(x)
    std::cout << "Punto fijo" << std::endl;
    std::cout << root_pf << std::endl;
  }
  else {
    std::cout << "Metodo diverge" << std::endl;
  }
  std::cout << std::endl;

  if (metnum::rootNewton(g, in2, root_n) == 0) {
    // Raíz de g(x)
    std::cout << "Newton" << std::endl;
    std::cout << root_n << std::endl;
  }
  std::cout << std::endl;

  if (metnum::rootSecant(g, in2, root_s) == 0) {
    // Raíz de g(x)
    std::cout << "Secante" << std::endl;
    std::cout << root_s << std::endl;
  }

}

static void eqsolver_test() {
  auto p1 = []() -> void {
    std::cout << "a)" << std::endl;
    metnum::VecDouble outS, outJ;
    metnum::EquationMat a_in;
    a_in.coef = {
      {8, 8, 1},
      {2, 1, 4},
      {2, 4, 1}
    };
    a_in.res = {2, 1, 4};

    std::cout << "Gauss simple:" << std::endl;
    metnum::systGaussSim(a_in, outS);
    matrixutil::printVec(outS);

    std::cout << "Gauss-Jordan:" << std::endl;
    metnum::systGaussJor(a_in, outJ);
    matrixutil::printVec(outJ);

    std::cout << std::endl;

    std::cout << "b)" << std::endl;
    metnum::VecDouble outJa, outSe;

    metnum::IterMetInput b_in;
    b_in.iter = 20;
    b_in.err = 10e-5;
    b_in.x_0 = {0, 0, 0};
    b_in.mat = {
      .coef = {
        {10, 3, 1},
        {2, -10, 3},
        {1, 3, 10}
      },
      .res = {14, -5, 14},
    };

    std::cout << "Jacobi:" << std::endl;
    metnum::systJacobi(b_in, outJa);
    matrixutil::printVec(outJa);

    std::cout << "Gauss-Seidel:" << std::endl;
    metnum::systGaussSei(b_in, outSe);
    matrixutil::printVec(outSe);
  };

  auto p2 = []() -> void {
    metnum::VecDouble out_og, out_red, out_trunc;
    metnum::EquationMat in_og, in_red, in_trunc;

    // Datos originales
    in_og.coef = {
      {1, 1/2.0, 1/3.0, 1/4.0},
      {1/2.0, 1/3.0, 1/4.0, 1/5.0},
      {1/3.0, 1/4.0, 1/5.0, 1/6.0},
      {1/4.0, 1/5.0, 1/6.0, 1/7.0}
    };
    in_og.res = {25/12.0, 77/60.0, 57/60.0, 319/420.0};

    // Datos con redondeo a 3 cifras significativas
    in_red.coef = {
      {1, 0.5, 0.334, 0.25},
      {0.5, 0.334, 0.25, 0.2},
      {0.334, 0.25, 0.2, 0.167},
      {0.25, 0.2, 0.167, 0.143} 
    };
    in_red.res = {2.083, 1.283, 0.95, 0.760};

    // Datos con truncamiento en la 3er cifra decimal
    in_trunc.coef = {
      {1, 0.5, 0.333, 0.25},
      {0.5, 0.333, 0.25, 0.2},
      {0.333, 0.25, 0.2, 0.166},
      {0.25, 0.2, 0.166, 0.142}
    };
    in_trunc.res = {2.083, 1.283, 0.95, 0.759};

    std::cout << "Datos originales" << std::endl;
    metnum::systGaussSim(in_og, out_red);
    matrixutil::printVec(out_red);

    std::cout << "Redondeado a 3 cifras decimales:" << std::endl;
    metnum::systGaussSim(in_red, out_red);
    matrixutil::printVec(out_red);

    std::cout << "Truncado en 3 cifras decimales:" << std::endl;
    metnum::systGaussSim(in_trunc, out_trunc);
    matrixutil::printVec(out_trunc);
  };

  auto p3 = []() -> void {
    metnum::VecDouble out;
    metnum::EquationMat in;
    in.coef = {
      {5, 2, 4},
      {3, 5, 3},
      {4, 5, 6}
    };
    in.res = {45, 44, 58};
    metnum::systGaussSim(in, out);
    std::cout << "Viajes barcaza Angeka: " << out[0] << std::endl;
    std::cout << "Viajes barcaza María: " << out[1] << std::endl;
    std::cout << "Viajes barcaza Hanahui: " << out[2] << std::endl;
  };

  auto p4 = []() -> void {
    double err = 10e-5;
    int maxiter = 20;

    metnum::IterMetInput a;
    a.err = err;
    a.iter = maxiter;
    a.mat = {
      .coef = {
        {1, 2, 3, 4},
        {1, 4, 9, 16},
        {1, 8, 27, 64},
        {1, 16, 81, 256}
      },
      .res = { 2, 10, 44, 190 },
    };
    a.x_0 = { 0, 0, 0, 0};
    if (matrixutil::willConverge(a.mat)) {
      metnum::VecDouble out;
      metnum::systGaussSei(a, out);
      std::cout << "a)" << std::endl;
      matrixutil::printVec(out);
    }
    else
      std::cout << "a) No cumple condición de convergencia" << std::endl;

    metnum::IterMetInput b;
    b.err = err;
    b.iter = maxiter;
    b.mat = {
      .coef = {
        {3, 1, -1},
        {1, 2, 1},
        {-2, 0, 1}
      },
      .res = { 0, 1, 3 },
    };
    b.x_0 = { 0, 0, 0 };
    if (matrixutil::willConverge(b.mat)) {
      metnum::VecDouble out;
      metnum::systGaussSei(b, out);
      std::cout << "b)" << std::endl;
      matrixutil::printVec(out);
    }
    else
      std::cout << "b) No cumple condición de convergencia" << std::endl;
    
    metnum::IterMetInput c;
    c.err = err;
    c.iter = maxiter;
    c.mat = {
      .coef = {
        {22.2, 0.5, -1.5, 2.3},
        {0.5, 23.5, 1.0, 5.9},
        {6.0, 3.0, 27.0, 0},
        {0, 0, -17.5, 20.9}
      },
      .res = {-1.0, 2.0, 6.0, -5.0},
    };
    c.x_0 = { 0, 0, 0, 0 };
    if (matrixutil::willConverge(c.mat)) {
      metnum::VecDouble out;
      metnum::VecDouble x_0 = {0, 0, 0, 0};
      metnum::systGaussSei(c, out);
      std::cout << "c)" << std::endl;
      matrixutil::printVec(out);
    }
    else
      std::cout << "c) No cumple condición de convergencia" << std::endl;

    metnum::IterMetInput d;
    d.err = err;
    d.iter = maxiter;
    d.mat = {
      .coef = {
        {2.5, 0.14, 0, 0},
        {-0.25, 1.4, 0.72, 0},
        {0, 0.44, 3.2, -0.21},
        {0.85, 0, 0.11, 1.8}
      },
      .res = {3.4, -1.1, 1.6, -2.2},
    };
    d.x_0 = { 0, 0, 0, 0 };
    if (matrixutil::willConverge(d.mat)) {
      metnum::VecDouble out;
      metnum::VecDouble x_0 = {0, 0, 0, 0};
      metnum::systGaussSei(d, out);
      std::cout << "d)" << std::endl;
      matrixutil::printVec(out);
    }
    else
      std::cout << "d) No cumple condición de convergencia" << std::endl;
  };

  auto p5 = []() -> void {
    metnum::VecDouble outJa, outSe;
    metnum::IterMetInput in;
    in.err = 10e-7;
    in.iter = 22;
    in.mat = {
      .coef = {
        {22.2, 0.5, 1.3, 2.3},
        {0.5, 23.5, 1.0, 5.9},
        {6.0, 3.0, 27.0, 0},
        {0, 0, 17.5, 20.9}
      },
      .res = { -1., 2., 6., -5. },
    };
    in.x_0 = { .1, -.1, .1, -.1 };

    std::cout << "Jacobi:" << std::endl;
    int jacobiIter = metnum::systJacobi(in, outJa);
    matrixutil::printVec(outJa);
    std::cout << "iter: " << jacobiIter << std::endl;

    std::cout << "Gauss-Seidel:" << std::endl;
    int seidelIter = metnum::systGaussSei(in, outSe);
    matrixutil::printVec(outSe);
    std::cout << "iter: " << seidelIter << std::endl;
  };

  p1();
  p2();
  p3();
  p4();
  p5();
}

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

    std::cout << "1): "; 

    if (method == metnum::EULER_SIMPLE) {
      std::cout << "Euler Simple" << std::endl;
      metnum::ODESolverEulerSimple out(in);
      out.calculate();
      out.print();
#ifdef PLOT_THINGS
      out.plot();
#endif
    }
    else if (method == metnum::RUNGE_KUTTA_4) {
      std::cout << "Runge Kutta 4" << std::endl;
      metnum::ODESolverRungeKutta4 out(in);
      out.calculate();
      out.print();
#ifdef PLOT_THINGS
      out.plot();
#endif
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

    std::cout << "2): "; 

    if (method == metnum::EULER_SIMPLE) {
      std::cout << "Euler Simple" << std::endl;
      metnum::ODESolverEulerSimple out(in);
      out.calculate();
      out.print();
#ifdef PLOT_THINGS
      out.plot();
#endif
    }
    else if (method == metnum::RUNGE_KUTTA_4) {
      std::cout << "Runge Kutta 4" << std::endl;
      metnum::ODESolverRungeKutta4 out(in);
      out.calculate();
      out.print();
#ifdef PLOT_THINGS
      out.plot();
#endif
    }
  };
  
  p1(metnum::EULER_SIMPLE);
  p1(metnum::RUNGE_KUTTA_4);
  p2(metnum::EULER_SIMPLE);
  p2(metnum::RUNGE_KUTTA_4);
}

static void interp_test() {
  auto p1 = []() -> void {
    metnum::LagPolInput in;
    in.x_i = {-1, 0, 2, 3};
    in.y_i = {1, -1, 2, 2};

    metnum::LagrangePol f(in);
    std::cout << "1)" << std::endl;
    std::cout << "Polinomio:" << std::endl;
    f.printExpr();
    std::cout << "f(1) = " << f(1) << std::endl; 
  };

  auto p2 = []() -> void {
    metnum::LagPolInput in;
    in.x_i = {1, 5, 20, 40};
    in.y_i = {56.5, 113.0, 181.0, 214.5};

    metnum::LagrangePol f(in);
    std::cout << "2)" << std::endl;
    std::cout << "Temp ebullición de la acetona a 2 atm: f(2) = " << f(2) << std::endl;
    f.printExpr();
  };

  auto p3 = []() -> void {
    metnum::LagPolInput in;
    in.x_i = {0, 5, 10, 20, 30, 40};
    in.y_i = {1.787, 1.519, 1.307, 1.002, 0.796, 0.653};

    metnum::LagrangePol f(in);
    std::cout << "3)" << std::endl;
    std::cout << "Viscosidad a 7.5 grados: f(7.5) = " << f(7.5) << std::endl;
    f.printExpr();
  };

  p1();
  p2();
  p3();
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
  std::cout << "== Root Finder test ==\n";
  rootfinder_test();
  std::cout << std::endl;

  std::cout << "== Equation system solver test==\n";
  eqsolver_test();
  std::cout << std::endl;

  std::cout << "== ODE test ==\n";
  ode_test();
  std::cout << std::endl;

  std::cout << "== Interpolator test==\n";
  interp_test();
  std::cout << std::endl;

  std::cout << "== Integral test ==\n";
  integral_test();
  std::cout << std::endl;

  return 0;
}
