
#ifndef UPLUS_H_
#define UPLUS_H_

#include "UnariOperator.h"

class UPlus: public UnariOperator {
 public:
  UPlus(Expression* pEx);
  virtual ~UPlus();
  virtual double calculate();

};

#endif /* UPLUS_H_ */