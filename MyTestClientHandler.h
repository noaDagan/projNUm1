#include "CacheManager.h"
#include "ClientHandler.h"
#include "Solver.h"
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#ifndef PROJECTNUM2_MYTESTCLIENTHANDLER_H
#define PROJECTNUM2_MYTESTCLIENTHANDLER_H


class MyTestClientHandler : public ClientHandler {
    // Members
    Solver<string, string> *solver;
    CacheManager<string, string> *cacheManager;
public:

    //Constructor
    MyTestClientHandler(Solver<string, string> *solver,
                        CacheManager<string, string> *cacheManager) {
        this->solver = solver;
        this->cacheManager = cacheManager;
    }

/**
*  The function open a socket and read the problem and result from the client by socketFd
*/
    virtual void handleClient(int socketFd) {
        char buffer[1025];
        char resultChar[1025];
        int n;
        string result, problem;
        while (true) {
            bzero(buffer, 1025);
            n = read(socketFd, buffer, 1024);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            if (strcmp(buffer, "end") == 0) {
                return;
            }
            problem = string(buffer);
            if (this->cacheManager->haveSolution(problem)) {
                result = this->cacheManager->getSolution(problem);
            } else {
                result = this->solver->solve(problem);
                this->cacheManager->saveSolution(problem, result);
            }
            bzero(resultChar,1024);
            strcpy(resultChar,result.c_str());
            size_t n2 = write(socketFd, resultChar, strlen(resultChar));
            if (n2 < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
        }

    }

};


#endif //PROJECTNUM2_MYTESTCLIENTHANDLER_H