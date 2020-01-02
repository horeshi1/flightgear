//
// Created by inbar on 31/12/2019.
//

#ifndef EX3__CONSTVARS_H_
#define EX3__CONSTVARS_H_

#include <unordered_map>

using namespace std;

class ConstVars {
 private:
  unordered_map<string, float> myMap;
  static ConstVars *s;

  ConstVars() {

  }

 public:
  unordered_map<string, float> getInstance() {
    return myMap;
  }
  void add(string name, float num) {
    this->myMap[name] = num;
  }
  void setVar(string name, float num) {
    this->myMap[name] = num;
  }
  static ConstVars *instance() {
    if(!s) {
      s = new ConstVars;
    }
    return s;
  }
};


#endif //EX3_SINGLETON_H
