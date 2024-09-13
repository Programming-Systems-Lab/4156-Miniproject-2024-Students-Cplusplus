#pragma once

#include "../external_libraries/Crow/include/crow.h"
#include "Globals.h"
#include "MyFileDatabase.h"

using Response = crow::response&;
using Request = const::crow::request&;
using App = crow::App<>&;

class RouteController {
 private:
        MyFileDatabase* myFileDatabase;
 public:
        void initRoutes(App app);
        void setDatabase(MyFileDatabase* db);

        void index(Response res);
        void retrieveDepartment(Request req, Response res);
        void retrieveCourse(Request req, Response res);
        void isCourseFull(Request req, Response res);
        void getMajorCountFromDept(Request req, Response res);
        void identifyDeptChair(Request req, Response res);
        void findCourseLocation(Request req, Response res);
        void findCourseInstructor(Request req, Response res);
        void findCourseTime(Request req, Response res);
        void addMajorToDept(Request req, Response res);
        void removeMajorFromDept(Request req, Response res);
        void setEnrollmentCount(Request req, Response res);
        void setCourseLocation(Request req, Response res);
        void setCourseInstructor(Request req, Response res);
        void setCourseTime(Request req, Response res);
        void dropStudentFromCourse(Request, Response res);
};


