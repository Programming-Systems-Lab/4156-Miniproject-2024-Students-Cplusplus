// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#ifndef INDIVIDUALMINIPROJECTC___INCLUDE_ROUTECONTROLLER_H_
#define INDIVIDUALMINIPROJECTC___INCLUDE_ROUTECONTROLLER_H_

#include "crow.h" // NOLINT
#include "Globals.h" // NOLINT
#include "MyFileDatabase.h" // NOLINT

class RouteController {
    private:
        MyFileDatabase* myFileDatabase;

    public:
        void initRoutes(crow::App<>& app); // NOLINT
        void setDatabase(MyFileDatabase* db);

        void index(crow::response& res); // NOLINT
        void retrieveDepartment(const crow::request& req, crow::response& res); // NOLINT
        void retrieveCourse(const crow::request& req, crow::response& res); // NOLINT
        void isCourseFull(const crow::request& req, crow::response& res); // NOLINT
        void getMajorCountFromDept(const crow::request& req, crow::response& res); // NOLINT
        void identifyDeptChair(const crow::request& req, crow::response& res); // NOLINT
        void findCourseLocation(const crow::request& req, crow::response& res); // NOLINT
        void findCourseInstructor(const crow::request& req, crow::response& res); // NOLINT
        void findCourseTime(const crow::request& req, crow::response& res); // NOLINT
        void addMajorToDept(const crow::request& req, crow::response& res); // NOLINT
        void removeMajorFromDept(const crow::request& req, crow::response& res); // NOLINT
        void setEnrollmentCount(const crow::request& req, crow::response& res); // NOLINT
        void setCourseLocation(const crow::request& req, crow::response& res); // NOLINT
        void setCourseInstructor(const crow::request& req, crow::response& res); // NOLINT
        void setCourseTime(const crow::request& req, crow::response& res); // NOLINT
        void dropStudentFromCourse(const crow::request&, crow::response& res); // NOLINT
};

#endif // INDIVIDUALMINIPROJECTC___INCLUDE_ROUTECONTROLLER_H_
