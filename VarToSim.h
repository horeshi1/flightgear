//
// Created by inbar on 01/01/2020.
//

#ifndef EX3__VARTOSIM_H_
#define EX3__VARTOSIM_H_

#include <unordered_map>
#include "Variable.h"

using namespace std;

class VarToSim {
 private:
  unordered_map<string, Variable> myMap;
  static VarToSim *s;

  VarToSim() {

  }

 public:
  unordered_map<string, Variable> getInstance() {
    return myMap;
  }
  void add(string name, Variable v) {
    this->myMap[name] = v;
  }
  static VarToSim *instance() {
    if(!s) {
      s = new VarToSim();
    }
    return s;
  }
};


#endif //EX3__VARTOSIM_H_
