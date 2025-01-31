#include <gtest/gtest.h>
#include "trip.hpp"
#include "location.hpp"
#include "../user/member.hpp"

class MockLocation : public Location {
public:
    MockLocation(double x, double y) : Location(x, y) {}
    double distance_to(Location* other) override {
        return 10.0; 
    }
    int traffic_to(Location* other) override {
        return 2; 
    }
};

class MockMember : public Member {
public:
    MockMember(int id) : Member(id) {}
};

class TripTest : public ::testing::Test {
protected:
    void SetUp() override {
        passenger = new MockMember(1);
        origin = new MockLocation(0.0, 0.0);
        destination = new MockLocation(1.0, 1.0);
        trip = new Trip(passenger, origin, destination, 123);
    }

    void TearDown() override {
        delete trip;
        delete passenger;
        delete origin;
        delete destination;
    }

    Member* passenger;
    Location* origin;
    Location* destination;
    Trip* trip;
};

TEST_F(TripTest, Constructor) {
    EXPECT_EQ(trip->get_passenger(), passenger);
    EXPECT_EQ(trip->get_origin(), origin);
    EXPECT_EQ(trip->get_destination(), destination);
    EXPECT_EQ(trip->get_id(), 123);
    EXPECT_EQ(trip->get_status(), TRIP_WAITING);
    EXPECT_EQ(trip->get_price(), 0.0);
}

TEST_F(TripTest, CalcPriceNoHurry) {
    double price = trip->calc_price(false);
    EXPECT_DOUBLE_EQ(price, 10.0 * 2 * PRICE_COEFFICIENT);
    EXPECT_DOUBLE_EQ(trip->get_price(), price);
}

TEST_F(TripTest, CalcPriceWithHurry) {
    double price = trip->calc_price(true);
    EXPECT_DOUBLE_EQ(price, HURRY_COEFFICIENT * 10.0 * 2 * PRICE_COEFFICIENT);
    EXPECT_DOUBLE_EQ(trip->get_price(), price);
}

TEST_F(TripTest, StatusChanges) {
    trip->start();
    EXPECT_EQ(trip->get_status(), TRIP_TRAVELING);

    trip->finish();
    EXPECT_EQ(trip->get_status(), TRIP_FINISHED);

    trip->delete_yourself();
    EXPECT_EQ(trip->get_status(), TRIP_DELETED);
}

TEST_F(TripTest, IsSameAs) {
    EXPECT_TRUE(trip->is_same_as(123));
    EXPECT_FALSE(trip->is_same_as(456));
}

TEST_F(TripTest, IsDeleted) {
    EXPECT_FALSE(trip->is_deleted());
    trip->delete_yourself();
    EXPECT_TRUE(trip->is_deleted());
}

TEST_F(TripTest, IsStatus) {
    EXPECT_TRUE(trip->is_status(TRIP_WAITING));
    trip->start();
    EXPECT_TRUE(trip->is_status(TRIP_TRAVELING));
    trip->finish();
    EXPECT_TRUE(trip->is_status(TRIP_FINISHED));
    trip->delete_yourself();
    EXPECT_TRUE(trip->is_status(TRIP_DELETED));
}

TEST_F(TripTest, SetAndGetDriver) {
    Member* driver = new MockMember(2);
    trip->set_driver(driver);
    EXPECT_EQ(trip->get_driver(), driver);
    delete driver;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}