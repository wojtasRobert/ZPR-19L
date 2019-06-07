#ifndef RESMOND_CLIENTINTERFACE_HPP
#define RESMOND_CLIENTINTERFACE_HPP


#include <string>
#include <server_http.hpp>

#include <resmond/processmanager.hpp>
#include <resmond/resourcemonitor.hpp>
#include <resmond/limitmanager.hpp>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

namespace resmond {

    /*!
     * Class of which object represents a server which conducts different operations after Client's requests. Created object starts and joins a new server thread.
     * Thanks to dependency injection it is possible for ClientInterface object to call methods from other modules. Given a request, object is able to handle different
     * situations depending on request's type.
     */
    class ClientInterface {
    public:
        ClientInterface(
            const std::string &address,
            unsigned short port,
            const std::shared_ptr<ProcessManager> &processManager,
            const std::shared_ptr<ResourceMonitor> &resourceMonitor,
            const std::shared_ptr<LimitManager> &limitManager
        );

        /*!
         * Starts ClientInterface thread.
         */
        void start();

        /*!
         * Stops ClientInterface thread.
         */
        void stop();

        /*!
         * Joins ClientInterface thread.
         */
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

        void limitsHandler(const Response& response, const Request& request);

        std::thread serverThread;
        HttpServer server;
        std::shared_ptr<ProcessManager> processManager;
        std::shared_ptr<ResourceMonitor> resourceMonitor;
        std::shared_ptr<LimitManager> limitManager;
    };

}


#endif //RESMOND_CLIENTINTERFACE_HPP
