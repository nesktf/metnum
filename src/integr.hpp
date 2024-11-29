#pragma once

#include "common.hpp"

namespace metnum {
struct IntegrInput {
  double a;
  double b;
  int n;
  Function f;
};

class IntegrBaseMult {
protected:
  double a;
  double b;
  double h;
  double size;
  int n;
  Function f;
public:
  IntegrBaseMult(IntegrInput& in);
  virtual double getVal(void) {return 0;};
};

class IntegrBase {
protected:
  double a;
  double b;
  double h;
  double size;
  Function f;
public:
  IntegrBase(IntegrInput& in);
  virtual double getVal(void) {return 0;};
};

class IntegrTrap : public IntegrBase {
public:
  IntegrTrap(IntegrInput& in) : IntegrBase(in) {};
  double getVal(void) override;
};

class IntegrSimp13 : public IntegrBase {
public:
  IntegrSimp13(IntegrInput& in) : IntegrBase(in) {};
  double getVal(void) override;
};

class IntegrSimp38 : public IntegrBase {
public:
  IntegrSimp38(IntegrInput& in) : IntegrBase(in) {};
  double getVal(void) override;
};

class IntegrTrapMult : public IntegrBaseMult {
public:
  IntegrTrapMult(IntegrInput& in) : IntegrBaseMult(in) {};
  double getVal(void) override;
};

class IntegrSimp13Mult : public IntegrBaseMult {
public:
  IntegrSimp13Mult(IntegrInput& in) : IntegrBaseMult(in) {};
  double getVal(void) override;
};
}
