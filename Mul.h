

#ifndef MUL_H_
#define MUL_H_
#include <iostream>

#include "Mul.h"
#include "BinaryOperator.h"

class Mul: public BinaryOperator {
 public:
  Mul(Expression* pExLeft = nullptr, Expression* pExRight = nullptr);
  virtual ~Mul();
  virtual double calculate();
};

#endif /* MUL_H_ */