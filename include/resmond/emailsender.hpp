#ifndef RESMOND_EMAILSENDER_HPP
#define RESMOND_EMAILSENDER_HPP


#include <boost/process/child.hpp>
#include <queue>

namespace resmond {

    class EmailSender {
    public:
        explicit EmailSender(const std::string &mailerCommand, std::chrono::system_clock::time_point::duration cooldown);

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
