#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <vector>
#include <string>
#include "define.hpp"
class Location {

public:
    Location(std::string _name, double _latitude, double _longitude, int _traffic);
    double calculate_cost(Location* destination);
    bool are_you_this(std::string _name);
private:
    std::string name;
    double latitude;
    double longitude;
    int traffic;
};



#endif