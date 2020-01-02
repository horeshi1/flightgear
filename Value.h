
#ifndef VALUE_H_
#define VALUE_H_
#include <iostream>

#include "Expression.h"

class Value: public Expression {
 private:
  double* m_value;
 public:
  Value(double v);
  virtual ~Value();
  virtual double calculate();
  static bool ValidateValue(std::string& strValue);
};

#endif /* VALUE_H_ */