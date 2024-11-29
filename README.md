# metnum
A bunch of numerical methods that I implemented in C++17 for some college assignments

All methods were taken from the book "Métodos numéricos para ingenieros - Quinta Edición" by
Steven C. Chapra & Raymond P. Canale

The excercises where probably taken from there too, i didn't check lmao

## Method list
Root finding
- [Bisection method](https://en.wikipedia.org/wiki/Bisection_method)
- [Regula Falsi](https://en.wikipedia.org/wiki/Regula_falsi)
- [Fixed point iteration](https://en.wikipedia.org/wiki/Fixed-point_iteration)
- [Newton's method](https://en.wikipedia.org/wiki/Newton's_method)
- [Secant method](https://en.wikipedia.org/wiki/Secant_method)

Systems of linear equations solving
- [Gaussian and Gauss-Jordan elimination](https://en.wikipedia.org/wiki/Gaussian_elimination)
- [Jacobi method](https://en.wikipedia.org/wiki/Jacobi_method)
- [Gauss-Seidel method](https://en.wikipedia.org/wiki/Gauss%E2%80%93Seidel_method)

Ordinary Differential Equation solving
- [Euler method](https://en.wikipedia.org/wiki/Euler_method)
- [4th order Runge-Kutta method](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods)

Polynomial interpolation
- [Lagrange polynomial](https://en.wikipedia.org/wiki/Lagrange_polynomial)

Integration
- [Trapezoidal rule](https://en.wikipedia.org/wiki/Trapezoidal_rule)
- [Simpson's 1/3 and 3/8 rules](https://en.wikipedia.org/wiki/Simpson%27s_rule)

## Building
Tested on Debian 12 Bookworm and Arch Linux. You will need the following dependencies:

```sh
$ sudo apt install libarmadillo-dev liblaplack-dev libopenblas-dev
```
You will also need gnuplot if you want to plot the ODEs (uncomment the PLOT_THINGS define)

Then build and execute the project by doing the following:

```sh
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ make -C build -j4
$ ./build/metnum
```

## Libraries
- [armadillo](https://arma.sourceforge.net/) 
- [gnuplot-cpp](https://github.com/martinruenz/gnuplot-cpp) 
