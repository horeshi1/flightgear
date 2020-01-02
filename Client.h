//
// Created by ofir on 25/12/2019.
//

#include <sys/socket.h>
#include <iostream>
#include <rpc/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

using namespace std;

struct Client {
  string IP;
  int port;

  Client(string str, int p) {
    this->IP = str;
    this->port = p;
  }


  int openClient() {

    //test
    cout << "I'm in ClientCommand execute! yay!" << endl;
    cout << "IP: " << this->IP.c_str() << endl;
    cout << "port: " << this->port << endl;


    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
      cerr << "Could not create a socket" << endl;
      return -1;
    }

    //socket address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(this->IP.c_str()); //TODO: make sure we get the right IP("127.0.0.1")
    address.sin_port = htons(this->port); //TODO: make sure we get the right port

    //request a connection with the server
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
      cerr << "Could not connect to server" << endl;
      return -2;
    } else {
      cout << "Client is now connected to server" << endl;
    }

    char hello[] = "Hi from client";
    int is_sent = send(client_socket, hello, strlen(hello), 0);
    if (is_sent == -1) {
      cout << "Error sending message" << endl;
    } else {
      cout << "Hello message sent to server" << endl;
    }

    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    cout << buffer << endl;

    close(client_socket);

    return 0;
  }
};