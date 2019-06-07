#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/process.hpp>

#include <resmond/resourcemonitor.hpp>

namespace resmond {

    void ResourceMonitor::update() {
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
                    sendIfLimitViolated(pid, std::get<0>(resourceUsage[pid]), std::get<1>(resourceUsage[pid]));
                }
            }
        }

        top.wait();
    }

    const std::map<pid_t, std::tuple<float, float>> &ResourceMonitor::getResourceUsage() const {
        std::lock_guard<std::mutex> lock(resourceUsageMutex);
        return resourceUsage;
    }

    void ResourceMonitor::sendIfLimitViolated(pid_t id, float cpuUsage, float memoryUsage) {
        auto cpuLimit = limitManager->getCpuLimit(id);
        auto memoryLimit = limitManager->getMemoryLimit(id);

        if (cpuUsage > cpuLimit) {
            emailSender->sendViolationEmail(
                id,
                std::get<1>(processManager->getChildren().at(id)),
                "cpu",
                cpuLimit,
                cpuUsage
            );
        }

        if (cpuUsage > cpuLimit) {
            emailSender->sendViolationEmail(
                id,
                std::get<1>(processManager->getChildren().at(id)),
                "memory",
                memoryLimit,
                memoryUsage
            );
        }
    }

    ResourceMonitor::ResourceMonitor(const std::shared_ptr<EmailSender> &emailSender,
                                     const std::shared_ptr<ProcessManager> &processManager,
                                     const std::shared_ptr<LimitManager> &limitManager)
        : emailSender(emailSender), processManager(processManager), limitManager(limitManager) {}

}
