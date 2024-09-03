#include "Course.h"
#include "Department.h"
#include "Globals.h"
#include "MyApp.h"
#include "MyFileDatabase.h"
#include "RouteController.h"
#include "crow.h"
#include <csignal>
#include <iostream>
#include <map>
#include <string>

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
    // MyApp::run(mode);

    std::cerr << "Running on port 8080\n";
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([]() { return "Hello world"; });
    app.port(8080).run();

    // crow::SimpleApp app;
    // app.signal_clear();
    // std::signal(SIGINT, signalHandler);
    // std::signal(SIGTERM, signalHandler);

    // RouteController routeController;
    // routeController.initRoutes(app);
    // routeController.setDatabase(MyApp::getDatabase());
    // app.port(8080).multithreaded().run();
    return 0;
}
