#include "app_manager.hpp"
#include "utaxi.hpp"
#include <iostream>
#include <string>

using namespace std;

AppManager::AppManager(string _location){
    location = _location;
    utaxi = new Utaxi(read_locations_names());
}

vector<Location*> AppManager::read_locations_names(){
    ifstream input_file;
    vector<string> line_parsed_input;
    vector<Location*> locations;
    input_file.open(location);
    string line;
    getline(input_file, line);
    while (getline(input_file, line)){
       line_parsed_input = parse_line(line , COMMA_DELIMITER);
       locations.push_back(new Location(line_parsed_input[0], 
        stod(line_parsed_input[1]), stod(line_parsed_input[2]), stoi(line_parsed_input[3])));
    }
    return locations;
}

vector<string> AppManager::parse_line(string line, string delimiter){
    vector<string> tokens;
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != string::npos){
        tokens.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    tokens.push_back(line.substr(0, pos));
    return tokens;
}

Utaxi* AppManager::return_utaxi(){
    return utaxi;
}