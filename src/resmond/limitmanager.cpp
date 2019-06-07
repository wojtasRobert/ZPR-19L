#include <resmond/limitmanager.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    LimitManager::LimitManager() {

    }

    float LimitManager::getCpuLimit(pid_t id) const {
        std::lock_guard<std::mutex> lock(resourceLimitsMutex);
        if (resourceLimits.find(id) == resourceLimits.end() || std::get<0>(resourceLimits.at(id)) == 0) {
            return 100;
        }
        return std::get<0>(resourceLimits.at(id));
    }

    float LimitManager::getMemoryLimit(pid_t id) const {
        std::lock_guard<std::mutex> lock(resourceLimitsMutex);
        if (resourceLimits.find(id) == resourceLimits.end() || std::get<1>(resourceLimits.at(id)) == 0) {
            return 100;
        }
        return std::get<1>(resourceLimits.at(id));
    }

    void LimitManager::setCpuLimit(pid_t id, float limit) {
        std::lock_guard<std::mutex> lock(resourceLimitsMutex);
        std::get<0>(resourceLimits[id]) = limit;
    }

    void LimitManager::setMemoryLimit(pid_t id, float limit) {
        std::lock_guard<std::mutex> lock(resourceLimitsMutex);
        std::get<1>(resourceLimits[id]) = limit;
    }

    void LimitManager::clearLimits(pid_t id) {
        std::lock_guard<std::mutex> lock(resourceLimitsMutex);
        resourceLimits.erase(id);
    }

}