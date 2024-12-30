#ifndef BAD_REQUEST_ERR
#define BAD_REQUEST_ERR

#include <string>
#include "define.hpp"

class BadRequest{
public:
    BadRequest();
    std::string get_message();
private:
    std::string message;
};



#endif