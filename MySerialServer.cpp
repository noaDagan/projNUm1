
#include "MySerialServer.h"

# define TIME_TO_WAIT 60


// struct save the parameter
struct params {
    int newSockFd;
    int sockFd;
    int client;
    struct sockaddr_in client_addr;
    ClientHandler *clientHandler;

};

//Constructor
MySerialServer::MySerialServer() {}


/**
 * The function open a socket
 * @param args a struct parameters.
 */
void *openSocketLoop(void *args) {
    struct params *openSocket = (struct params *) args;
    timeval timeVal;
    timeVal.tv_sec = TIME_TO_WAIT;
    timeVal.tv_usec = 0;

    /*Accept actual connection from the client */
    openSocket->newSockFd = accept(openSocket->sockFd,
                                   (struct sockaddr *) &openSocket->client_addr,
                                   (socklen_t *) &openSocket->client);
    if (openSocket->newSockFd < 0) {
        perror("connect error");
        exit(3);
    }
    openSocket->clientHandler->handleClient(openSocket->newSockFd);
    close(openSocket->newSockFd);
    while (true) {
        /*Accept actual connection from the client */
        setsockopt(openSocket->sockFd, SOL_SOCKET, SO_RCVTIMEO,
                   (char *) &timeVal, sizeof(timeVal));
        openSocket->newSockFd = accept(openSocket->sockFd,
                                       (struct sockaddr *) &openSocket->client_addr,
                                       (socklen_t *) &openSocket->client);
        if (openSocket->newSockFd < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "timeout!" << endl;
                return 0;
            } else {
                perror("connect error");
                exit(3);
            }
        }

        openSocket->clientHandler->handleClient(openSocket->newSockFd);
        close(openSocket->newSockFd);
    }
    return 0;
}

/**
 * The function open a socket
 * @param port the number of port
 * @param clientHandler a client
 */
void MySerialServer::open(int port, ClientHandler *clientHandler) {
    int sockfd, portno, clilen,newsockfd = 0;
    struct sockaddr_in serv_addr, cli_addr;
    struct params *openSocket = new params();

    // First call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    openSocket->clientHandler = clientHandler;
    openSocket->client = clilen;
    openSocket->client_addr = cli_addr;
    openSocket->newSockFd = newsockfd;
    openSocket->sockFd = sockfd;
    pthread_t pthread;
    pthread_create(&pthread, nullptr, openSocketLoop, openSocket);
    pthread_join(pthread, NULL);
    stop(openSocket->sockFd);
}

/**
 * The function stop the connection socket
 * @param socketFd a socket
 */
void MySerialServer::stop(int socketFd) {
    close(socketFd);
}
