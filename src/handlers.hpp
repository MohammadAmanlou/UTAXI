#ifndef HANDLERS_HPP
#define HANDLERS_HPP
#include "server/server.hpp"
#include "app_manager.hpp"
#include "bad_request_err.hpp"
#include "not_found_err.hpp"
#include "permission_denied_err.hpp"

class CustomRequestHandler : public RequestHandler{
public:
    CustomRequestHandler(Utaxi* _utaxi);
    virtual Response* callback(Request *) = 0;
protected:
    Utaxi* utaxi;
};

class SignupPageHandler : public CustomRequestHandler{
    using CustomRequestHandler::CustomRequestHandler;
    Response* callback(Request *);
};

class NewTripPageHandler : public CustomRequestHandler{
    using CustomRequestHandler::CustomRequestHandler;
    Response* callback(Request *);
};

class DeleteTripPageHandler : public CustomRequestHandler{
    using CustomRequestHandler::CustomRequestHandler;
    Response* callback(Request *);
};

class CalCostPageHandler : public CustomRequestHandler{
    using CustomRequestHandler::CustomRequestHandler;
    Response* callback(Request *);
};

class ShowTripsListHandler : public CustomRequestHandler{
    using CustomRequestHandler::CustomRequestHandler;
    Response* callback(Request *);
};

class AcceptTripsHandler : public CustomRequestHandler{
    using CustomRequestHandler::CustomRequestHandler;
    Response* callback(Request *);
};

class FinishTripsHandler : public CustomRequestHandler{
    using CustomRequestHandler::CustomRequestHandler;
    Response* callback(Request *);
};

#endif