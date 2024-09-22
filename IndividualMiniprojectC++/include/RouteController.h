// Copyright 2024 vcm2114
#ifndef _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_ROUTECONTROLLER_H_
#define _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_ROUTECONTROLLER_H_

#include "../external_libraries/Crow-1.2.0/include/crow.h"
#include "Globals.h"
#include "MyFileDatabase.h"

class RouteController {
 private:
        MyFileDatabase* myFileDatabase;

 public:
        void initRoutes(const crow::App<>& app);
        void setDatabase(MyFileDatabase* db);

        void index(const crow::response& res);
        void retrieveDepartment(const crow::request& req, const crow::response& res);
        void retrieveCourse(const crow::request& req, const crow::response& res);
        void isCourseFull(const crow::request& req, const crow::response& res);
        void getMajorCountFromDept(const crow::request& req, const crow::response& res);
        void identifyDeptChair(const crow::request& req, const crow::response& res);
        void findCourseLocation(const crow::request& req, const crow::response& res);
        void findCourseInstructor(const crow::request& req, const crow::response& res);
        void findCourseTime(const crow::request& req, const crow::response& res);
        void addMajorToDept(const crow::request& req, const crow::response& res);
        void removeMajorFromDept(const crow::request& req, const crow::response& res);
        void setEnrollmentCount(const crow::request& req, const crow::response& res);
        void setCourseLocation(const crow::request& req, const crow::response& res);
        void setCourseInstructor(const crow::request& req, const crow::response& res);
        void setCourseTime(const crow::request& req, const crow::response& res);
        void dropStudentFromCourse(const crow::request&, const crow::response& res);
};

#endif  // _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_ROUTECONTROLLER_H_"
