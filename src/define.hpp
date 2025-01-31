#ifndef DEFINE_HPP
#define DEFINE_HPP
#include <string>

const std::string SPACE_DELIMITER = " ";
const std::string COMMA_DELIMITER = ",";
const std::string POST_COMMEND_TYPE = "POST";
const std::string DELETE_COMMEND_TYPE = "DELETE";
const std::string GET_COMMEND_TYPE = "GET";
const std::string PASSENGER_ROLE = "passenger";
const std::string DRIVER_ROLE = "driver";
const std::string SIGNUP_COMMEND = "signup";
const std::string ASK_TRIP_COMMAND = "trips";
const std::string WRONG_ROLE_ERROR_MASSAGE = "Permission Denied";
const std::string WRONG_ACCESSIBILITY_ERROR_MASSAGE = "Permission Denied";
const std::string TRIPS_LIST_COMMAND = "trips";
const std::string TRIPS_DELETE_COMMAND = "trips";
const std::string ACCEPT_A_TRIP_COMMAND = "accept";
const std::string FINISH_TRIP_COMMAND = "finish";
const std::string USERNAME_ARGUMENT = "username";
const std::string ID_ARGUMENT = "id";
const std::string ORIGINE_ARGUMENT = "origin";
const std::string DESTINATION_ARGUMENT = "destination";
const std::string SORT_STATUS_ARGUMENT = "sort_by_cost";
const std::string IN_HURRY_ARGUMENT = "in_hurry";
const std::string ROLE_ARGUMENT = "role";
const std::string EMPTY_LIST_ERROR_MASSAGE = "EMPTY";
const std::string BAD_REQUEST_ERROR_MASSAGE = "Bad Request";
const std::string NOT_FOUND_ERROR_MASSAGE = "Not Found";
const std::string SUCCESSFUL_COMMAND = "OK";
const std::string WAITING_STATUS = "waiting";
const std::string TRAVELING_STATUS = "traveling";
const std::string FINISHED_STATUS = "finished";
const std::string SORT_LIST_YES = "yes";
const int TYPE_OF_COMMAND_INDEX = 0;
const int COMMAND_INDEX = 1;
const double IN_HURRRY_COST = 1.2;
const double MAP_TO_REAL_DISTANCE = 110.5;
const int EXCHANGE_MONEY = 10000;
#endif