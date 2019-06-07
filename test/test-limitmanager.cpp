#include <boost/test/unit_test.hpp>
#include <resmond/limitmanager.hpp>

using namespace std::chrono_literals;

BOOST_AUTO_TEST_CASE(limitmanager_test) {
    auto limitManager = std::make_shared<resmond::LimitManager>();

    BOOST_CHECK_EQUAL(limitManager->getCpuLimit(42), 100);
    limitManager->setCpuLimit(42, 33);

    BOOST_CHECK_EQUAL(limitManager->getCpuLimit(42), 33);
    limitManager->setMemoryLimit(42, 21);
    BOOST_CHECK_EQUAL(limitManager->getMemoryLimit(42), 21);

    limitManager->setMemoryLimit(31, 66);
    BOOST_CHECK_EQUAL(limitManager->getMemoryLimit(31), 66);

    limitManager->clearLimits(42);
    BOOST_CHECK_EQUAL(limitManager->getCpuLimit(42), 100);
    BOOST_CHECK_EQUAL(limitManager->getMemoryLimit(42), 100);

    limitManager->clearLimits(31);
    BOOST_CHECK_EQUAL(limitManager->getCpuLimit(31), 100);
    BOOST_CHECK_EQUAL(limitManager->getMemoryLimit(31), 100);
}