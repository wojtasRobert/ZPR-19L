#include <resource_monitor/clientinterface.hpp>

ClientInterface::ClientInterface(const std::string &address, unsigned short port) {
    initServer(address, port);
    initEndpoints();
    start();
}

void ClientInterface::start() {
    serverThread = std::thread([this]() {
        server.start();
    });
}

void ClientInterface::stop() {
    server.stop();
}

void ClientInterface::joinServerThread() {
    serverThread.join();
}

void ClientInterface::initServer(const std::string &address, unsigned short port) {
    server.config.address = address;
    server.config.port = port;

    server.on_error = [](std::shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & ec) {
        std::cerr << ec.message() << std::endl;
    };
}

void ClientInterface::initEndpoints() {
    server.resource["^/$"]["POST"] = [](
        std::shared_ptr<HttpServer::Response> response,
        std::shared_ptr<HttpServer::Request> request
    ) {
        response->write("Hello.");
    };
}
