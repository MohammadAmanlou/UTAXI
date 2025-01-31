#include <string>
#include "define.hpp"

enum Status {
    Wating,
    Traveling,
    Finished
};

class Trip {
public:
    Trip(std::string _passenger , std::string _origin , std::string _destination , int id, double _cost);
    std::string print_yourself();
    bool are_you_for_this_person(std::string username);
    bool are_you_finished();
    bool are_you_accepted();
    void become_accepted(std::string _driver);
    void become_finished();
    friend bool is_expensive_than(Trip* first,Trip* second);
    bool are_you_this(int _id);
    std::string get_passenger();
private:
    std::string passenger;
    std::string driver;
    std::string origin;
    std::string destination;
    int id;
    double cost;
    Status status;
    bool is_deleted;
};