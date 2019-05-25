#include <resmond/linuxresourcemonitor.hpp>
#include <fcntl.h>
#include <boost/filesystem/fstream.hpp>
#include <boost/process.hpp>
#include <sstream>

namespace resmond {

    LinuxResourceMonitor::LinuxResourceMonitor(const std::shared_ptr<ProcessManager> &processManager) : ResourceMonitor(
        processManager) {}

    void LinuxResourceMonitor::update() {
        namespace bp = boost::process;

        std::string propertyList = "top -b -n 1 ";

        for (const auto &child : processManager->getChildren()) {
            propertyList += "-p " + std::to_string(child.second->id()) + " ";
        }

        bp::ipstream is;
        auto top = boost::process::child(propertyList, bp::std_out > is);

        resourceUsage.clear();
        std::string line;
        for (int i = 0; top.running() && std::getline(is, line); ++i) {
            std::stringstream ss{line};
            std::vector<std::string> result(std::istream_iterator<std::string>{ss},
                                            std::istream_iterator<std::string>());

            if (i >= 7) {
                resourceUsage[std::stoi(result[0])] = {std::stod(result[8]), std::stod(result[9])};
            }
        }

        top.wait();
    }

}
