#include "utaxi.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Utaxi::Utaxi(vector <Location*> _locations){
    locations = _locations;
    trip_counter = 0;
}

bool Utaxi::does_user_exist(string username){
    for(int i = 0; i < users.size(); i++){
        if(users[i]->are_you_this(username))
            return true;
    }
    return false;
}

bool Utaxi::does_location_exist(string location){
    for (int i = 0; i < locations.size(); i++){
        if (locations[i]->are_you_this(location))
            return true;
    }
    return false;
}

int Utaxi::find_user_by_username(string username){
    for (int i = 0; i < users.size(); i++){
        if (users[i]->are_you_this(username))
            return i;
    }
    return -1;
}

int Utaxi::find_location_by_name(string name){
    for (int i = 0; i < locations.size(); i++){
        if (locations[i]->are_you_this(name))
            return i;
    }
    return -1;
}

void Utaxi::signup(string username , string role){
    if(does_user_exist(username))
        throw BadRequest();
    if (role == PASSENGER_ROLE)
        users.push_back(new Passenger(username));
    else if (role == DRIVER_ROLE)
        users.push_back(new Driver(username));
    else
        throw BadRequest();
}

int Utaxi::new_trip(string username, string origin, string destination, string in_hurry){
    if(!does_user_exist(username) || !does_location_exist(origin) || !does_location_exist(destination))
        throw NotFound();
    if (users[find_user_by_username(username)]->is_on_trip_func())
        throw BadRequest();
    if(users[find_user_by_username(username)]->are_you_driver())
        throw PermissionDenied();
    int destination_index, origin_index;
    destination_index = find_location_by_name(destination);
    origin_index = find_location_by_name(origin);
    double cost = locations[origin_index]->calculate_cost(locations[destination_index]);
    if(in_hurry == SORT_LIST_YES)
        cost = cost * IN_HURRRY_COST;
    users[find_user_by_username(username)]->go_on_trip();
    trip_counter++;
    trips.push_back(new Trip(username, origin, destination, trip_counter, cost));
    return trip_counter;
}

bool is_expensive_than(Trip* first,Trip* second){
    return first->cost > second->cost;
}

string Utaxi::show_trip_list(string username , string sort_status){
    if(find_user_by_username(username) == -1)
        throw NotFound();
    if(!users[find_user_by_username(username)]->are_you_driver())
        throw PermissionDenied();
    if (trips.size() == 0)
        throw runtime_error(EMPTY_LIST_ERROR_MASSAGE);
    std::vector<Trip*> want_to_print_list = trips;
    string body;
    if(sort_status == SORT_LIST_YES){
        sort(want_to_print_list.begin(), want_to_print_list.end(), is_expensive_than);
    }
    for (int i = 0; i < trips.size() ; i++){
            body += want_to_print_list[i]->print_yourself();
            body += "<input type=\"hidden\" id=\"username\" name=\"username\"";
            body += "value=" + username + ">";
            body += "<button type=\"submit\" value=\"submit\">ACCEPT</button>";
            body += "</td>";
            body += "<td>";
            body += "<button type=\"submit\" value=\"submit\" formaction=\"/finish_trip\">FINISH</button>";
            body += "</td>";
            body += "</form>";
            body += "</tr>";
        }
    return body;
}

void Utaxi::delete_a_trip(string username, int id){
    if(users[find_user_by_username(username)]->are_you_driver())
        throw PermissionDenied();
    for (int i = 0; i < trips.size(); i++){
        if (trips[i]->are_you_this(id)){
            if (!trips[i]->are_you_for_this_person(username))
                throw PermissionDenied();
            if (trips[i]->are_you_finished())
                throw BadRequest();
            trips.erase(trips.begin() + i);
            users[find_user_by_username(username)]->finish_your_trip();
            return;
        }
    }
    throw NotFound();
}

void Utaxi::accept_a_trip(string username, int id){
    if(find_user_by_username(username) == -1)
        throw NotFound();
    if(!users[find_user_by_username(username)]->are_you_driver())
        throw PermissionDenied();
    if (trips.size() == 0)
        throw NotFound();
    for (int i = 0; i < trips.size(); i++){
        if (trips[i]->are_you_this(id)){
            if (trips[i]->are_you_finished())
                throw PermissionDenied();
            if (trips[i]->are_you_accepted())
                throw BadRequest();
            if(users[find_user_by_username(username)]->is_on_trip_func())
                throw BadRequest();
            trips[i]->become_accepted(username);
            users[find_user_by_username(username)]->go_on_trip();
            return;
        }
    }
    throw NotFound();
}

void Utaxi::finishe_a_trip(string username, int id){
    if(!users[find_user_by_username(username)]->are_you_driver())
        throw PermissionDenied();
    for (int i = 0; i < trips.size(); i++){
        if (trips[i]->are_you_this(id)){
            if (trips[i]->are_you_finished())
                throw BadRequest();
            trips[i]->become_finished();
            users[find_user_by_username(username)]->finish_your_trip();
            users[find_user_by_username(trips[i]->get_passenger())]->finish_your_trip();
            return;
        }
    }
    throw NotFound();
}

bool Utaxi::does_trip_exist(int id){
    for (int i = 0; i < trips.size(); i++){
        if (trips[i]->are_you_this(id))
            return true;
    }
    return false;
}

double Utaxi::calculate_cost(string passenger, string origin, string destination, string in_hurry){
    if(users[find_user_by_username(passenger)]->are_you_driver())
        throw PermissionDenied();
    if(!does_location_exist(origin) || !does_location_exist(destination))
        throw NotFound();
    int destination_index, origin_index;
    destination_index = find_location_by_name(destination);
    origin_index = find_location_by_name(origin);
    double cost;
    cost = locations[origin_index]->calculate_cost(locations[destination_index]);
    if(in_hurry == SORT_LIST_YES)
        cost = cost * IN_HURRRY_COST;
    return cost;
}