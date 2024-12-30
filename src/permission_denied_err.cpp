#include "permission_denied_err.hpp"

using namespace std;

PermissionDenied::PermissionDenied(){
    message = WRONG_ROLE_ERROR_MASSAGE;
}

string PermissionDenied::get_message(){
    return message;
}