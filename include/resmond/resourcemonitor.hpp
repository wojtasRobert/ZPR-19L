#ifndef RESMOND_RESOURCEMONITOR_HPP
#define RESMOND_RESOURCEMONITOR_HPP


#include <fcntl.h>
#include <resmond/processmanager.hpp>

namespace resmond {

    class ResourceMonitor {
    public:
        explicit ResourceMonitor(const std::shared_ptr<ProcessManager> &processManager) : processManager(processManager) {}

        virtual void update() = 0;

        const std::map<pid_t, std::tuple<float, float>> &getResourceUsage() const;

    protected:
        std::shared_ptr<resmond::ProcessManager> processManager;
        std::map<pid_t, std::tuple<float, float>> resourceUsage;
        mutable std::mutex resourceUsageMutex;
    };

}


#endif //RESMOND_RESOURCEMONITOR_HPP
