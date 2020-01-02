#ifndef EX3_VARS_H
#define EX3_VARS_H

#include <unordered_map>

using namespace std;

class Vars {
 private:
  unordered_map<string, float *> myMap;
  static Vars *s;

  Vars() {

  }

 public:
  unordered_map<string, float*> getInstance() {
    return myMap;
  }
  void add(string name, float *ptr) {
    this->myMap[name] = ptr;
  }
  void setVar(string name, float *ptr) {
    this->myMap.erase(name);
    this->myMap[name] = ptr;
  }
  static Vars *instance() {
    if(!s) {
      s = new Vars;
    }
    return s;
  }
};


#endif //EX3_SINGLETON_H