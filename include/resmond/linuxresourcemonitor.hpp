#ifndef RESMOND_LINUXRESOURCEMONITOR_HPP
#define RESMOND_LINUXRESOURCEMONITOR_HPP


#include <resmond/resourcemonitor.hpp>
#include <fcntl.h>
#include <boost/shared_ptr.hpp>

namespace resmond {

    class LinuxResourceMonitor : public ResourceMonitor {
    public:
        explicit LinuxResourceMonitor(const std::shared_ptr<ProcessManager> &processManager);

        void update() override;
    };

}


#endif //RESMOND_LINUXRESOURCEMONITOR_HPP
