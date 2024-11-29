#include "integr.hpp"

namespace metnum {
IntegrBaseMult::IntegrBaseMult(IntegrInput& in) {
  this->a = in.a;
  this->b = in.b;
  this->n = in.n;
  this->f = in.f;
  this->size = (b-a);
  this->h = size/n;
}

IntegrBase::IntegrBase(IntegrInput& in) {
  this->a = in.a;
  this->b = in.b;
  this->f = in.f;
  this->size = (b-a);
}

double IntegrTrap::getVal(void) {
  return (size/2)*(f(a)+f(b));
}

double IntegrSimp13::getVal(void) {
  double x_1 = a+((b-a)/3);
  return (size/6)*(f(a)+4*f(x_1)+f(b));
}

double IntegrSimp38::getVal(void) {
  double h = (b-a)/4;
  double x_1 = a+h;
  double x_2 = a+(h*2);
  return (size/8)*(f(a)+3*f(x_1)+3*f(x_2)+f(b));
}

double IntegrTrapMult::getVal(void) {
  double out = f(a);
  for (int i = 1; i < n; ++i)
    out += 2*f(a+(i*h));
  out += f(b);
  return (size*out)/(2*n);
}

double IntegrSimp13Mult::getVal(void) {
  double out = f(a);
  // Impares
  for (int i = 1; i < n; i+=2)
    out += 4*f(a+(i*h));
  // Pares
  for (int i = 2; i < n-1; i+=2)
    out += 2*f(a+(i*h));
  out += f(b);
  return (size*out)/(3*n);
}
}
