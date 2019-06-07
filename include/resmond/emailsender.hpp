#ifndef RESMOND_EMAILSENDER_HPP
#define RESMOND_EMAILSENDER_HPP


#include <boost/process/child.hpp>
#include <queue>

namespace resmond {

    /*!
     * Class which provides methods used for sending an e-mail.
     */
    class EmailSender {
    public:
        explicit EmailSender(const std::string &mailerCommand, std::chrono::system_clock::time_point::duration cooldown);

        /*!
         * Method for sending e-mail notifications
         * @param pid process ID
         * @param command name of command
         * @param resource name of a resource which limits have been violated
         * @param limit value of a limit
         * @param usage violating usage
         */
        void sendViolationEmail(pid_t pid, const std::string &command, const std::string &resource, float limit,
                                float usage);

    private:
        std::chrono::system_clock::time_point::duration cooldown;
        std::map<pid_t, std::chrono::system_clock::time_point> lastSent;
        std::string mailerCommand;
        boost::process::child mailer;
    };

}


#endif //RESMOND_EMAILSENDER_HPP
