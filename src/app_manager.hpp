#ifndef _APP_MANAGER_hpp
#define _APP_MANAGER_hpp

#include <string>
#include <vector>
#include "utaxi.hpp"
#include <fstream>

class AppManager {
public:
    AppManager(std::string _location);
    std::vector<Location*> read_locations_names();
    Utaxi* return_utaxi();
    std::vector<std::string> parse_line(std::string line, std::string delimiter);
private:
    Utaxi *utaxi;
    std::string location;
    std::vector<std::string> line_parsed;
};

#endif