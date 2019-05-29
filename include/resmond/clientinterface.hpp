#ifndef RESMOND_CLIENTINTERFACE_HPP
#define RESMOND_CLIENTINTERFACE_HPP


#include <string>
#include <server_http.hpp>

#include <resmond/processmanager.hpp>
#include <resmond/resourcemonitor.hpp>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

namespace resmond {

    class ClientInterface {
    public:
        ClientInterface(
            const std::string &address,
            unsigned short port,
            std::shared_ptr<ProcessManager> processManager,
            std::shared_ptr<ResourceMonitor> resourceMonitor
        );

        void start();

        void stop();

        void joinServerThread();

    private:
        typedef std::shared_ptr<HttpServer::Response> Response;
        typedef std::shared_ptr<HttpServer::Request> Request;

        void initServer(const std::string &address, unsigned short port);

        void initEndpoints();

        void respondWithError(const std::shared_ptr<HttpServer::Response> &response, const std::string &msg);

        void spawnHandler(const Response& response, const Request& request);

        void terminateHandler(const Response& response, const Request& request);

        void statusHandler(const Response& response, const Request& request);

        std::thread serverThread;
        HttpServer server;
        std::shared_ptr<ProcessManager> processManager;
        std::shared_ptr<ResourceMonitor> resourceMonitor;
    };

}


#endif //RESMOND_CLIENTINTERFACE_HPP
