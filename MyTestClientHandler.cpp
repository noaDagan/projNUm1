
#include "MyTestClientHandler.h"
template<>

MyTestClientHandler<string, string>::MyTestClientHandler(Solver<string,string> *solver,CacheManager<string,string> *cacheManager) {
    this->solver=solver;
    this->cacheManager=cacheManager;
}

template<>
void MyTestClientHandler< string, string>::handleCLient(int socketFd) {
    char buffer[1025];
    int n;
    string result,problem;
    while (true) {
        bzero(buffer, 1025);
        n = read(socketFd, buffer, 1024);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        if (strcmp(buffer,"end") == 0) {
            return;
        }
        problem = string(buffer);
        if (this->cacheManager->haveSolution(problem)) {
            result=this->cacheManager->getSolution(problem);
        } else {
            result=this->solver->solve(problem);
            this->cacheManager->saveSolution(problem,result);
        }
        char* resultChar = const_cast<char*>(result.c_str());
        n = write(socketFd,resultChar, sizeof(resultChar));
    }

}