#ifndef RESMOND_CLIENTINTERFACE_HPP
#define RESMOND_CLIENTINTERFACE_HPP


#include <string>
#include <server_http.hpp>

#include <resmond/processmanager.hpp>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

namespace resmond {

    class ClientInterface {
    public:
        ClientInterface(
            const std::string &address,
            unsigned short port,
            std::shared_ptr<ProcessManager> processManager
        );

        void start();

        void stop();

        void joinServerThread();

    private:
        void initServer(const std::string &address, unsigned short port);

        void initEndpoints();

        void respondWithError(const std::shared_ptr<HttpServer::Response>& response, const std::string& msg);

        std::thread serverThread;
        HttpServer server;
        std::shared_ptr<ProcessManager> processManager;
    };

}


#endif //RESMOND_CLIENTINTERFACE_HPP
