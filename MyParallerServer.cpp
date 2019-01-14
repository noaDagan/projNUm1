#include "MyParallerServer.h"

# define TIME_TO_WAIT 1
# define TIME_TO_WAIT2 0

//Client struct
struct client {
    ClientHandler *clientHandler;
    int newSockFd;

};

//Server struct
struct params {
    int newSockFd;
    int sockFd;
    int client;
    struct sockaddr_in client_addr;
    ClientHandler *clientHandler;

};

//Constructor
MyParallerServer::MyParallerServer() {

}

/**
 * The function open a thread to communuczte to a client
 */
void *clientThread(void *arg) {
    struct client *clientStruct = (struct client *) arg;
    //Handle client
    clientStruct->clientHandler->handleClient(clientStruct->newSockFd);
    return 0;
}

/**
 * The function open a socket server and listen to multiple clients simultaneously
 */
void *openMultiple(void *args) {
    vector< pthread_t> clientFd;
    struct params *openSocket = (struct params *) args;
    timeval timeVal;
    timeVal.tv_sec = TIME_TO_WAIT;
    timeVal.tv_usec = 0;
    timeval timeVal2;
    timeVal2.tv_sec = TIME_TO_WAIT2;
    timeVal2.tv_usec = 0;
    //Wait for connection from the first client
    struct client *clientStruct = new client();
    clientStruct->clientHandler = openSocket->clientHandler;
    openSocket->newSockFd = accept(openSocket->sockFd,
                                   (struct sockaddr *) &openSocket->client_addr,
                                   (socklen_t *) &openSocket->client);
    if (openSocket->newSockFd < 0) {
        perror("connect error");
        return 0;
    }

    //Open a thread to talk to the client
    clientStruct->newSockFd = openSocket->newSockFd;
    pthread_t pthread;
    pthread_create(&pthread, nullptr, clientThread, clientStruct);
    clientFd.push_back(pthread);
    //While there are more clients
    while (true) {
        /*Accept actual connection from the client */
        //Wait for connection from the next client
        setsockopt(openSocket->sockFd, SOL_SOCKET, SO_RCVTIMEO,
                   (char *) &timeVal, sizeof(timeVal));
        openSocket->newSockFd = accept(openSocket->sockFd,
                                       (struct sockaddr *) &openSocket->client_addr,
                                       (socklen_t *) &openSocket->client);
        //If the client failed to connect or the time ended clise the sever
        if (openSocket->newSockFd < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "timeout!" << endl;
                // close( clientStruct->newSockFd);
                break;
            } else {
                perror("connect error");
                break;
            }
        }
        setsockopt(openSocket->newSockFd ,SOL_SOCKET, SO_RCVTIMEO,
                   (char *) &timeVal2, sizeof(timeVal2));
        //Open a thread to talk to the client
        clientStruct->newSockFd = openSocket->newSockFd;
        pthread_t pthread;
        pthread_create(&pthread, nullptr, clientThread, clientStruct);
        clientFd.push_back(pthread);

    }
    int vectorSize = clientFd.size();
    for (int i = 0; i < vectorSize; ++i) {
        pthread_join(clientFd[i],NULL);
    }
    delete(clientStruct);
    return 0;
}

/**
 * The function open thread to open a server and listen to multiple clients simultaneously
 */
void MyParallerServer::open(int port, ClientHandler *clientHandler) {
    int sockfd, portno, clilen, newsockfd = 0;
    struct sockaddr_in serv_addr, cli_addr;
    struct params *openSocket = new params();
    // open a socket
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
    //Listen to the socket
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    // Initialize server structure
    openSocket->clientHandler = clientHandler;
    openSocket->client = clilen;
    openSocket->client_addr = cli_addr;
    openSocket->newSockFd = newsockfd;
    openSocket->sockFd = sockfd;
    //Open a thread to the server
    pthread_t pthread;
    pthread_create(&pthread, nullptr, openMultiple, openSocket);
    pthread_join(pthread, NULL);
    delete openSocket;
    stop(sockfd);
}

void MyParallerServer::stop(int socketFd) {
    close(socketFd);
}