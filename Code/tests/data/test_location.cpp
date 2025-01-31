#include "gtest/gtest.h"
#include "location.hpp"
#include <cmath>

class LocationTest : public ::testing::Test {
protected:
    void SetUp() override {
        loc1 = new Location("loc1", 10.0, 20.0, 5);
        loc2 = new Location("loc2", 15.0, 25.0, 10);
    }

    void TearDown() override {
        delete loc1;
        delete loc2;
    }

    Location* loc1;
    Location* loc2;
};

TEST_F(LocationTest, ConstructorInitializesLocation) {
    EXPECT_EQ(loc1->get_name(), "loc1");
    EXPECT_EQ(loc1->distance_to(loc2), LENGTH_OF_A_DEGREE * calc_linear_dist(10.0, 20.0, 15.0, 25.0));
    EXPECT_EQ(loc1->traffic_to(loc2), 15);
}

TEST_F(LocationTest, IsSameAsReturnsTrueForSameName) {
    EXPECT_TRUE(loc1->is_same_as("loc1"));
}

TEST_F(LocationTest, IsSameAsReturnsFalseForDifferentName) {
    EXPECT_FALSE(loc1->is_same_as("loc2"));
}

TEST_F(LocationTest, DistanceToReturnsCorrectDistance) {
    double expected_distance = LENGTH_OF_A_DEGREE * calc_linear_dist(10.0, 20.0, 15.0, 25.0);
    EXPECT_DOUBLE_EQ(loc1->distance_to(loc2), expected_distance);
}

TEST_F(LocationTest, TrafficToReturnsCorrectTraffic) {
    EXPECT_EQ(loc1->traffic_to(loc2), 15);
}