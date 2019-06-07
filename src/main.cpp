#include <iostream>
#include <boost/program_options.hpp>
#include <server_http.hpp>

#include <resmond/clientinterface.hpp>
#include <resmond/processmanager.hpp>
#include <resmond/resourcemonitor.hpp>
#include <resmond/limitmanager.hpp>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {

    using namespace std::chrono_literals;

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

    auto limitManager = std::make_shared<resmond::LimitManager>();
    auto emailSender = std::make_shared<resmond::EmailSender>("../script/mailer", 5min);
    auto processManager = std::make_shared<resmond::ProcessManager>(limitManager);
    auto resourceMonitor = std::make_shared<resmond::ResourceMonitor>(emailSender, processManager, limitManager);

    std::thread resourceMonitorThread([&resourceMonitor]() {
        while (true) {
            resourceMonitor->update();
            std::this_thread::sleep_for(1s);
        }
    });

    resmond::ClientInterface clientInterface("127.0.0.1", 8081, processManager, resourceMonitor, limitManager);

    std::cout << "Daemon started." << std::endl;

    clientInterface.joinServerThread();

    return 0;
}