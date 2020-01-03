//
// Created by ofir on 23/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>
#include <vector>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include "Vars.h"
#include "ConstVars.h"
#include "VarToSim.h"
#include "Variable.h"
#include "globFunctions.h"

using namespace std;
Vars *Vars::s;
ConstVars *ConstVars::s;
VarToSim *VarToSim::s;


class Command {
 public:
  virtual int execute(vector<string> commands, int index) = 0;
};


class OpenServerCommand : public Command {

 public:
  int execute(vector<string> commands, int index) {

    Server *s = new Server(stoi(commands[index + 1]));
    s->openServer();
    return 2;
  }
};


class ConnectCommand : public Command {

 public:
  int execute(vector<string> commands, int index) {
    string IP = commands[index + 1];
    int port = stoi(commands[index + 2]);
    Client *c = new Client(IP, port);
    c->openClient();
    return 3;
  }
};


class DefineVarCommand : public Command {

 public:
  int execute(vector<string> commands, int index) {
    if (commands[index+2] == "->") {
      // real value : float value = Singleton::instance()->getInstance().at(commands[index+3]);
      VarToSim::instance()->add(commands[index+1], commands[index+4], 0);
    } else if (commands[index+2] == "=") {
      updateVar("ConstVars", commands[index + 1], solveExpression(commands[index+3]));
      return 4;
    } else if (commands[index+2] == "<-") {
      Vars::instance()->add(commands[index+1],&Singleton::instance()->getInstance().at(commands[index+4]));
    }
    return 5;
  }
};


class PrintCommand : public Command {
 public:
  int execute(vector<string> strings, int index) {
    cout << strings[index + 1] << endl;
    return 2;
  }
};


#endif //EX3_COMMAND_H