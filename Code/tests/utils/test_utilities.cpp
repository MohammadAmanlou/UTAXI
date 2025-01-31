#include "gtest/gtest.h"
#include "utilities.hpp"
#include <fstream>
#include <map>
#include <vector>

class UtilitiesTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_file = "test_file.txt";
        std::ofstream file(test_file);
        file << "Hello, World!\nThis is a test file.\n";
        file.close();
    }

    void TearDown() override {
        remove(test_file.c_str());
    }

    std::string test_file;
};

TEST_F(UtilitiesTest, ToLowerCaseConvertsStringToLowercase) {
    std::string input = "Hello World!";
    std::string expected = "hello world!";
    EXPECT_EQ(toLowerCase(input), expected);
}

TEST_F(UtilitiesTest, ReadFileReadsFileContent) {
    std::string content = readFile(test_file);
    std::string expected = "Hello, World!\nThis is a test file.\n";
    EXPECT_EQ(content, expected);
}

TEST_F(UtilitiesTest, SplitSplitsStringByDelimiter) {
    std::string input = "one,two,three";
    std::vector<std::string> expected = {"one", "two", "three"};
    EXPECT_EQ(split(input, ","), expected);
}

TEST_F(UtilitiesTest, UrlEncodeEncodesSpecialCharacters) {
    std::string input = "Hello World!";
    std::string expected = "Hello%20World%21";
    EXPECT_EQ(urlEncode(input), expected);
}

TEST_F(UtilitiesTest, UrlDecodeDecodesSpecialCharacters) {
    std::string input = "Hello%20World%21";
    std::string expected = "Hello World!";
    EXPECT_EQ(urlDecode(input), expected);
}

TEST_F(UtilitiesTest, GetExtensionReturnsFileExtension) {
    std::string file_path = "test_file.txt";
    std::string expected = "txt";
    EXPECT_EQ(getExtension(file_path), expected);
}

TEST_F(UtilitiesTest, TokenizeSplitsStringByDelimiter) {
    std::string input = "one two three";
    std::vector<std::string> expected = {"one", "two", "three"};
    EXPECT_EQ(tokenize(input, ' '), expected);
}

TEST_F(UtilitiesTest, ReplaceAllReplacesAllOccurrences) {
    std::string input = "Hello World!";
    replaceAll(input, "World", "Universe");
    std::string expected = "Hello Universe!";
    EXPECT_EQ(input, expected);
}

TEST_F(UtilitiesTest, FindSubStrPositionFindsSubstring) {
    std::string input = "Hello World!";
    int pos = findSubStrPosition(input, "World", 0);
    EXPECT_EQ(pos, 6);
}

TEST_F(UtilitiesTest, WriteToFileWritesContentToFile) {
    std::string content = "Test content";
    std::string file_path = "output.txt";
    writeToFile(content, file_path);
    std::string read_content = readFile(file_path);
    EXPECT_EQ(read_content, content);
    remove(file_path.c_str());
}

TEST_F(UtilitiesTest, GetCimapFromStringParsesKeyValuePairs) {
    std::string input = "key1=value1&key2=value2";
    cimap expected = {{"key1", "value1"}, {"key2", "value2"}};
    EXPECT_EQ(getCimapFromString(input), expected);
}

TEST_F(UtilitiesTest, ReadMapFromFileReadsKeyValuePairs) {
    std::string file_path = "map_file.txt";
    std::ofstream file(file_path);
    file << "key1=value1\nkey2=value2\n";
    file.close();

    std::map<std::string, std::string> map;
    readMapFromFile(file_path, &map);

    std::map<std::string, std::string> expected = {{"key1", "value1"}, {"key2", "value2"}};
    EXPECT_EQ(map, expected);

    remove(file_path.c_str());
}