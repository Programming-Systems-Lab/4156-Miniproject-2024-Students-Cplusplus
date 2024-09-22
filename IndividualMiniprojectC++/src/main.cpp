// Copyright 2024 vcm2114
#include <iostream>
#include <map>
#include <string>
#include <csignal>
#include "../external_libraries/Crow-1.2.0/include/crow.h"
#include "Course.h"
#include "Department.h"
#include "MyFileDatabase.h"
#include "RouteController.h"
#include "Globals.h"
#include "MyApp.h"

/**
 *  Method to handle proper termination protocols 
 */
void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        MyApp::onTermination();
        std::exit(signal);
    }
}

/**
 *  Sets up the HTTP server and runs the program 
 */
int main(int argc, char* argv[]) {
    std::string mode = argc > 1 ? argv[1] : "run";
    MyApp::run(mode);

    crow::SimpleApp app;
    app.signal_clear();
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    RouteController routeController;
    routeController.initRoutes(app);
    routeController.setDatabase(MyApp::getDatabase());
    app.port(8080).multithreaded().run();
    return 0;
}
