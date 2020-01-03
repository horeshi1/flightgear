#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "Command.h"
#include "Vars.h"
#include "globFunctions.h"

using namespace std;

vector<string> lexer(string fname) {
  fstream f;
  f.open(fname, ios:: in | ios:: out);
  vector<string> strings(0);

  if (f){
    string line;

    while (getline(f, line)) {
      int i;
      string command;
      for (i = 0; i < line.length(); i++) {
        command = "";
        while ((line[i] != ',') && (line[i] != '(') && (line[i] != ' ') && (line[i] != ')')  && (line[i]!='\t') && (i<line.length())) {
          command += line[i];
          i++;
        }
        if (command != "") {
          strings.resize(strings.size() + 1);
          strings[strings.size() - 1] = command;
          if (command == "=") {
            strings.resize(strings.size() + 1);
            command = line.substr(line.find("=") + 2);
            strings[strings.size() - 1] = command;
            i = line.length();
          }
        }
      }
    }
    f.close();
  }
  return strings;
}

void parser(vector<string> strings, unordered_map<string, Command*> commands) {
  int index = 0;
  while (index < strings.size()) {
    if (commands.find(strings[index]) == commands.end()) {                                //if not a command
      string vType = isVar(strings[index]);
      if (vType == "no") {  //not var
        cout << "Command named : '" << strings[index] << "' was not defined" << endl;
        index++;
      } else {                                                                              //is a varuable
        updateVar(vType, strings[index], solveExpression(strings[index+2]));
        index+=3;
      }
    } else {                                                                              //is a command
      Command *c = commands.at(strings[index]);
      index += c->execute(strings, index);
    }
  }
}
unordered_map<string, Command*> createMap() {
  unordered_map<string, Command*> commands;

  commands.insert(pair<string, Command*>("openDataServer", new OpenServerCommand()));
  commands.insert(pair<string, Command*>("connectControlClient", new ConnectCommand()));
  commands.insert(pair<string, Command*>("var", new DefineVarCommand()));
  commands.insert(pair<string, Command*>("print", new PrintCommand()));

  return commands;
}



int main(int argc, char * argv[]) {
  unordered_map<string, Command *> commands = createMap();
  vector<string> strings = lexer(argv[1]);
//  for (int i = 0; i < strings.size(); i++) {
//      cout << strings[i] << endl;
//    }
  parser(strings, commands);
}