#ifndef RESMOND_PROCESSMANAGER_HPP
#define RESMOND_PROCESSMANAGER_HPP


#include <vector>
#include <boost/process.hpp>

#include <resmond/limitmanager.hpp>

namespace resmond {

    /*!
     * Class which enables creating objects to manage processes.
     * Primary tasks for ProcessManager object are spawning and terminating children processes.
     */
    class ProcessManager {
    public:
        typedef std::tuple<std::shared_ptr<boost::process::child>, std::string> Child;

        ProcessManager(const std::shared_ptr<LimitManager> &limitManager);

        /*!
         * Spawns a child process and adds it to the manager.
         * @param command the command to be executed
         * @return new child's id
         */
        int spawn(std::string command);

        /*!
         * Terminates a child.
         * @param id child's id
         * @throws resmond::NoSuchChildError
         */
        void terminate(int id);

        /*!
         * @return map of children processes and their IDs.
         */
        const std::map<pid_t, Child> &getChildren() const;


    private:
        std::shared_ptr<resmond::LimitManager> limitManager;
        std::map<pid_t, Child> children;
        mutable std::mutex childrenMutex;
    };

}


#endif //RESMOND_PROCESSMANAGER_HPP
