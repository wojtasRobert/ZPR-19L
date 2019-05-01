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
        int spawn(Args&&...args);

        /*!
         * Terminates a child.
         * @param id child's id
         * @throws resmond::NoSuchChildError
         */
        void terminate(int id);


    private:
        int freeId = 0;
        std::map<int, boost::process::child> children;
    };

    template<typename... Args>
    int ProcessManager::spawn(Args &&... args) {
        children[freeId] = boost::process::child(
            std::forward<Args>(args)...,
            boost::process::std_out > boost::process::null,
            boost::process::std_err > boost::process::null
        );

        return freeId++;
    }

}


#endif //RESMOND_PROCESSMANAGER_HPP
