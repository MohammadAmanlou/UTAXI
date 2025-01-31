#include <gtest/gtest.h>
#include "driver.hpp"

class DriverTest : public ::testing::Test {
protected:
    void SetUp() override {
        driver = new Driver("driver_user");
    }

    void TearDown() override {
        delete driver;
    }

    Driver* driver;
};

TEST_F(DriverTest, Constructor) {
    EXPECT_EQ(driver->get_username(), "driver_user");
    EXPECT_FALSE(driver->is_passenger());
    EXPECT_TRUE(driver->is_driver());
}

TEST_F(DriverTest, IsPassenger) {
    EXPECT_FALSE(driver->is_passenger());
}

TEST_F(DriverTest, IsDriver) {
    EXPECT_TRUE(driver->is_driver());
}

TEST_F(DriverTest, GetUsername) {
    EXPECT_EQ(driver->get_username(), "driver_user");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}