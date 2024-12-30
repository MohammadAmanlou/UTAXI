#include "trip.hpp"
#include <iostream>
using namespace std;
Trip::Trip(string _passenger , string _origin , string _destination , int _id, double _cost){
    
    passenger = _passenger;
    origin = _origin;
    destination = _destination;
    id = _id;
    status = Wating;
    cost = _cost;
    is_deleted = false;
}

string Trip::print_yourself(){
    string body;
    body += "<tr>";
    body += "<td>" + to_string(id) + "</td>";
    body += "<td>" + passenger + "</td>";
    body += "<td>" + origin + "</td>";
    body += "<td>" + destination + "</td>";
    body += "<td>" + to_string(cost) + "</td>";
        if (status == Wating)
            body += "<td>" + WAITING_STATUS + "</td>";
        else if (status == Traveling)
            body += "<td>" + TRAVELING_STATUS + "</td>";
        else if (status == Finished)
            body += "<td>" + FINISHED_STATUS + "</td>";
        body += "<td>";
        body += "<form action=\"/accept_trip\"  method=\"post\">";
        body += "<input type=\"hidden\" id=\"id\" name=\"id\"";
        body += "value=" + to_string(id) + ">";
    return body;
}

bool Trip::are_you_finished(){
    if (status == Finished)
        return true;
    return false;
}

bool Trip::are_you_for_this_person(string username){
    if (passenger == username)
        return true;
    return false;
}

void Trip::become_accepted(string _driver){
    driver = _driver;
    status = Traveling;
}

void Trip::become_finished(){
    status = Finished;
}

string Trip::get_passenger(){
    return passenger;
}

bool Trip::are_you_accepted(){
    if(status == Traveling)
        return true;
    return false;
}

bool Trip::are_you_this(int _id){
    if(id == _id)
        return true;
    return false;
}