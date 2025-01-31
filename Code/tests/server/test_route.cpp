#include <gtest/gtest.h>
#include "route.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"

class MockRequestHandler : public RequestHandler {
public:
    Response* callback(Request* req) override {
        return new Response("Mock Response", 200);
    }
};

class RouteTest : public ::testing::Test {
protected:
    void SetUp() override {
        handler = new MockRequestHandler();
        route = new Route(GET, "/test");
        route->setHandler(handler);
    }

    void TearDown() override {
        delete route;
    }

    Route* route;
    RequestHandler* handler;
};

TEST_F(RouteTest, Constructor) {
    EXPECT_EQ(route->isMatch(GET, "/test"), true);
    EXPECT_EQ(route->isMatch(POST, "/test"), false);
    EXPECT_EQ(route->isMatch(GET, "/wrong"), false);
}

TEST_F(RouteTest, IsMatch) {
    EXPECT_TRUE(route->isMatch(GET, "/test"));
    EXPECT_FALSE(route->isMatch(POST, "/test"));
    EXPECT_FALSE(route->isMatch(GET, "/invalid"));
}

TEST_F(RouteTest, Handle) {
    Request* req = new Request(GET, "/test");
    Response* res = route->handle(req);
    EXPECT_EQ(res->getBody(), "Mock Response");
    EXPECT_EQ(res->getStatusCode(), 200);
    delete req;
    delete res;
}

TEST_F(RouteTest, SetHandler) {
    RequestHandler* newHandler = new MockRequestHandler();
    route->setHandler(newHandler);
    Request* req = new Request(GET, "/test");
    Response* res = route->handle(req);
    EXPECT_EQ(res->getBody(), "Mock Response");
    EXPECT_EQ(res->getStatusCode(), 200);
    delete req;
    delete res;
    delete newHandler;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}