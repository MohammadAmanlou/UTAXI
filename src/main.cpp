#include "app_manager.hpp"
#include <iomanip>
#include <iostream>
#include "server/server.hpp"
#include "handlers.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    try{
        Server server(5000);
        AppManager app_manger(argv[1]);
        Utaxi* utaxi = app_manger.return_utaxi();
        server.get("/common.css", new ShowPage("static/common.css"));
        server.get("/home_bkg.jpg", new ShowPage("static/home_bkg.jpg"));
        server.get("/signup.jpg", new ShowPage("static/signup/signup.jpg"));
        server.get("/passenger-driver-form.jpg", new ShowPage("static/passenger-driver-form.jpg"));

        server.get("/", new ShowPage("static/home.html"));

        server.get("/signup", new ShowPage("static/signup/signup.html"));
        server.post("/signup", new SignupPageHandler(utaxi));

        server.get("/new_trip", new ShowPage("static/new_trip.html"));
        server.post("/new_trip", new NewTripPageHandler(utaxi));

        server.post("/trip_cost", new CalCostPageHandler(utaxi));

        server.get("/delete_trip", new ShowPage("static/delete_trip.html"));
        server.post("/delete_trip", new DeleteTripPageHandler(utaxi));

        server.get("/passenger", new ShowPage("static/passenger.html"));
        server.get("/driver", new ShowPage("static/driver.html"));

        server.get("/show_trip_list_stc", new ShowPage("static/show_trip_list.html"));
        server.post("/show_trip_list", new ShowTripsListHandler(utaxi));

        server.post("/accept_trip", new AcceptTripsHandler(utaxi));
        server.post("/finish_trip", new FinishTripsHandler(utaxi));

        server.get("/bad_request", new ShowPage("static/error/bad_request.html"));
        server.get("/not_found", new ShowPage("static/error/not_found.html"));
        server.get("/permission_denied", new ShowPage("static/error/permission_denied.html"));
        server.get("/empty", new ShowPage("static/error/empty.html"));

        server.run();
    }
    catch (Server::Exception e){
        cerr << e.getMessage() << endl;
    }
}