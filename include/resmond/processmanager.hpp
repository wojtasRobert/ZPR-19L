#ifndef RESMOND_PROCESSMANAGER_HPP
#define RESMOND_PROCESSMANAGER_HPP


#include <vector>
#include <boost/process.hpp>

namespace resmond {

    class ProcessManager {
    public:

        /*!
         * Spawns a child process and adds it to the manager.
         * @param args same as boost::process::child
         * @return new child's id
         */
        template<typename ...Args>
        int spawn(Args &&...args);

        /*!
         * Terminates a child.
         * @param id child's id
         * @throws resmond::NoSuchChildError
         */
        void terminate(int id);

        const std::map<pid_t, std::shared_ptr<boost::process::child>> &getChildren() const;


    private:
        std::map<pid_t, std::shared_ptr<boost::process::child>> children;
    };

    template<typename... Args>
    int ProcessManager::spawn(Args &&... args) {
        auto child = std::make_shared<boost::process::child>(
            std::forward<Args>(args)...,
            boost::process::std_out > boost::process::null,
            boost::process::std_err > boost::process::null
        );
        children[child->id()] = child;
    }

}


#endif //RESMOND_PROCESSMANAGER_HPP
