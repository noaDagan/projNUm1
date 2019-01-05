#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "StringReverse.h"
#include "Server.h"
#include "Solver.h"
#include "CacheManager.h"
#include "FileCacheManager.h"

using namespace server_side;
int main() {
    Server* mySerialServer = new MySerialServer();
    Solver<string,string> *stringReverse = new StringReverse();
    CacheManager<string,string> *fileCacheManager = new FileCacheManager<string,string>();
    ClientHandler* clientHandler = new MyTestClientHandler <string, string> (stringReverse, fileCacheManager);
    cout<< "start mySerialServer" << endl;
    mySerialServer->open(5400, clientHandler);
    cout<< "end mySerialServer" <<endl;

    return 0;
}