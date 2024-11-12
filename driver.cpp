#include "driver.hpp"

using namespace std;

Driver::Driver(string _username)
        : User (_username){}

bool Driver::are_you_driver(){
        return true;
}