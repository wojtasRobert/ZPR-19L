#include <thread>
#include <chrono>
#include <boost/test/unit_test.hpp>
#include <client_http.hpp>
#include <resmond/clientinterface.hpp>

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
using namespace std::chrono_literals;

BOOST_AUTO_TEST_CASE(clientinterface_test) {
    auto limitManager = std::make_shared<resmond::LimitManager>();
    auto emailSender = std::make_shared<resmond::EmailSender>("../script/mailer", 5min);
    auto processManager = std::make_shared<resmond::ProcessManager>(limitManager);
    auto resourceMonitor = std::make_shared<resmond::ResourceMonitor>(emailSender, processManager, limitManager);
    resmond::ClientInterface clientInterface("127.0.0.1", 8081, processManager, resourceMonitor, limitManager);
    std::this_thread::sleep_for(2s);

    HttpClient client("localhost:8081");
    client.request("POST", "/ping", [&clientInterface](std::shared_ptr<HttpClient::Response> response, const SimpleWeb::error_code &ec) {
        if(!ec) {
            std::string text((std::istreambuf_iterator<char>(response->content.rdbuf())), std::istreambuf_iterator<char>());
            BOOST_CHECK_EQUAL(text, "pong");
            clientInterface.stop();
        }
    });
    client.io_service->run();

    clientInterface.joinServerThread();
}