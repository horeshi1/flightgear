
#include <iostream>
#include "UPlus.h"

UPlus::UPlus(Expression* pEx) : UnariOperator(pEx)
{
}

UPlus::~UPlus()
{
}

double UPlus::calculate()
{
  return m_pEx->calculate();
}


