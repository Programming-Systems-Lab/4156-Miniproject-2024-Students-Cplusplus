#include <map>
#include <string>
#include <exception>
#include <iostream>
#include "RouteController.h"
#include "Globals.h"
#include "MyFileDatabase.h"
#include "../external_libraries/Crow/include/crow.h"


// Utility function to handle exceptions
crow::response handleException(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return crow::response{500, "An error has occurred"};
}

/**
 * Redirects to the homepage.
 *
 * @return A string containing the name of the html file to be loaded.
 */
void RouteController::index(Response res) {
    std::string message1 = "Welcome, in order to make an API call direct";
    std::string message2 = "your browser or Postman to an endpoint ";
    std::string message3 = "\n\n This can be done using the following format: ";
    std::string message4 = "\n\n http://127.0.0.1:8080/endpoint?arg=value";
    res.write(message1 + message2 + message3 + message4);
    res.end();
}

/**
 * Returns the details of the specified department.
 *
 * @param deptCode A {@code string} representing the department the user wishes
 *                 to retrieve.
 *
 * @return A crow::response object containing either the details of the Department and
 *         an HTTP 200 response or, an appropriate message indicating the proper response.
 */
void RouteController::retrieveDepartment(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto departmentMapping = myFileDatabase->getDepartmentMapping();

        auto it = departmentMapping.find(deptCode);
        if (it == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            res.code = 200;
            res.write(it->second.display());
            // Use dot operator to access method
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}
/**
 * Returns the string representation of all courses with the specified course code.
*/
std::string RouteController::retrieveCourses(Request req, Response res) {
    return "Hi";
}


/**
 * Displays the details of the requested course to the user or displays the proper error
 * message in response to the request.
 *
 * @param deptCode   A {@code string} representing the department the user wishes
 *                   to find the course in.
 *
 * @param courseCode A {@code int} representing the course the user wishes
 *                   to retrieve.
 *
 * @return           A crow::response object containing either the details of the
 *                   course and an HTTP 200 response or, an appropriate message indicating the
 *                   proper response.
 */
void RouteController::retrieveCourse(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt == coursesMapping.end()) {
                res.code = 404;
                res.write("Course Not Found");
            } else {
                res.code = 200;
                res.write(courseIt->second->display());
                // Use dot operator to access method
            }
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Displays whether the course has at minimum reached its enrollmentCapacity.
 *
 * @param deptCode   A {@code string} representing the department the user wishes
 *                   to find the course in.
 *
 * @param courseCode A {@code int} representing the course the user wishes
 *                   to retrieve.
 *
 * @return           A crow::response object containing either the requested information
 *                   and an HTTP 200 response or, an appropriate message indicating the proper
 *                   response.
 */
void RouteController::isCourseFull(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt == coursesMapping.end()) {
                res.code = 404;
                res.write("Course Not Found");
            } else {
                auto course = courseIt->second;
                res.code = 200;
                res.write(course->isCourseFull() ? "true" : "false");
                // Use dot operator to call method
            }
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Displays the number of majors in the specified department.
 *
 * @param deptCode     A {@code string} representing the department the user wishes
 *                     to find number of majors for.
 *
 * @return             A crow::response object containing either number of majors for the
 *                     specified department and an HTTP 200 response or, an appropriate message
 *                     indicating the proper response.
 */
void RouteController::getMajorCountFromDept(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            res.code = 200;
            auto nums = deptIt->second.getNumberOfMajors();
            std::string numMajors = std::to_string(nums);
            res.write("There are: " + numMajors + " majors in the department");
            // Use dot operator to call method
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Displays the department chair for the specified department.
 *
 * @param deptCode  A {@code string} representing the department the user wishes
 *                  to find the department chair of.
 *
 * @return          A crow::response object containing either department chair of the
 *                  specified department and an HTTP 200 response or, an appropriate message
 *                  indicating the proper response.
 */
void RouteController::identifyDeptChair(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            res.code = 200;
            std::string deptChair = deptIt->second.getDepartmentChair();
            res.write(deptChair + " is the department chair.");
            // Use dot operator to call method
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Displays the location for the specified course.
 *
 * @param deptCode   A {@code string} representing the department the user wishes
 *                   to find the course in.
 *
 * @param courseCode A {@code int} representing the course the user wishes
 *                   to find information about.
 *
 * @return           A crow::response object containing either the location of the
 *                   course and an HTTP 200 response or, an appropriate message indicating the
 *                   proper response.
 */
void RouteController::findCourseLocation(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt == coursesMapping.end()) {
                res.code = 404;
                res.write("Course Not Found");
            } else {
                auto course = courseIt->second;
                res.code = 200;
                std::string courseLocation = course->getCourseLocation();
                res.write(courseLocation + " is where the course is located.");
                // Use dot operator to call method
            }
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Displays the instructor for the specified course.
 *
 * @param deptCode   A {@code string} representing the department the user wishes
 *                   to find the course in.
 *
 * @param courseCode A {@code int} representing the course the user wishes
 *                   to find information about.
 *
 * @return           A crow::response object containing either the course instructor and
 *                   an HTTP 200 response or, an appropriate message indicating the proper
 *                   response.
 */
void RouteController::findCourseInstructor(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt == coursesMapping.end()) {
                res.code = 404;
                res.write("Course Not Found");
            } else {
                auto course = courseIt->second;
                res.code = 200;
                std::string instructor = course->getInstructorName();
                res.write(instructor + " is the instructor for the course.");
                // Use dot operator to call method
            }
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Displays the time the course meets at for the specified course.
 *
 * @param deptCode   A {@code String} representing the department the user wishes
 *                   to find the course in.
 *
 * @param courseCode A {@code int} representing the course the user wishes
 *                   to find information about.
 *
 * @return           A crow::response object containing either the details of the
 *                   course timeslot and an HTTP 200 response or, an appropriate message
 *                   indicating the proper response.
 */
void RouteController::findCourseTime(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt == coursesMapping.end()) {
                res.code = 404;
                res.write("Course Not Found");
            } else {
                auto course = courseIt->second;
                res.code = 200;
                std::string timeSlot = course->getCourseTimeSlot();
                res.write("The course meets at: " + timeSlot);
            }
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Attempts to add a student to the specified department.
 *
 * @param deptCode       A {@code String} representing the department.
 *
 * @return               A crow::response object containing an HTTP 200
 *                       response with an appropriate message or the proper status
 *                       code in tune with what has happened.
 */
void RouteController::addMajorToDept(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            deptIt->second.addPersonToMajor();
            // Use dot operator to call method
            res.code = 200;
            res.write("Attribute was updated successfully");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

// Set Enrollment Count
void RouteController::setEnrollmentCount(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));
        auto count = std::stoi(req.url_params.get("count"));

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt != departmentMapping.end()) {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt != coursesMapping.end()) {
                courseIt->second->setEnrolledStudentCount(count);
                res.code = 200;
                res.write("Attribute was updated successfully.");
            } else {
                res.code = 404;
                res.write("Course Not Found");
            }
        } else {
            res.code = 404;
            res.write("Department Not Found");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

// Set Course Location
void RouteController::setCourseLocation(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));
        auto location = req.url_params.get("location");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt != departmentMapping.end()) {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt != coursesMapping.end()) {
                courseIt->second->reassignLocation(location);
                res.code = 200;
                res.write("Attribute was updated successfully.");
            } else {
                res.code = 404;
                res.write("Course Not Found");
            }
        } else {
            res.code = 404;
            res.write("Department Not Found");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::setCourseInstructor(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCodeStr = req.url_params.get("courseCode");
        auto instructor = req.url_params.get("instructor");

        int courseCode = std::stoi(courseCodeStr);
        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt != departmentMapping.end()) {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt != coursesMapping.end()) {
                courseIt->second->reassignInstructor(instructor);
                res.code = 200;
                res.write("Attribute was updated successfully.");
            } else {
                res.code = 404;
                res.write("Course Not Found");
            }
        } else {
            res.code = 404;
            res.write("Department Not Found");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

// Set Course Time
void RouteController::setCourseTime(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));
        auto time = req.url_params.get("time");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt != departmentMapping.end()) {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt != coursesMapping.end()) {
                courseIt->second->reassignTime(time);
                res.code = 200;
                res.write("Attribute was updated successfully.");
            } else {
                res.code = 404;
                res.write("Course Not Found");
            }
        } else {
            res.code = 404;
            res.write("Department Not Found");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}


