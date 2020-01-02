
#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include "Expression.h"

class Variable: public Expression {
  std::string name;
  double value;
 public:
  Variable(std::string strName, double dblValue);
  virtual ~Variable();
  virtual double calculate();

  static bool ValidateVarName(std::string& strVarName);

  const std::string& getName() { return name;}
  double getValue() {return value;}

  Variable& operator ++();
  Variable& operator --();
  Variable& operator +=(double dblValue);
  Variable& operator -=(double dblValue);
  Variable& operator ++(int intValue);
  Variable& operator --(int intValue);
};

#endif /* VARIABLE_H_ */