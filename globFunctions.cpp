//
// Created by inbar on 03/01/2020.
//

#include <sstream>
#include "globFunctions.h"

string isVar(string var) {
  if (VarToSim::instance()->getInstance().find(var) != VarToSim::instance()->getInstance().end()) {
    return "VarToSim";
  } else if (ConstVars::instance()->getInstance().find(var) != ConstVars::instance()->getInstance().end()) {
    return "ConstVars";
  } else if (Vars::instance()->getInstance().find(var) != Vars::instance()->getInstance().end()) {
    return "Vars";
  } else {
    return "no";
  }
}

void updateVar(string varType, string var, float value) {
  if (varType == "VarToSim") {               //////////////// replace
    VarToSim::instance()->updateVar(var, value);
  } else if (varType == "ConstVars") {       //////////////// if exists replace, otherwise make new
    ConstVars::instance()->updateVar(var, value);
  }
}


bool is_number( string myString ) {
  std::istringstream iss(myString);
  float f;
  iss >> noskipws >> f; // noskipws considers leading whitespace invalid
  // Check the entire string was consumed and if either failbit or badbit is set
  return iss.eof() && !iss.fail();
}

float solveExpression(string expression) {
//  if(is_number(expression)) {
//    return stof(expression);
//  }
  Interpreter* it = new Interpreter();
  ////////////////////////////////////////////////// search for variables
  int i;
  string command;
  for (i = 0; i < expression.length(); i++) {
    command = "";
    while ((expression[i] != ',') && (expression[i] != '(') && (expression[i] != ' ') && (expression[i] != ')')  &&
    (expression[i]!='\t') && (expression[i]!='+') && (expression[i]!='-') && (expression[i]!='*') && (expression[i]!='/') && (i<expression.length())) {
      command += expression[i];
      i++;
    }
    if (command != "") {
      if (!is_number(command)) {                  /////////////// if not a number, operator etc. check for variables
        string vType = isVar(command);
        if (vType == "no") {
          cout << "error: what is " << command << endl;
        } else {
          std::ostringstream oss;
          if (vType == "Vars") {
            oss << command << "=" << *Vars::instance()->getInstance().at(command);
          } else if (vType == "VarToSim") {
          oss << command << "=" << VarToSim::instance()->getInstance().at(command)->getValue();
        } else if (vType == "ConstVars") {
          oss << command << "=" << ConstVars::instance()->getInstance().at(command);
          }
          string val = oss.str();
          it->setVariables(val);
        }
      }
    }
  }
  expression += "+0";
  ////////////////////////////////////////////// solve and return answer
  Expression* ans = it->interpret(expression);
  return ans->calculate();
}