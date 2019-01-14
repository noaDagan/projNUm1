#include "ClientHandler.h"

#ifndef PROJECTNUM2_SERVER_H
#define PROJECTNUM2_SERVER_H

namespace server_side {

    class Server {
    public:

        /**
        * The function open a socket
        * @param port the number of port
        * @param clientHandler a client
        */
        virtual void open(int port, ClientHandler *clientHandler) = 0;

        /**
         * The function stop the connection socket
         * @param socketFd a socket
         */
        virtual void stop(int socketFd) = 0;

        virtual ~Server(){};

    };
}

#endif //PROJECTNUM2_SERVER_H