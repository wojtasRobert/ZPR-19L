#include <resmond/processmanager.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    void ProcessManager::terminate(int id) {
        if (!children.count(id)) {
            throw resmond::NoSuchChildError();
        }
        children.erase(id);
    }

    const std::map<pid_t, std::shared_ptr<boost::process::child>> &ProcessManager::getChildren() const {
        return children;
    }

}
