#include "passenger.hpp"

using namespace std;

Passenger::Passenger(string _username) :
             User(_username){}

bool Passenger::are_you_driver(){
    return false;
}