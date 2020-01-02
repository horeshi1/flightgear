//
// Created by ofir on 24/12/2019.
//

#include <sys/socket.h>
#include <iostream>
#include <rpc/types.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <pthread.h>
#include <unordered_map>
#include "Singleton.h"
#include <vector>


using namespace std;

Singleton *Singleton::s;

struct  Server {
  int port;

  Server(int p) {
    this -> port = p;
  }

  static void buffToMap(char buffer[]) {
    unordered_map<string, float> ret;
    vector<string> names = Singleton::instance()->buildArray();

    int i = 0;
    int place = 0;
    string word = "";
    while ((place < 1024) && (((buffer[place] >= '0') && (buffer[place] <= '9')) || (buffer[place] == ',') ||
        (buffer[place] == '.') || (buffer[place] == '-'))) { //while place < buffer.length
      if (buffer[place] == ',') {
        ret[names[i]] = stof(word);
        i++;
        word = "";
      } else {
        word += buffer[place];
      }
      place++;
    }
    ret[names[i]] = stof(word);
    Singleton::instance()->setInstance(ret);
    cout<< "answer: "<<Singleton::instance()->getInstance().at("/instrumentation/altimeter/pressure-alt-ft")<<"\n"<<endl;
  }

  void openServer() {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
      cerr << "Could not create a socket" << endl;
      //return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port);

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
      cerr << "Could not bind the socket to an IP" << endl;
      //return -2;
    }


    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //was 1024
      cerr << "Error during listening command" << endl;
      //return -3;
    }

    //Here we need to create a thread
    thread thread_obj(readFromClient, socketfd, address);
    thread_obj.join();

//        //accepting a client
//        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
//        if (client_socket == -1) {
//            cerr << "Error accepting client" << endl;
//            //return -4;
//        }
//
//        //reading from client
//        while (true) {
//            char buffer[1024] = {0};
//            int valread = read(client_socket, buffer, 1024);
//            buffToMap(buffer);
//        }
//
//        //writing back to client
//        const char *hello = "hello, I can hear you! \n";
//        send(client_socket, hello, strlen(hello), 0);
//        cout << "Hello message sent" << endl;
//        //return 0;
  }

  static void readFromClient(int socketfd, sockaddr_in address) {
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    if (client_socket == -1) {
      cerr << "Error accepting client" << endl;
      //return -4;
    }
    while (true) {
      char buffer[1024] = {0};
      int valread = read(client_socket, buffer, 1024);
      buffToMap(buffer);
    }
  }
};