#ifndef _DRIVER_hpp
#define _DRIVER_hpp
#include "user.hpp"



class Driver : public User {
public:
    Driver(std::string _username);
    virtual bool are_you_driver();
private:
};
#endif