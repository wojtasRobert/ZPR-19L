#include <iostream>
#include <boost/program_options.hpp>
#include <server_http.hpp>
#include <resmond/clientinterface.hpp>

#ifndef _WIN32
    #include <sys/types.h>
    #include <sys/sysinfo.h>
#endif

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
    resmond::ClientInterface clientInterface("127.0.0.1", 8081, processManager);
    clientInterface.joinServerThread();

    return 0;
}