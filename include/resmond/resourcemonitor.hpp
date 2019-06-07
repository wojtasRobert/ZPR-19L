#ifndef RESMOND_RESOURCEMONITOR_HPP
#define RESMOND_RESOURCEMONITOR_HPP


#include <fcntl.h>
#include <boost/shared_ptr.hpp>

#include <resmond/processmanager.hpp>

namespace resmond {

    class ResourceMonitor {
    public:
        explicit ResourceMonitor(const std::shared_ptr<ProcessManager> &processManager);

        /*!
         * Updates information about resources used by monitored processes.
        */
        void update();

        /*!
         * @return map of processes and their resource usage.
         */
        const std::map<pid_t, std::tuple<float, float>> &getResourceUsage() const;

    protected:
        std::shared_ptr<resmond::ProcessManager> processManager;
        std::map<pid_t, std::tuple<float, float>> resourceUsage;
        mutable std::mutex resourceUsageMutex;
    };

}


#endif //RESMOND_RESOURCEMONITOR_HPP
