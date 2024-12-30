#ifndef _Utaxi_hpp
#define _Utaxi_hpp
#include <vector>
#include <string>
#include "user.hpp"
#include "driver.hpp"
#include "passenger.hpp"
#include "define.hpp"
#include "trip.hpp"
#include "location.hpp"
#include <algorithm>
#include "bad_request_err.hpp"
#include "permission_denied_err.hpp"
#include "not_found_err.hpp"

class Utaxi {
public:
    Utaxi(std::vector <Location*> locations);
    void signup(std::string username , std::string role);
    int new_trip(std::string passenger,std::string origin, std::string destination, std::string in_hurry);
    bool does_user_exist(std::string username);
    bool does_location_exist(std::string location);
    bool does_trip_exist(int id);
    std::string show_trip_list(std::string username, std::string sort_status);
    int find_user_by_username(std::string username);
    int find_location_by_name(std::string name);
    void delete_a_trip(std::string username , int id);
    void accept_a_trip(std::string username , int id);
    void finishe_a_trip(std::string username , int id);
    double calculate_cost(std::string passenger,std::string origin, std::string destination, std::string in_hurry);
    bool sorter(Trip* first, Trip* second);
private:
    std::vector <Location*> locations;
    std::vector <User*> users;
    std::vector<Trip*> trips;
    int trip_counter;
};


#endif