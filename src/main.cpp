#include <iostream>
#include <boost/program_options.hpp>
#include <server_http.hpp>
#include <resmond/clientinterface.hpp>

#ifndef _WIN32

#include <sys/types.h>
#include <sys/sysinfo.h>
#include <resmond/resourcemonitor.hpp>
#include <resmond/linuxresourcemonitor.hpp>

#endif

int main(int argc, char *argv[]) {
    namespace po = boost::program_options;
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

    unsigned long long virtualMemUsed;
#ifdef _WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
#else
    struct sysinfo memInfo{};
    sysinfo (&memInfo);
    virtualMemUsed = memInfo.totalram - memInfo.freeram;
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;
#endif
    std::cout << "Total virtual memory used: " << virtualMemUsed << std::endl;

    auto processManager = std::make_shared<resmond::ProcessManager>();
    auto resourceMonitor = std::make_shared<resmond::LinuxResourceMonitor>(processManager);

    // FOR DEBUGGING PURPOSES
    processManager->spawn("sleep 1000");
    std::cout << std::endl << "PID\tCPU%\tMEM%" << std::endl << std::endl;
    std::thread resourceMonitorThread([&resourceMonitor]() {
        while (true) {
            resourceMonitor->update();
            for (const auto &process : resourceMonitor->getResourceUsage()) {
                std::cout << process.first << "\t" << std::get<0>(process.second) << "\t" << std::get<0>(process.second)
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