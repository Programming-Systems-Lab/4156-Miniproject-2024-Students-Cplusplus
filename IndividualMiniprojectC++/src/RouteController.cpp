// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <map>
#include <string>
#include <exception>
#include <iostream>

#include "RouteController.h"
#include "Globals.h"
#include "MyFileDatabase.h"

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
void RouteController::index(crow::response& res) {
    res.write("Welcome, in order to make an API call direct your browser or Postman to an endpoint "
              "\n\n This can be done using the following format: \n\n http://127.0.0.1:8080/endpoint?arg=value");
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
void RouteController::retrieveDepartment(const crow::request& req, crow::response& res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto departmentMapping = myFileDatabase->getDepartmentMapping();

        auto it = departmentMapping.find(deptCode);
        if (it == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            res.code = 200;
            res.write(it->second.display()); // Use dot operator to access method
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
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
void RouteController::retrieveCourse(const crow::request& req, crow::response& res) {
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
                res.write(courseIt->second->display()); // Use dot operator to access method
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
void RouteController::isCourseFull(const crow::request& req, crow::response& res) {
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
                res.write(course->isCourseFull() ? "true" : "false"); // Use dot operator to call method
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
void RouteController::getMajorCountFromDept(const crow::request& req, crow::response& res) {
    try {
        auto deptCode = req.url_params.get("deptCode");
        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            res.code = 200;
            res.write("There are: " + std::to_string(deptIt->second.getNumberOfMajors()) + " majors in the department"); // Use dot operator to call method
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
void RouteController::identifyDeptChair(const crow::request& req, crow::response& res) {
    try {
        auto deptCode = req.url_params.get("deptCode");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            res.code = 200;
            res.write(deptIt->second.getDepartmentChair() + " is the department chair."); // Use dot operator to call method
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
void RouteController::findCourseLocation(const crow::request& req, crow::response& res) {
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
                res.write(course->getCourseLocation() + " is where the course is located."); // Use dot operator to call method
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
void RouteController::findCourseInstructor(const crow::request& req, crow::response& res) {
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
                res.write(course->getInstructorName() + " is the instructor for the course."); // Use dot operator to call method
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
void RouteController::findCourseTime(const crow::request& req, crow::response& res) {
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
                res.write("The course meets at: " + course->getCourseTimeSlot()); 
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
void RouteController::addMajorToDept(const crow::request& req, crow::response& res) {
    try {
        auto deptCode = req.url_params.get("deptCode");

        auto departmentMapping = myFileDatabase->getDepartmentMapping();
        auto deptIt = departmentMapping.find(deptCode);

        if (deptIt == departmentMapping.end()) {
            res.code = 404;
            res.write("Department Not Found");
        } else {
            deptIt->second.addPersonToMajor(); // Use dot operator to call method
            res.code = 200;
            res.write("Attribute was updated successfully");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

// Set Enrollment Count
void RouteController::setEnrollmentCount(const crow::request& req, crow::response& res) {
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
void RouteController::setCourseLocation(const crow::request& req, crow::response& res) {
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

void RouteController::setCourseInstructor(const crow::request& req, crow::response& res) {
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
void RouteController::setCourseTime(const crow::request& req, crow::response& res) {
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
void RouteController::removeMajorFromDept(const crow::request& req, crow::response& res) {
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
void RouteController::dropStudentFromCourse(const crow::request& req, crow::response& res) {
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
void RouteController::initRoutes(crow::App<>& app) {
    CROW_ROUTE(app, "/")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            index(res);
        });

    CROW_ROUTE(app, "/retrieveDept")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            retrieveDepartment(req, res);
        });

    CROW_ROUTE(app, "/retrieveCourse")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            retrieveCourse(req, res);
        });

    CROW_ROUTE(app, "/isCourseFull")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            isCourseFull(req, res);
        });

    CROW_ROUTE(app, "/getMajorCountFromDept")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            getMajorCountFromDept(req, res);
        });

    CROW_ROUTE(app, "/idDeptChair")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            identifyDeptChair(req, res);
        });

    CROW_ROUTE(app, "/findCourseLocation")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            findCourseLocation(req, res);
        });

    CROW_ROUTE(app, "/findCourseInstructor")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            findCourseInstructor(req, res);
        });

    CROW_ROUTE(app, "/findCourseTime")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            findCourseTime(req, res);
        });

    CROW_ROUTE(app, "/addMajorToDept")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            addMajorToDept(req, res);
        });

    CROW_ROUTE(app, "/removeMajorFromDept")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            removeMajorFromDept(req, res);
        });

    CROW_ROUTE(app, "/changeCourseLocation")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            setCourseLocation(req, res);
        });

    CROW_ROUTE(app, "/changeCourseTeacher")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            setCourseInstructor(req, res);
        });

    CROW_ROUTE(app, "/changeCourseTime")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            setCourseTime(req, res);
        });

    CROW_ROUTE(app, "/setEnrollmentCount")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            setEnrollmentCount(req, res);
        });
}

void RouteController::setDatabase(MyFileDatabase *db) {
    myFileDatabase = db;
}
