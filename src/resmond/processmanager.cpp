#include <resmond/processmanager.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    ProcessManager::ProcessManager(const std::shared_ptr<LimitManager> &limitManager) : limitManager(limitManager) {}

    void ProcessManager::terminate(int id) {
        std::lock_guard<std::mutex> lock(childrenMutex);
        if (!children.count(id)) {
            throw resmond::NoSuchChildError();
        }
        children.erase(id);
        limitManager->clearLimits(id);
    }

    const std::map<pid_t, ProcessManager::Child> &ProcessManager::getChildren() const {
        std::lock_guard<std::mutex> lock(childrenMutex);
        return children;
    }

    int ProcessManager::spawn(std::string command) {
        auto child = std::make_shared<boost::process::child>(command);
        {
            std::lock_guard<std::mutex> lock(childrenMutex);
            children[child->id()] = std::make_tuple(child, command);
        }
        return child->id();
    }

}
