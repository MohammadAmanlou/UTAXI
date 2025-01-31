#include <gtest/gtest.h>
#include "request.hpp"
#include <map>
#include <string>

class RequestTest : public ::testing::Test {
protected:
    void SetUp() override {
        request = new Request("GET");
    }

    void TearDown() override {
        delete request;
    }

    Request* request;
};

TEST_F(RequestTest, Constructor) {
    EXPECT_EQ(request->getMethod(), GET);
    EXPECT_EQ(request->getPath(), "");
}

TEST_F(RequestTest, SetAndGetPath) {
    request->setPath("/test");
    EXPECT_EQ(request->getPath(), "/test");
}

TEST_F(RequestTest, SetAndGetQueryParam) {
    request->setQueryParam("key", "value");
    EXPECT_EQ(request->getQueryParam("key"), "value");
}

TEST_F(RequestTest, SetAndGetBodyParam) {
    request->setBodyParam("key", "value");
    EXPECT_EQ(request->getBodyParam("key"), "value");
}

TEST_F(RequestTest, SetAndGetHeader) {
    request->setHeader("Content-Type", "application/json");
    EXPECT_EQ(request->getHeader("Content-Type"), "application/json");
}

TEST_F(RequestTest, GetBody) {
    request->setBodyParam("key1", "value1");
    request->setBodyParam("key2", "value2");
    EXPECT_EQ(request->getBody(), "key1=value1&key2=value2&");
}

TEST_F(RequestTest, GetSessionId) {
    request->setHeader("cookie", "sessionId=12345; other=value");
    EXPECT_EQ(request->getSessionId(), "12345");
}

TEST_F(RequestTest, GetQueryString) {
    request->setQueryParam("key1", "value1");
    request->setQueryParam("key2", "value2");
    EXPECT_EQ(request->getQueryString(), "?key1=value1&key2=value2&");
}

TEST_F(RequestTest, GetHeadersString) {
    request->setHeader("Header1", "Value1");
    request->setHeader("Header2", "Value2");
    EXPECT_EQ(request->getHeadersString(), "Header1=Value1&Header2=Value2&");
}

TEST_F(RequestTest, SerializeAndDeserialize) {
    request->setPath("/test");
    request->setMethod(POST);
    request->setHeader("Content-Type", "application/json");
    request->setQueryParam("key", "value");
    request->setBodyParam("bodyKey", "bodyValue");

    Request::serializeToFile(request, "request.txt");

    Request* deserializedRequest = new Request();
    Request::deserializeFromFile(deserializedRequest, "request.txt");

    EXPECT_EQ(deserializedRequest->getPath(), "/test");
    EXPECT_EQ(deserializedRequest->getMethod(), POST);
    EXPECT_EQ(deserializedRequest->getHeader("Content-Type"), "application/json");
    EXPECT_EQ(deserializedRequest->getQueryParam("key"), "value");
    EXPECT_EQ(deserializedRequest->getBodyParam("bodyKey"), "bodyValue");

    delete deserializedRequest;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}