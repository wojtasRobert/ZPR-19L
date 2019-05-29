#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/process.hpp>

#include <resmond/resourcemonitor.hpp>

namespace resmond {

    ResourceMonitor::ResourceMonitor(const std::shared_ptr<ProcessManager> &processManager) : processManager(
        processManager) {}

    void ResourceMonitor::update() {
        // TODO: simplify this mess
        namespace bp = boost::process;

        auto children = processManager->getChildren();

        if (children.empty()) {
            std::lock_guard<std::mutex> lock(resourceUsageMutex);
            resourceUsage.clear();
            return;
        }

        std::string propertyList = "top -b -n 1 ";

        for (const auto &child : children) {
            propertyList += "-p " + std::to_string(std::get<0>(child.second)->id()) + " ";
        }

        bp::ipstream is;
        auto top = boost::process::child(propertyList, bp::std_out > is);

        std::lock_guard<std::mutex> lock(resourceUsageMutex);
        resourceUsage.clear();
        std::string line;
        for (int i = 0; top.running() && std::getline(is, line); ++i) {
            std::stringstream ss{line};
            std::vector<std::string> result(std::istream_iterator<std::string>{ss},
                                            std::istream_iterator<std::string>());

            if (i >= 7) {
                int pid = std::stoi(result[0]);
                if (std::get<0>(children[pid])->running()) {
                    resourceUsage[pid] = {std::stod(result[8]), std::stod(result[9])};
                }
            }
        }

        top.wait();
    }

    const std::map<pid_t, std::tuple<float, float>> &ResourceMonitor::getResourceUsage() const {
        std::lock_guard<std::mutex> lock(resourceUsageMutex);
        return resourceUsage;
    }

}
