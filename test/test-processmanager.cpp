#include <boost/test/unit_test.hpp>
#include <resmond/processmanager.hpp>

using namespace std::chrono_literals;

BOOST_AUTO_TEST_CASE(processmanager_test) {
    auto limitManager = std::make_shared<resmond::LimitManager>();
    auto processManager = std::make_shared<resmond::ProcessManager>(limitManager);

    pid_t id = processManager->spawn("sleep 100");
    BOOST_CHECK_EQUAL(std::get<0>(processManager->getChildren().at(id))->running(), true);
    BOOST_CHECK_EQUAL(std::get<1>(processManager->getChildren().at(id)), "sleep 100");

    processManager->terminate(id);
    BOOST_CHECK_EQUAL(processManager->getChildren().count(id), 0);
}