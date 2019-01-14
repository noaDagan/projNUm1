#include <iostream>
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "Server.h"
#include "Solver.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MatrixSolver.h"
#include "AStar.h"
#include "MyParallerServer.h"

#include <string>
#include <string.h>

#ifndef PROJECTNUM2_MYMAIN_H
#define PROJECTNUM2_MYMAIN_H

using namespace server_side;
namespace boot {
    /**
     * The main function create serial server to solver matrix by aStar algoritim
     * The main handle client in Paraller server
     */
    class MyMain {
    public:
        int main(int argc, char *argv[]) {
            if (argc != 2) {
                throw "ERROR - invalid input";
            } else {
                CacheManager<string,string> *cacheManager = new FileCacheManager<std::string,std::string>();
                Searcher<std::string> *aStar = new ASTar<std::string>();
                Solver<std::string,std::string> *solver = new MatrixSolver<std::string,std::string>(aStar);
                ClientHandler *clientHandler = new MyClientHandler(solver,
                                                                   cacheManager);
                Server *server = new MyParallerServer();
                int port = atoi(argv[1]);
                server->open(port, clientHandler);
                delete aStar;
                delete cacheManager;
                delete solver;
                delete server;
                delete clientHandler;
                return 0;
            }
        }
        ~MyMain(){};
    };

}

#endif //PROJECTNUM2_MYMAIN_H
