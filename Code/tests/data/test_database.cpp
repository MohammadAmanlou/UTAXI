#include "gtest/gtest.h"
#include "database.hpp"
#include "location.hpp"
#include "driver.hpp"
#include "passenger.hpp"
#include "trip.hpp"
#include <vector>
#include <string>
#include <stdexcept>

class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        db = new Database();
        driver = new Driver("driver1");
        passenger = new Passenger("passenger1");
        location1 = new Location("loc1");
        location2 = new Location("loc2");
    }

    void TearDown() override {
        delete db;
        delete driver;
        delete passenger;
        delete location1;
        delete location2;
    }

    Database* db;
    Driver* driver;
    Passenger* passenger;
    Location* location1;
    Location* location2;
};

TEST_F(DatabaseTest, AddMemberAddsDriver) {
    SignupCredentials creds = {"driver1", DRIVER_ROLE};
    db->add_member(creds);
    EXPECT_EQ(db->find_member_index("driver1"), 0);
}

TEST_F(DatabaseTest, AddMemberAddsPassenger) {
    SignupCredentials creds = {"passenger1", PASSENGER_ROLE};
    db->add_member(creds);
    EXPECT_EQ(db->find_member_index("passenger1"), 0);
}

TEST_F(DatabaseTest, AddLocationAddsLocation) {
    db->add_location(location1);
    EXPECT_EQ(db->find_location_index("loc1"), 0);
}

TEST_F(DatabaseTest, AddTripAddsTrip) {
    db->add_member({"passenger1", PASSENGER_ROLE});
    db->add_location(location1);
    db->add_location(location2);
    TripRequestTokens tokens = {"passenger1", "loc1", "loc2", "1", NO_HURRY};
    db->add_trip(tokens);
    EXPECT_EQ(db->find_trip_index(1), 0);
}

TEST_F(DatabaseTest, CalcTripCostReturnsCorrectCost) {
    db->add_member({"passenger1", PASSENGER_ROLE});
    db->add_location(location1);
    db->add_location(location2);
    TripRequestTokens tokens = {"passenger1", "loc1", "loc2", "1", NO_HURRY};
    double cost = db->calc_trip_cost(tokens);
    EXPECT_GT(cost, 0);
}

TEST_F(DatabaseTest, GetTripsReturnsUnsortedTrips) {
    db->add_member({"passenger1", PASSENGER_ROLE});
    db->add_location(location1);
    db->add_location(location2);
    TripRequestTokens tokens = {"passenger1", "loc1", "loc2", "1", NO_HURRY};
    db->add_trip(tokens);
    std::vector<Trip*> trips = db->get_trips(NO_HURRY);
    EXPECT_EQ(trips.size(), 1);
}

TEST_F(DatabaseTest, GetCostSortedTripsReturnsSortedTrips) {
    db->add_member({"passenger1", PASSENGER_ROLE});
    db->add_location(location1);
    db->add_location(location2);
    TripRequestTokens tokens1 = {"passenger1", "loc1", "loc2", "1", NO_HURRY};
    TripRequestTokens tokens2 = {"passenger1", "loc1", "loc2", "2", NO_HURRY};
    db->add_trip(tokens1);
    db->add_trip(tokens2);
    std::vector<Trip*> trips = db->get_cost_sorted_trips();
    EXPECT_GE(trips[0]->get_price(), trips[1]->get_price());
}

TEST_F(DatabaseTest, CheckMemberIsAvailableThrowsWhenMemberNotFound) {
    EXPECT_THROW(db->check_member_is_available("nonexistent"), std::runtime_error);
}

TEST_F(DatabaseTest, CheckLocationIsAvailableThrowsWhenLocationNotFound) {
    EXPECT_THROW(db->check_location_is_available("nonexistent"), std::runtime_error);
}

TEST_F(DatabaseTest, CheckTripIsAvailableThrowsWhenTripNotFound) {
    EXPECT_THROW(db->check_trip_is_available(999), std::runtime_error);
}

TEST_F(DatabaseTest, CheckIsPassengerThrowsWhenMemberIsNotPassenger) {
    db->add_member({"driver1", DRIVER_ROLE});
    EXPECT_THROW(db->check_is_passenger("driver1"), std::runtime_error);
}

TEST_F(DatabaseTest, CheckIsDriverThrowsWhenMemberIsNotDriver) {
    db->add_member({"passenger1", PASSENGER_ROLE});
    EXPECT_THROW(db->check_is_driver("passenger1"), std::runtime_error);
}