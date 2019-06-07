#ifndef RESMOND_RESOURCEMONITOR_HPP
#define RESMOND_RESOURCEMONITOR_HPP


#include <fcntl.h>
#include <boost/shared_ptr.hpp>

#include <resmond/processmanager.hpp>

namespace resmond {

    class ResourceMonitor {
    public:
        ResourceMonitor(const std::shared_ptr<EmailSender> &emailSender,
                        const std::shared_ptr<ProcessManager> &processManager,
                        const std::shared_ptr<LimitManager> &limitManager);

        /*!
         * Updates information about resources used by monitored processes.
        */
        void update();

        void sendIfLimitViolated(pid_t id, float cpuUsage, float memoryUsage);

        /*!
         * @return map of processes and their resource usage.
         */
        const std::map<pid_t, std::tuple<float, float>> &getResourceUsage() const;

        enum class Resource {
            CPU = 0,
            MEMORY = 1,
        };

    protected:
        std::shared_ptr<EmailSender> emailSender;
        std::shared_ptr<resmond::ProcessManager> processManager;
        std::shared_ptr<resmond::LimitManager> limitManager;
        std::map<pid_t, std::tuple<float, float>> resourceUsage;
        mutable std::mutex resourceUsageMutex;
    };

}


#endif //RESMOND_RESOURCEMONITOR_HPP
