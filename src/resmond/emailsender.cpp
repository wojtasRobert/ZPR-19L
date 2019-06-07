#include <resmond/emailsender.hpp>

namespace resmond {

    EmailSender::EmailSender(const std::string &mailerCommand, std::chrono::system_clock::time_point::duration cooldown)
        : mailerCommand(mailerCommand), cooldown(cooldown) {}

    void
    EmailSender::sendViolationEmail(pid_t pid, const std::string &command, const std::string &resource, float limit) {
        if (mailer.running()) {
            throw std::runtime_error("Previous email was not yet sent");
        }

        if (lastSent.count(pid) && std::chrono::system_clock::now() - lastSent[pid] < cooldown) {
            return;
        }

        mailer = boost::process::child(
            mailerCommand + " "
            + std::to_string(pid) + " "
            + command + " "
            + resource + " "
            + std::to_string(limit)
        );

        lastSent[pid] = std::chrono::system_clock::now();
    }
}