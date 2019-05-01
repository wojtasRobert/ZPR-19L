#include <resmond/clientinterface.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    ClientInterface::ClientInterface(
        const std::string &address, unsigned short port,
        std::shared_ptr<ProcessManager> processManager
    ) : processManager(processManager) {
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

        server.on_error = [](std::shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code &ec) {
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

        server.resource["^/spawn$"]["POST"] = [this](
            std::shared_ptr<HttpServer::Response> response,
            std::shared_ptr<HttpServer::Request> request
        ) {
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(request->content, pt);

            try {
                int childId = processManager->spawn(pt.get<std::string>("executable"));
                response->write(std::to_string(childId));
            } catch (boost::process::process_error &e) {
                respondWithError(response, e.what());
            }
        };

        server.resource["^/terminate$"]["POST"] = [this](
            std::shared_ptr<HttpServer::Response> response,
            std::shared_ptr<HttpServer::Request> request
        ) {
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(request->content, pt);

            try {
                processManager->terminate(pt.get<int>("id"));
                response->write(SimpleWeb::StatusCode::success_ok);
            } catch (resmond::NoSuchChildError &) {
                respondWithError(response, "There is no child the with given id");
            }
        };

    }

    void ClientInterface::respondWithError(
        const std::shared_ptr<HttpServer::Response>& response,
        const std::string& msg
    ) {
        boost::property_tree::ptree pt;
        pt.put("msg", msg);

        std::stringstream ss;
        boost::property_tree::write_json(ss, pt);
        response->write(SimpleWeb::StatusCode::client_error_bad_request, ss.str());
    }

}