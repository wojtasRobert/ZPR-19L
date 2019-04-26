#include <iostream>
#include <boost/program_options.hpp>
#include <server_http.hpp>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main(int argc, char *argv[]) {
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("name", po::value<std::string>(), "set name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("name")) {
        std::cout << "Hello, " << vm["name"].as<std::string>() << ".\n";
    } else {
        std::cout << "Hello, unknown.\n";
    }

    HttpServer server;
    server.config.address = "127.0.0.1";
    server.config.port = 8081;

    server.resource["^/$"]["POST"] = [](
        std::shared_ptr<HttpServer::Response> response,
        std::shared_ptr<HttpServer::Request> request
    ) {
        response->write("Hello.");
    };

    server.on_error = [](std::shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & ec) {
        std::cerr << ec.message() << std::endl;
    };

    std::thread server_thread([&server]() {
        server.start();
        std::cout << "The server is listening on " << server.config.address << ":" << server.config.port << std::endl;
    });

    server_thread.join();

    return 0;
}