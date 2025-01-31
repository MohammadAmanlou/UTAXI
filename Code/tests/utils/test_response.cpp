#include <gtest/gtest.h>
#include "response.hpp"
#include <string>

class ResponseTest : public ::testing::Test {
protected:
    void SetUp() override {
        response = new Response(200);
    }

    void TearDown() override {
        delete response;
    }

    Response* response;
};

TEST_F(ResponseTest, Constructor) {
    EXPECT_EQ(response->getStatusCode(), 200);
    EXPECT_EQ(response->getStatusPhrase(), "OK");
}

TEST_F(ResponseTest, SetAndGetStatus) {
    response->setStatus(404, "Not Found");
    EXPECT_EQ(response->getStatusCode(), 404);
    EXPECT_EQ(response->getStatusPhrase(), "Not Found");

    response->setStatus(303);
    EXPECT_EQ(response->getStatusCode(), 303);
    EXPECT_EQ(response->getStatusPhrase(), "See Other");
}

TEST_F(ResponseTest, SetAndGetHeader) {
    response->setHeader("Content-Type", "application/json");
    EXPECT_EQ(response->getHeader("Content-Type"), "");
}

TEST_F(ResponseTest, SetAndGetBody) {
    response->setBody("Test Body");
    EXPECT_EQ(response->getHeader("Content-Length"), "");
}

TEST_F(ResponseTest, Print) {
    response->setBody("Test Body");
    int size;
    std::string printedResponse = response->print(size);
    EXPECT_NE(printedResponse.find("HTTP/1.0 200 OK"), std::string::npos);
    EXPECT_NE(printedResponse.find("Content-Length: 9"), std::string::npos);
    EXPECT_NE(printedResponse.find("Test Body"), std::string::npos);
}

TEST_F(ResponseTest, Redirect) {
    Response* redirectResponse = Response::redirect("/new-location");
    EXPECT_EQ(redirectResponse->getStatusCode(), 303);
    EXPECT_EQ(redirectResponse->getHeader("Location"), "");
    delete redirectResponse;
}

TEST_F(ResponseTest, SetSessionId) {
    response->setSessionId("12345");
    EXPECT_EQ(response->getHeader("set-cookie"), "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}