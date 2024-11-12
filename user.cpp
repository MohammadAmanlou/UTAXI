#include "user.hpp"

using namespace std;

User::User(std::string _username){
    username = _username;
    is_on_trip = false;
}

string User::get_username(){
    return username;
}

void User::go_on_trip(){
    is_on_trip = true;
}

bool User::is_on_trip_func(){
    if (is_on_trip)
        return true;
    return false;
}
void User::accept_a_trip(){
    is_on_trip = true;
}
void User::finish_your_trip(){
    is_on_trip = false;
}


bool User::are_you_this(string _username){
    if (username == _username)
        return true;
    return false;
}