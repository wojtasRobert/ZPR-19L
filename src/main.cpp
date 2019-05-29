#include <iostream>
#include <boost/program_options.hpp>
#include <server_http.hpp>
#include <resmond/clientinterface.hpp>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <resmond/resourcemonitor.hpp>
#include <resmond/resourcemonitor.hpp>

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

    auto processManager = std::make_shared<resmond::ProcessManager>();
    auto resourceMonitor = std::make_shared<resmond::ResourceMonitor>(processManager);

    // FOR DEBUGGING PURPOSES
    processManager->spawn("sleep 1000");
    std::cout << std::endl << "PID\tCPU%\tMEM%\tCOMMAND" << std::endl << std::endl;
    std::thread resourceMonitorThread([&resourceMonitor]() {
        while (true) {
            resourceMonitor->update();
            for (const auto &process : resourceMonitor->getResourceUsage()) {
                std::cout
                << process.first << "\t"
                << std::get<0>(process.second) << "\t"
                << std::get<1>(process.second) << "\t"
                << std::endl;
            }
            std::cout << std::endl;
            std::this_thread::sleep_for(1s);
        }
    }); // <-- FOR DEBUGGING PURPOSES

    resmond::ClientInterface clientInterface("127.0.0.1", 8081, processManager, resourceMonitor);
    clientInterface.joinServerThread();

    return 0;
}