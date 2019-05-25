#include <resmond/resourcemonitor.hpp>

namespace resmond {

    const std::map<pid_t, std::tuple<float, float>> &ResourceMonitor::getResourceUsage() const {
        return resourceUsage;
    }
}