// Copyright 2024 Jason Han
#ifndef ROUTECONTROLLER_H
#define ROUTECONTROLLER_H

#include "Globals.h"
#include "MyFileDatabase.h"
#include "crow.h"

class RouteController {
private:
    MyFileDatabase* myFileDatabase;

public:
    void initRoutes(crow::App<>& app);
    void setDatabase(MyFileDatabase* db);

    void index(crow::response& res);
    void retrieveDepartment(const crow::request& req, crow::response& res);
    void retrieveCourse(const crow::request& req, crow::response& res);
    void isCourseFull(const crow::request& req, crow::response& res);
    void getMajorCountFromDept(const crow::request& req, crow::response& res);
    void identifyDeptChair(const crow::request& req, crow::response& res);
    void findCourseLocation(const crow::request& req, crow::response& res);
    void findCourseInstructor(const crow::request& req, crow::response& res);
    void findCourseTime(const crow::request& req, crow::response& res);
    void addMajorToDept(const crow::request& req, crow::response& res);
    void removeMajorFromDept(const crow::request& req, crow::response& res);
    void setEnrollmentCount(const crow::request& req, crow::response& res);
    void setCourseLocation(const crow::request& req, crow::response& res);
    void setCourseInstructor(const crow::request& req, crow::response& res);
    void setCourseTime(const crow::request& req, crow::response& res);
    void dropStudentFromCourse(const crow::request&, crow::response& res);
};

#endif
