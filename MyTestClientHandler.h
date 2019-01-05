#include "CacheManager.h"
#include "ClientHandler.h"
#include "Solver.h"
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#ifndef PROJECTNUM2_MYTESTCLIENTHANDLER_H
#define PROJECTNUM2_MYTESTCLIENTHANDLER_H
using namespace std;

template<class T1, class T2>
class MyTestClientHandler : public ClientHandler {
    Solver<string,string> *solver;
    CacheManager <string,string> *cacheManager;
public:
    MyTestClientHandler( Solver<string,string> *solver,CacheManager <string,string> *cacheManager);
    virtual void handleCLient(int socketFd);

};


#endif //PROJECTNUM2_MYTESTCLIENTHANDLER_H
