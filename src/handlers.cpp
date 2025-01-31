#include "handlers.hpp"
#include <iostream>
#include <fstream>
using namespace std;

CustomRequestHandler::CustomRequestHandler(Utaxi* _utaxi){
    utaxi = _utaxi;
}

Response* SignupPageHandler::callback(Request* request){
    try{
        utaxi->signup(request->getBodyParam("username"), request->getBodyParam("role"));
        Response* res = Response::redirect("/");
	    return res;
    }
    catch(BadRequest& exception){
        Response* res = Response::redirect("/bad_request");
        return res;
    }
    catch(NotFound& exception){
        Response* res = Response::redirect("/not_found");
        return res;
    }
    catch(PermissionDenied& exception){
        Response* res = Response::redirect("/permission_denied");
        return res;
    }
}

Response* NewTripPageHandler::callback(Request* request){
    try{
    int id = utaxi->new_trip(request->getBodyParam("username"), request->getBodyParam("origin"), 
        request->getBodyParam("destination"), request->getBodyParam("in_hurry"));
    Response* response = new Response;
	response->setHeader("Content-Type", "text/html");
    string head;
    string body;
    string html;
    head = "<head>";
    head += "<link rel=\"stylesheet\" href=\"common.css\">";
    head += "<style>";
    head += "body {";
    head += "background-color: rgb(196, 196, 23)";
    head += "}";
    head += "</style>";
	head += "<title>SHOW_TRIP_ID &#9992</title>";
	head += "</head>";

    body += "<body>";
    body += "<h2> YOUR TRIP ID IS : </h2>";
    body += to_string(id);
    body += "<br>";
    body += "<br>";
    body += "<a  href=\"/\">HOME</a>";
    body += "<br>";
    body += "</body>";
    html = "<!DOCTYPE html>";
    html += "<html lang=\"en\">" + head + body + "</html>";
	response->setBody(html);
	return response;
    }
    catch(BadRequest& exception){
        Response* res = Response::redirect("/bad_request");
        return res;
    }
    catch(NotFound& exception){
        Response* res = Response::redirect("/not_found");
        return res;
    }
    catch(PermissionDenied& exception){
        Response* res = Response::redirect("/permission_denied");
        return res;
    }
}

Response* DeleteTripPageHandler::callback(Request* request){
    try{
    int id = stoi(request->getBodyParam("id"));
    string username = request->getBodyParam("username");
    utaxi->delete_a_trip(username, id);
    Response* res = Response::redirect("/");
	return res;
    }
    catch(BadRequest& exception){
        Response* res = Response::redirect("/bad_request");
        return res;
    }
    catch(NotFound& exception){
        Response* res = Response::redirect("/not_found");
        return res;
    }
    catch(PermissionDenied& exception){
        Response* res = Response::redirect("/permission_denied");
        return res;
    }
}

Response* CalCostPageHandler::callback(Request* request){
    try{
    double cost = utaxi->calculate_cost(request->getBodyParam("username"), request->getBodyParam("origin"), 
        request->getBodyParam("destination"), request->getBodyParam("in_hurry"));
    Response* response = new Response;
	response->setHeader("Content-Type", "text/html");
    string head;
    string body;
    string html;
    head = "<head>";
	head += "<title>SHOW_TRIP_COST &#9992</title>";
    head += "<link rel=\"stylesheet\" href=\"common.css\">";
    head += "<style>";
    head += "body {";
    head += "background-color: rgb(196, 196, 23)";
    head += "}";
    head += "</style>";
	head += "</head>";

    body += "<body>";
    body += "<h1> YOUR TRIP COST </h1>";
    body += to_string(cost);
    body += "<br>";
    body += "<br>";
    body += "<a  href=\"/new_trip\">NEW TRIP</a>";
    body += "<br>";
    body += "</body>";
    html = "<!DOCTYPE html>";
    html += "<html lang=\"en\">" + head + body + "</html>";
	response->setBody(html);
	return response;
    }
    catch(BadRequest& exception){
        Response* res = Response::redirect("/bad_request");
        return res;
    }
    catch(NotFound& exception){
        Response* res = Response::redirect("/not_found");
        return res;
    }
    catch(PermissionDenied& exception){
        Response* res = Response::redirect("/permission_denied");
        return res;
    }
}

Response* ShowTripsListHandler::callback(Request* request){
    try{
        Response* response = new Response;
	    response->setHeader("Content-Type", "text/html");
        string head;
        string body;
        string html;

        head = "<head>";
	    head += "<title>SHOW_TRIP_COST &#9992</title>";
        head += "<link rel=\"stylesheet\" href=\"common.css\">";
        head += "<style>";
        head += "body {";
        head += "background-color: rgb(196, 196, 23)";
        head += "}";
        head += "</style>";
	    head += "</head>";

        body += "<table style=\"width:100%\">";
        body += "<tr>";
        body += "<th> ID </th>";
        body += "<th> PASSENGER </th>";
        body += "<th> ORIGIN </th>";
        body += "<th> DESTINATION </th>";
        body += "<th> COST </th>";
        body += "<th> STATUS </th>";
        body += "<th> ACCESPT </th>";
        body += "<th> FINISH </th>";
        body += "</tr>";
        body += utaxi->show_trip_list(request->getBodyParam("username"), request->getBodyParam("sorted"));
        body += "</table>";
        body += "</body>";
        html = "<!DOCTYPE html>";
        html += "<html lang=\"en\">" + head + body + "</html>";
	    response->setBody(html);
	    return response;
    }
    catch(BadRequest& exception){
        Response* res = Response::redirect("/bad_request");
        return res;
    }
    catch(NotFound& exception){
        Response* res = Response::redirect("/not_found");
        return res;
    }
    catch(PermissionDenied& exception){
        Response* res = Response::redirect("/permission_denied");
        return res;
    }
    catch(runtime_error& exception){
        Response* res = Response::redirect("/empty");
        return res;
    }
}

Response* AcceptTripsHandler::callback(Request* request){
    try{
        utaxi->accept_a_trip(request->getBodyParam("username"), stoi(request->getBodyParam("id")));
        Response* res = Response::redirect("/");
    	return res;
    }
    catch(BadRequest& exception){
        Response* res = Response::redirect("/bad_request");
        return res;
    }
    catch(NotFound& exception){
        Response* res = Response::redirect("/not_found");
        return res;
    }
    catch(PermissionDenied& exception){
        Response* res = Response::redirect("/permission_denied");
        return res;
    }
}

Response* FinishTripsHandler::callback(Request* request){
    try{
        utaxi->finishe_a_trip(request->getBodyParam("username"), stoi(request->getBodyParam("id")));
        Response* res = Response::redirect("/");
	    return res;
    }
    catch(BadRequest& exception){
        Response* res = Response::redirect("/bad_request");
        return res;
    }
    catch(NotFound& exception){
        Response* res = Response::redirect("/not_found");
        return res;
    }
    catch(PermissionDenied& exception){
        Response* res = Response::redirect("/permission_denied");
        return res;
    }
}