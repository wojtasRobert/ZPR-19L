#define BOOST_TEST_MODULE ClientInterface
#include <thread>
#include <chrono>
#include <boost/test/unit_test.hpp>
#include <client_http.hpp>
#include <resmond/clientinterface.hpp>

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

BOOST_AUTO_TEST_CASE(clientinterface_test) {
    resmond::ClientInterface clientInterface("127.0.0.1", 8081);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    HttpClient client("localhost:8081");
    client.request("POST", "/", [&clientInterface](std::shared_ptr<HttpClient::Response> response, const SimpleWeb::error_code &ec) {
        if(!ec) {
            std::string text((std::istreambuf_iterator<char>(response->content.rdbuf())), std::istreambuf_iterator<char>());
            BOOST_CHECK_EQUAL(text, "Hello.");
            clientInterface.stop();
        }
    });
    client.io_service->run();

    clientInterface.joinServerThread();
}