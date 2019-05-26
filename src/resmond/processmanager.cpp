#include <resmond/processmanager.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    void ProcessManager::terminate(int id) {
        if (!children.count(id)) {
            throw resmond::NoSuchChildError();
        }
        children.erase(id);
    }

    const std::map<pid_t, ProcessManager::Child> &ProcessManager::getChildren() const {
        return children;
    }

    int ProcessManager::spawn(std::string command) {
        auto child = std::make_shared<boost::process::child>(command);
        children[child->id()] = std::make_tuple(child, command);
        return child->id();
    }

}
