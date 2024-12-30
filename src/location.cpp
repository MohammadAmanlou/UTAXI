#include "location.hpp"
#include <math.h>
#include <iostream>
using namespace std;

Location::Location (string _name, double _latitude, double _longitude, int _traffic){
    name = _name;
    latitude = _latitude;
    longitude = _longitude;
    traffic = _traffic;
}

bool Location::are_you_this(string _name){
    if (name == _name)
        return true;
    return false;
}

double Location::calculate_cost(Location* destination){
    double cost;
    double distance;
    distance = MAP_TO_REAL_DISTANCE * (sqrt(pow(destination->latitude - latitude, 2) +
             pow(destination->longitude - longitude, 2)));
    cost = distance * ((traffic + destination->traffic) * EXCHANGE_MONEY);
    return cost;
}