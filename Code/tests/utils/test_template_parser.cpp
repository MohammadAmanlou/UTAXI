#include "gtest/gtest.h"
#include "template_parser.hpp"
#include <map>
#include <fstream>

class TemplateParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_template = "test_template.html";
        std::ofstream file(test_template);
        file << "<html><body><% context[\"name\"] %> </body></html>";
        file.close();
    }

    void TearDown() override {
        remove(test_template.c_str());
    }

    std::string test_template;
};

TEST_F(TemplateParserTest, ConstructorParsesTemplate) {
    TemplateParser parser(test_template);
    EXPECT_NO_THROW(parser.getHtml({{"name", "John"}}));
}

TEST_F(TemplateParserTest, GetHtmlGeneratesCorrectHtml) {
    TemplateParser parser(test_template);
    std::map<std::string, std::string> context = {{"name", "John"}};
    std::string html = parser.getHtml(context);
    EXPECT_NE(html.find("John"), std::string::npos);
}

TEST_F(TemplateTest, GetHtmlHandlesEmptyContext) {
    TemplateParser parser(test_template);
    std::map<std::string, std::string> context = {};
    std::string html = parser.getHtml(context);
    EXPECT_NE(html.find("<html><body> </body></html>"), std::string::npos);
}

TEST_F(TemplateParserTest, GetHtmlHandlesMultipleContextVariables) {
    std::ofstream file(test_template);
    file << "<html><body><% context[\"name\"] %> <% context[\"age\"] %> </body></html>";
    file.close();

    TemplateParser parser(test_template);
    std::map<std::string, std::string> context = {{"name", "John"}, {"age", "30"}};
    std::string html = parser.getHtml(context);
    EXPECT_NE(html.find("John 30"), std::string::npos);
}

TEST_F(TemplateParserTest, GetHtmlHandlesInvalidTemplate) {
    std::ofstream file(test_template);
    file << "<html><body><% invalid_code %> </body></html>";
    file.close();

    TemplateParser parser(test_template);
    std::map<std::string, std::string> context = {{"name", "John"}};
    EXPECT_THROW(parser.getHtml(context), Server::Exception);
}

TEST_F(TemplateParserTest, GetHtmlHandlesMissingContextVariable) {
    TemplateParser parser(test_template);
    std::map<std::string, std::string> context = {{"age", "30"}};
    std::string html = parser.getHtml(context);
    EXPECT_NE(html.find("<html><body> </body></html>"), std::string::npos);
}