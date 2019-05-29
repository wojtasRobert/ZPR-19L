#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <resmond/clientinterface.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    ClientInterface::ClientInterface(
        const std::string &address,
        unsigned short port,
        std::shared_ptr<ProcessManager> processManager,
        std::shared_ptr<ResourceMonitor> resourceMonitor
    ) : processManager(processManager), resourceMonitor(resourceMonitor) {
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
            if (ec.value() == 2) {
                return;
            }

            std::cerr << ec.message() << std::endl;
        };
    }

    void ClientInterface::initEndpoints() {
        server.resource["^/spawn$"]["POST"] = [this](Response res, Request req) { spawnHandler(res, req); };
        server.resource["^/terminate$"]["POST"] = [this](Response res, Request req) { terminateHandler(res, req); };
        server.resource["^/status$"]["POST"] = [this](Response res, Request req) { statusHandler(res, req); };
    }

    void ClientInterface::respondWithError(
        const std::shared_ptr<HttpServer::Response> &response,
        const std::string &msg
    ) {
        boost::property_tree::ptree pt;
        pt.put("msg", msg);

        std::stringstream ss;
        boost::property_tree::write_json(ss, pt);
        response->write(SimpleWeb::StatusCode::client_error_bad_request, ss.str());
    }

    void ClientInterface::spawnHandler(const Response& response, const Request& request) {
        boost::property_tree::ptree pt, response_pt;
        boost::property_tree::read_json(request->content, pt);

        try {
            int childId = processManager->spawn(pt.get<std::string>("command"));
            response_pt.put("id", childId);
        } catch (boost::process::process_error &e) {
            respondWithError(response, e.what());
        }

        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, response_pt);
        response->write(ss.str());
    }

    void ClientInterface::terminateHandler(const Response& response, const Request& request) {
        boost::property_tree::ptree pt, response_pt;
        boost::property_tree::read_json(request->content, pt);

        try {
            int id = pt.get<int>("id");
            processManager->terminate(id);
            response_pt.put("id", id);
        } catch (resmond::NoSuchChildError &) {
            respondWithError(response, "There is no child the with given id");
        }

        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, response_pt);
        response->write(ss.str());
    }

    void ClientInterface::statusHandler(const Response& response, const Request& request) {
        boost::property_tree::ptree response_pt, children;

        const auto &resourceUsage = resourceMonitor->getResourceUsage();
        for (const auto &child : processManager->getChildren()) {
            if (!std::get<0>(child.second)->running()) {
                continue;
            }
            boost::property_tree::ptree cpt, usage;
            cpt.put("id", child.first);
            cpt.put("command", std::get<1>(child.second));
            usage.put("cpu", std::get<0>(resourceUsage.at(child.first)));
            usage.put("memory", std::get<1>(resourceUsage.at(child.first)));
            cpt.add_child("resources", usage);

            children.push_back(std::make_pair("", cpt));
        }

        response_pt.add_child("children", children);

        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, response_pt);
        response->write(ss.str());
    }

}