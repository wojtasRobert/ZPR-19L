#include <resmond/processmanager.hpp>
#include <resmond/exceptions.hpp>

namespace resmond {

    void ProcessManager::terminate(int id) {
        if (!children.count(id)) {
            throw resmond::NoSuchChildError();
        }
        children.erase(id);
    }

}
