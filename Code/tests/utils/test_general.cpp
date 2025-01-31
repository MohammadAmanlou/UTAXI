#include <gtest/gtest.h>
#include "general.hpp"
#include <vector>
#include <string>

TEST(GeneralTest, ParseLine) {
    std::string line = "one,two,three";
    std::string delimiter = ",";
    std::vector<std::string> tokens = parse_line(line, delimiter);
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "one");
    EXPECT_EQ(tokens[1], "two");
    EXPECT_EQ(tokens[2], "three");
}

TEST(GeneralTest, CalcLinearDist) {
    double lat1 = 0.0, long1 = 0.0;
    double lat2 = 3.0, long2 = 4.0;
    double dist = calc_linear_dist(lat1, long1, lat2, long2);
    EXPECT_DOUBLE_EQ(dist, 5.0);
}

TEST(GeneralTest, HasId) {
    std::vector<std::string> tokens = {"id", "sort_by_cost", "username"};
    EXPECT_TRUE(has_id(tokens));

    tokens = {"sort_by_cost", "username"};
    EXPECT_FALSE(has_id(tokens));
}

TEST(GeneralTest, HasCostSort) {
    std::vector<std::string> tokens = {"id", "sort_by_cost", "username"};
    EXPECT_TRUE(has_cost_sort(tokens));

    tokens = {"id", "username"};
    EXPECT_FALSE(has_cost_sort(tokens));
}

TEST(GeneralTest, ChangeErrorText) {
    std::string err_text = "Test error message";
    change_error_text(err_text);

    std::ifstream js_err("static/js_files/error.js");
    std::string content((std::istreambuf_iterator<char>(js_err)), std::istreambuf_iterator<char>());
    EXPECT_EQ(content, "alert(\'Test error message\');");

    change_error_text("");
    js_err.close();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}