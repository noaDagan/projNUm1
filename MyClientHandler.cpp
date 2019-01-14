#include "MyClientHandler.h"

// Constructor
MyClientHandler::MyClientHandler(Solver<string, string> *solve,
                                 CacheManager<string, string> *cacheManager) {
    this->solver = solve;
    this->cacheManager = cacheManager;
}

/**
 *  The function open a socket and read the problem and result from the client by socketFd
 */
void MyClientHandler::handleClient(int socketFd) {
    char buffer[1025];
    char bufferWrite[1024];
    int n;
    string result = "";
    string problem = "";
    bzero(buffer, 1025);
    n = read(socketFd, buffer, 1024);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    // read from client until "end" and copy to problem string
    while (strcmp(buffer, "end") != 0) {
        string temp = string(buffer);
        problem += temp + ";";
        bzero(buffer, 1025);
        n = read(socketFd, buffer, 1024);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
    }
    // add to problem string "end" , start and goal point
    problem += "end;";
    // check if the file have the solution and get
    if (this->cacheManager->haveSolution(problem)) {
        result = this->cacheManager->getSolution(problem);
    } else { // solver the problem and save
        result = this->solver->solve(problem);
        this->cacheManager->saveSolution(problem, result);
    }
    bzero(bufferWrite,1025);
    strcpy(bufferWrite,result.c_str());
    size_t n2 = write(socketFd, bufferWrite, strlen(bufferWrite));
    if (n2 < 0) {
        perror("ERROR writing from socket");
        exit(1);
    }
    // close socketFd
    close(socketFd);
}