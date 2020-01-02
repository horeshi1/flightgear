
#include <iostream>

#include "Minus.h"


Minus::Minus(Expression* pExLeft, Expression* pExRight)
    : BinaryOperator(pExLeft, pExRight)
{

}

Minus::~Minus()
{
}
double Minus::calculate()
{
  return left->calculate() - right->calculate();
}


