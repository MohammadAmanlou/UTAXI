#ifndef _USER_hpp
#define _USER_hpp
#include <vector>
#include <string>

class User {
public:
    User(std::string _username);
    std::string get_username();
    void go_on_trip();
    bool is_on_trip_func();
    void accept_a_trip();
    void finish_your_trip();
    bool are_you_this(std::string username);
    virtual bool are_you_driver() = 0;
protected:
    std::string username;
    bool is_on_trip;
};

#endif