#include <resmond/resourcemonitor.hpp>

namespace resmond {

    const std::map<pid_t, std::tuple<float, float>> &ResourceMonitor::getResourceUsage() const {
        std::lock_guard<std::mutex> lock(resourceUsageMutex);
        return resourceUsage;
    }
}