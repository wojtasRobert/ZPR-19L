#include <iostream>
#include <server_http.hpp>

#include <resmond/clientinterface.hpp>
#include <resmond/processmanager.hpp>
#include <resmond/resourcemonitor.hpp>
#include <resmond/limitmanager.hpp>

int main(int argc, char *argv[]) {

    using namespace std::chrono_literals;

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