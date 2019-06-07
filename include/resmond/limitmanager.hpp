#ifndef RESMOND_LIMITMANAGER_HPP
#define RESMOND_LIMITMANAGER_HPP


#include <map>
#include <mutex>
#include <memory>
#include <resmond/emailsender.hpp>

namespace resmond {

    /*!
     * Class which allows managing resources limits for processes.
     * Provides methods for setting and getting values of both resources.
     * If needed, limits can also be cleared.
     */
    class LimitManager {
    public:
        LimitManager();

        /*!
         * Returns value of CPU usage limit of given child.
         * @param id of a child process
         * @return CPU's limit
         */
        float getCpuLimit(pid_t id) const;

        /*!
         * Returns value of memory usage limit of given child.
         * @param id of a child process
         * @return Memory limit
         */
        float getMemoryLimit(pid_t id) const;

        /*!
         * Sets CPU limit for a child process
         * @param id of a child process
         * @param required CPU limit for a child process
         */
        void setCpuLimit(pid_t id, float limit);

        /*!
         * Sets memory limit for a child process
         * @param id of a child process
         * @param required memory limit for a child process
         */
        void setMemoryLimit(pid_t id, float limit);

        /*!
         * Clears limitations for a child process
         * @param id of a child process
         */
        void clearLimits(pid_t id);

    private:

        std::map<pid_t, std::tuple<float, float>> resourceLimits;
        mutable std::mutex resourceLimitsMutex;
    };

}


#endif //RESMOND_LIMITMANAGER_HPP
