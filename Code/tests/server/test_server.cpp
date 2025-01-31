#include <gtest/gtest.h>
#include "server.hpp"
#include "route.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"

class MockRequestHandler : public RequestHandler {
public:
    Response* callback(Request* req) override {
        return new Response("Mock Response", 200);
    }
};

class ServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        server = new Server(8080);
        handler = new MockRequestHandler();
    }

    void TearDown() override {
        delete server;
        delete handler;
    }

    Server* server;
    RequestHandler* handler;
};

TEST_F(ServerTest, AddGetRoute) {
    server->get("/test", handler);
    EXPECT_EQ(server->getRoutes().size(), 1);
}

TEST_F(ServerTest, AddPostRoute) {
    server->post("/test", handler);
    EXPECT_EQ(server->getRoutes().size(), 1);
}

TEST_F(ServerTest, HandleRequest) {
    server->get("/test", handler);
    Request* req = new Request(GET, "/test");
    Response* res = server->handleRequest(req);
    EXPECT_EQ(res->getBody(), "Mock Response");
    EXPECT_EQ(res->getStatusCode(), 200);
    delete req;
    delete res;
}

TEST_F(ServerTest, HandleNotFound) {
    Request* req = new Request(GET, "/nonexistent");
    Response* res = server->handleRequest(req);
    EXPECT_EQ(res->getStatusCode(), 404);
    delete req;
    delete res;
}

TEST_F(ServerTest, SetNotFoundErrPage) {
    server->setNotFoundErrPage("404.html");
    Request* req = new Request(GET, "/nonexistent");
    Response* res = server->handleRequest(req);
    EXPECT_EQ(res->getStatusCode(), 404);
    delete req;
    delete res;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}