#ifndef PERMISSION_DENIED_ERR
#define PERMISSION_DENIED_ERR

#include <string>
#include "define.hpp"

class PermissionDenied{
public:
    PermissionDenied();
    std::string get_message();
private:
    std::string message;
};

#endif