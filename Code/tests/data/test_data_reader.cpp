#include "gtest/gtest.h"
#include "data_reader.hpp"
#include <fstream>
#include <vector>
#include <string>

class DataReaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream test_file("test_data.csv");
        test_file << "Header\n";
        test_file << "Location1,10,20\n";
        test_file << "Location2,30,40\n";
        test_file.close();
    }

    void TearDown() override {
        remove("test_data.csv");
    }

    DataReader reader;
};

TEST_F(DataReaderTest, ConstructorInitializesLocsNumToZero) {
    EXPECT_EQ(reader.get_locs_num(), 0);
}

TEST_F(DataReaderTest, ReadMethodReadsFileCorrectly) {
    reader.read("test_data.csv");
    EXPECT_EQ(reader.get_locs_num(), 2);
    std::vector<std::string> expected_data = {"Location1,10,20", "Location2,30,40"};
    for (int i = 0; i < expected_data.size(); ++i) {
        EXPECT_EQ(reader.provide_loc_raw_data(i), expected_data[i]);
    }
}

TEST_F(DataReaderTest, ProvideLocRawDataReturnsCorrectTokens) {
    reader.read("test_data.csv");
    std::vector<std::string> tokens = reader.provide_loc_raw_data(0);
    std::vector<std::string> expected_tokens = {"Location1", "10", "20"};
    EXPECT_EQ(tokens, expected_tokens);
    tokens = reader.provide_loc_raw_data(1);
    expected_tokens = {"Location2", "30", "40"};
    EXPECT_EQ(tokens, expected_tokens);
}

TEST_F(DataReaderTest, ProvideLocRawDataHandlesInvalidIndex) {
    reader.read("test_data.csv");
    EXPECT_THROW(reader.provide_loc_raw_data(2), std::out_of_range);
}