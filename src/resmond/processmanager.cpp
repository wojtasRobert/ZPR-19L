#include <resmond/processmanager.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    void ProcessManager::terminate(int id) {
        std::lock_guard<std::mutex> lock(childrenMutex);
        if (!children.count(id)) {
            throw resmond::NoSuchChildError();
        }
        children.erase(id);
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
