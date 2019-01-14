#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include <string.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>


#ifndef PROJECTNUM2_MYCLIENTHANDLER_H
#define PROJECTNUM2_MYCLIENTHANDLER_H

using namespace std;

class MyClientHandler : public ClientHandler {
    //members
    Solver<string, string> *solver;
    CacheManager<string, string> *cacheManager;
public:
    // Constructor
    MyClientHandler(Solver<string, string> *solve,
                    CacheManager<string, string> *cacheManager);

/**
*  The function open a socket and read the problem and result from the client by socketFd
*/
    virtual void handleClient(int socketFd);

    // Distructor
    virtual ~MyClientHandler() {};
};


#endif //PROJECTNUM2_MYCLIENTHANDLER_H