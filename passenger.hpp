#ifndef _PASSANGER_hpp
#define _PASSANGER_hpp
#include "user.hpp"

class Passenger : public User {
public:
    Passenger(std::string _username);
    virtual bool are_you_driver();
private:
};
#endif