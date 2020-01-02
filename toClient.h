//
// Created by inbar on 01/01/2020.
//

#ifndef EX3__TOCLIENT_H_
#define EX3__TOCLIENT_H_


#include <unordered_map>
#include <vector>
#include "Singleton.h"
#include "VarToSim.h"

using namespace std;
Singleton *Singleton::s;


class toClient {
 private:
  unordered_map<string, float> myMap;
  static toClient *s;

  toClient() {

  }

 public:
  unordered_map<string, float> getInstance() {
    vector<string> arr = Singleton::instance()->buildArray();
    unordered_map <string, float> newMap;
    for(int i = 0; i<arr.size(); i++) {
      if (VarToSim::instance()->getInstance().find(arr[i]) == VarToSim::instance()->getInstance().end()) {
        myMap[arr[i]] = Singleton::instance()->getInstance().at(arr[i]);
      } else {
        myMap[arr[i]] = VarToSim::instance()->getInstance().at(arr[i]).getValue();
      }
    }
    myMap = newMap;
  }
  static toClient *instance() {
    if(!s) {
      s = new toClient;
    }
    return s;
  }
};

#endif //EX3__TOCLIENT_H_
