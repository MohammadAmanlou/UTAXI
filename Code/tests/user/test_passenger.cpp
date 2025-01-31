#include <gtest/gtest.h>
#include "passenger.hpp"

class PassengerTest : public ::testing::Test {
protected:
    void SetUp() override {
        passenger = new Passenger("passenger_user");
    }

    void TearDown() override {
        delete passenger;
    }

    Passenger* passenger;
};

TEST_F(PassengerTest, Constructor) {
    EXPECT_EQ(passenger->get_username(), "passenger_user");
    EXPECT_TRUE(passenger->is_passenger());
    EXPECT_FALSE(passenger->is_driver());
}

TEST_F(PassengerTest, IsPassenger) {
    EXPECT_TRUE(passenger->is_passenger());
}

TEST_F(PassengerTest, IsDriver) {
    EXPECT_FALSE(passenger->is_driver());
}

TEST_F(PassengerTest, GetUsername) {
    EXPECT_EQ(passenger->get_username(), "passenger_user");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}