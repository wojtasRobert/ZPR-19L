#ifndef RESMOND_PROCESSMANAGER_HPP
#define RESMOND_PROCESSMANAGER_HPP


#include <vector>
#include <boost/process.hpp>

namespace resmond {

    class ProcessManager {
    public:
        typedef std::tuple<std::shared_ptr<boost::process::child>, std::string> Child;

        /*!
         * Spawns a child process and adds it to the manager.
         * @param args same as boost::process::child
         * @return new child's id
         */
        int spawn(std::string command);

        /*!
         * Terminates a child.
         * @param id child's id
         * @throws resmond::NoSuchChildError
         */
        void terminate(int id);

        const std::map<pid_t, Child> &getChildren() const;


    private:
        std::map<pid_t, Child> children;
    };

}


#endif //RESMOND_PROCESSMANAGER_HPP
