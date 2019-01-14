#include <iostream>
#include <istream>
#include <ostream>


#ifndef PROJECTNUM2_CLIENHANDLER_H
#define PROJECTNUM2_CLIENHANDLER_H

using namespace std;

class ClientHandler {
public:

    /**
     * The function receive a socket id and communicate with a client.
     * @param socketFd
     */
    virtual void handleClient(int socketFd) = 0;

    virtual ~ClientHandler(){};

};


#endif //PROJECTNUM2_CLIENHANDLER_H