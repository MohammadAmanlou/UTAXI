#include "not_found_err.hpp"

using namespace std;

NotFound::NotFound(){
    message = NOT_FOUND_ERROR_MASSAGE;
}

string NotFound::get_message(){
    return message;
}