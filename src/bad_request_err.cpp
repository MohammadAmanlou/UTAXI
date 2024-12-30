#include "bad_request_err.hpp"

using namespace std;

BadRequest::BadRequest(){
    message = BAD_REQUEST_ERROR_MASSAGE;
}

string BadRequest::get_message(){
    return message;
}