/**
 * Attempts to remove a student from the specified department.
 *
 * @param deptCode       A {@code String} representing the department.
 *
 * @return               A crow::response object containing an HTTP 200
 *                       response with an appropriate message or the proper status
 *                       code in tune with what has happened.
 */
void RouteController::removeMajorFromDept(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            deptIt->second.dropPersonFromMajor();
            res.code = 200;
            res.write("Attribute was updated successfully");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

/**
 * Attempts to remove a student from the specified department.
 *
 * @param deptCode       A {@code String} representing the department.
 * 
 * @param courseCode     A {@code int} representing the course the user wishes
 *                       to find information about.
 *
 * @return               A crow::response object containing an HTTP 200
 *                       response with an appropriate message or the proper status
 *                       code in tune with what has happened.
 */
void RouteController::dropStudentFromCourse(Request req, Response res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto courseCode = std::stoi(req.url_params.get("courseCode"));

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            auto coursesMapping = deptIt->second.getCourseSelection();
            auto courseIt = coursesMapping.find(std::to_string(courseCode));

            if (courseIt == coursesMapping.end()) {
                res.code = 404;
                res.write("Course Not Found");
            } else {
                bool isStudentDropped = courseIt->second->dropStudent();
                if (isStudentDropped) {
                    res.code = 200;
                    res.write("Student has been dropped");
                } else {
                    res.code = 400;
                    res.write("Student has not been dropped");
                }
            }
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

// Initialize API Routes
void RouteController::initRoutes(App app) {
    CROW_ROUTE(app, "/")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            index(res);
        });

    CROW_ROUTE(app, "/retrieveDept")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            retrieveDepartment(req, res);
        });

    CROW_ROUTE(app, "/retrieveCourse")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            retrieveCourse(req, res);
        });

    CROW_ROUTE(app, "/isCourseFull")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            isCourseFull(req, res);
        });

    CROW_ROUTE(app, "/getMajorCountFromDept")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            getMajorCountFromDept(req, res);
        });

    CROW_ROUTE(app, "/idDeptChair")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            identifyDeptChair(req, res);
        });

    CROW_ROUTE(app, "/findCourseLocation")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            findCourseLocation(req, res);
        });

    CROW_ROUTE(app, "/findCourseInstructor")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            findCourseInstructor(req, res);
        });

    CROW_ROUTE(app, "/findCourseTime")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            findCourseTime(req, res);
        });

    CROW_ROUTE(app, "/addMajorToDept")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            addMajorToDept(req, res);
        });

    CROW_ROUTE(app, "/removeMajorFromDept")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            removeMajorFromDept(req, res);
        });

    CROW_ROUTE(app, "/changeCourseLocation")
        .methods(crow::HTTPMethod::PATCH)([this](Request req, Response res) {
            setCourseLocation(req, res);
        });

    CROW_ROUTE(app, "/changeCourseTeacher")
        .methods(crow::HTTPMethod::PATCH)([this](Request req, Response res) {
            setCourseInstructor(req, res);
        });

    CROW_ROUTE(app, "/changeCourseTime")
        .methods(crow::HTTPMethod::PATCH)([this](Request req, Response res) {
            setCourseTime(req, res);
        });

    CROW_ROUTE(app, "/setEnrollmentCount")
        .methods(crow::HTTPMethod::PATCH)([this](Request req, Response res) {
            setEnrollmentCount(req, res);
        });
    CROW_ROUTE(app, "/retrieveCourses")
        .methods(crow::HTTPMethod::GET)([this](Request req, Response res) {
            retrieveCourses(req, res);
        });
}

void RouteController::setDatabase(MyFileDatabase *db) {
    myFileDatabase = db;
}
