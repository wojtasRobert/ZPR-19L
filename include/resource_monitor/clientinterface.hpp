#ifndef RESOURCE_MONITOR_CLIENTINTERFACE_HPP
#define RESOURCE_MONITOR_CLIENTINTERFACE_HPP


#include <string>
#include <server_http.hpp>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

class ClientInterface {
public:
    ClientInterface(const std::string &address, unsigned short port);
    void start();
    void stop();
    void joinServerThread();

private:
    void initServer(const std::string &address, unsigned short port);
    void initEndpoints();

    std::thread serverThread;
    HttpServer server;
};


#endif //RESOURCE_MONITOR_CLIENTINTERFACE_HPP
