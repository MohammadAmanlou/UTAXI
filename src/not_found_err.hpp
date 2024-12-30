#ifndef NOT_FOUND_ERR
#define NOT_FOUND_ERR

#include <string>
#include "define.hpp"

class NotFound{
public:
    NotFound();
    std::string get_message();
private:
    std::string message;
};

#endif