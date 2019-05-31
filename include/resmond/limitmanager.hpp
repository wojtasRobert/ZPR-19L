#ifndef RESMOND_LIMITMANAGER_HPP
#define RESMOND_LIMITMANAGER_HPP


#include <map>
#include <mutex>
#include <memory>

namespace resmond {

    class LimitManager {
    public:
        float getCpuLimit(pid_t id) const;

        float getMemoryLimit(pid_t id) const;

        void setCpuLimit(pid_t id, float limit);

        void setMemoryLimit(pid_t id, float limit);

        void clearLimits(pid_t id);

    private:
        std::map<pid_t, std::tuple<float, float>> resourceLimits;
        mutable std::mutex resourceLimitsMutex;
    };

}


#endif //RESMOND_LIMITMANAGER_HPP
