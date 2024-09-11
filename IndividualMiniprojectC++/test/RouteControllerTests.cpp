// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <gtest/gtest.h>

#include "MyApp.h"
#include "RouteController.h"

class RouteControllerTests : public ::testing::Test {
protected:
    RouteControllerTests(){
        controller.initRoutes(app);
        MyApp::run("setup"); 
        controller.setDatabase(MyApp::getDatabase());
    }
    crow::App<> app;
    RouteController controller;
    crow::request req;
    crow::response res;
};

TEST_F(RouteControllerTests, IndexTest) {
    controller.index(res);
    std:: string expectedResult = "Welcome, in order to make an API call direct your browser or Postman to an endpoint "
              "\n\n This can be done using the following format: \n\n http://127.0.0.1:8080/endpoint?arg=value";
    EXPECT_EQ(expectedResult, res.body);
}

TEST_F(RouteControllerTests, RetrieveDepartmentTest) {
    req.url_params = crow::query_string{"?deptCode=COMS"};
    controller.retrieveDepartment(req, res);
    std:: string expectedResult = R"(COMS 1004: 
Instructor: Adam Cannon; Location: 417 IAB; Time: 11:40-12:55
COMS 3134: 
Instructor: Brian Borowski; Location: 301 URIS; Time: 4:10-5:25
COMS 3157: 
Instructor: Jae Lee; Location: 417 IAB; Time: 4:10-5:25
COMS 3203: 
Instructor: Ansaf Salleb-Aouissi; Location: 301 URIS; Time: 10:10-11:25
COMS 3251: 
Instructor: Tony Dear; Location: 402 CHANDLER; Time: 1:10-3:40
COMS 3261: 
Instructor: Josh Alman; Location: 417 IAB; Time: 2:40-3:55
COMS 3827: 
Instructor: Daniel Rubenstein; Location: 207 Math; Time: 10:10-11:25
COMS 4156: 
Instructor: Gail Kaiser; Location: 501 NWC; Time: 10:10-11:25
)";
    EXPECT_EQ(200, res.code);
    EXPECT_EQ(expectedResult, res.body);

    // Test for 404
    crow::request req404;
    crow::response res404;
    req404.url_params = crow::query_string{"?deptCode=MATH"};
    controller.retrieveDepartment(req404, res404);
    expectedResult = "Department Not Found";
    EXPECT_EQ(404, res404.code);
    EXPECT_EQ(expectedResult, res404.body);
}

TEST_F(RouteControllerTests, IsCourseFullTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251"};
    controller.isCourseFull(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("false", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251"};
    controller.isCourseFull(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111"};
    controller.isCourseFull(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception"};
    controller.isCourseFull(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, GetMajorCountFromDeptTest) {
    req.url_params = crow::query_string{"?deptCode=COMS"};
    controller.getMajorCountFromDept(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("There are: 2700 majors in the department", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH"};
    controller.getMajorCountFromDept(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);
}

TEST_F(RouteControllerTests, IdentifyDeptChairTest) {
    req.url_params = crow::query_string{"?deptCode=COMS"};
    controller.identifyDeptChair(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Luca Carloni is the department chair.", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH"};
    controller.identifyDeptChair(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);
}

TEST_F(RouteControllerTests, FindCourseLocationTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251"};
    controller.findCourseLocation(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("402 CHANDLER is where the course is located.", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251"};
    controller.findCourseLocation(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111"};
    controller.findCourseLocation(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception"};
    controller.findCourseLocation(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, FindCourseInstructorTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251"};
    controller.findCourseInstructor(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Tony Dear is the instructor for the course.", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251"};
    controller.findCourseInstructor(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111"};
    controller.findCourseInstructor(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception"};
    controller.findCourseInstructor(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, FindCourseTimeTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251"};
    controller.findCourseTime(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("The course meets at: 1:10-3:40", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251"};
    controller.findCourseTime(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111"};
    controller.findCourseTime(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception"};
    controller.findCourseTime(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, AddMajorToDeptTest) {
    req.url_params = crow::query_string{"?deptCode=COMS"};
    controller.addMajorToDept(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Attribute was updated successfully", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH"};
    controller.addMajorToDept(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);
}

TEST_F(RouteControllerTests, SetEnrollmentCountTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251&count=69"};
    controller.setEnrollmentCount(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Attribute was updated successfully.", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251&count=69"};
    controller.setEnrollmentCount(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111&count=69"};
    controller.setEnrollmentCount(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception&count=69"};
    controller.setEnrollmentCount(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, SetCourseLocationTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251&location=301 URIS"};
    controller.setCourseLocation(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Attribute was updated successfully.", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251&location=301 URIS"};
    controller.setCourseLocation(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111&location=301 URIS"};
    controller.setCourseLocation(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception&location=301 URIS"};
    controller.setCourseLocation(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, SetCourseInstructorTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251&instructor=Jae Lee"};
    controller.setCourseInstructor(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Attribute was updated successfully.", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251&instructor=Jae Lee"};
    controller.setCourseInstructor(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111&instructor=Jae Lee"};
    controller.setCourseInstructor(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception&instructor=Jae Lee"};
    controller.setCourseInstructor(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, SetCourseTimeTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251&time=4:10-5:25"};
    controller.setCourseTime(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Attribute was updated successfully.", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251&time=4:10-5:25"};
    controller.setCourseTime(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111&time=4:10-5:25"};
    controller.setCourseTime(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception&time=4:10-5:25"};
    controller.setCourseTime(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}

TEST_F(RouteControllerTests, RemoveMajorFromDeptTest) {
    req.url_params = crow::query_string{"?deptCode=COMS"};
    controller.removeMajorFromDept(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Attribute was updated successfully", res.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH"};
    controller.removeMajorFromDept(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);
}

TEST_F(RouteControllerTests, DropStudentFromCourseTest) {
    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251"};
    controller.dropStudentFromCourse(req, res);
    EXPECT_EQ(200, res.code);
    EXPECT_EQ("Student has been dropped", res.body);

    req.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251&count=0"};
    controller.setEnrollmentCount(req, res);

    crow::request req400;
    crow::response res400;
    req400.url_params = crow::query_string{"?deptCode=COMS&courseCode=3251"};
    controller.dropStudentFromCourse(req400, res400);
    EXPECT_EQ(400, res400.code);
    EXPECT_EQ("Student has not been dropped", res400.body);

    crow::request req404_1;
    crow::response res404_1;
    req404_1.url_params = crow::query_string{"?deptCode=MATH&courseCode=3251"};
    controller.dropStudentFromCourse(req404_1, res404_1);
    EXPECT_EQ(404, res404_1.code);
    EXPECT_EQ("Department Not Found", res404_1.body);

    crow::request req404_2;
    crow::response res404_2;
    req404_2.url_params = crow::query_string{"?deptCode=COMS&courseCode=1111"};
    controller.dropStudentFromCourse(req404_2, res404_2);
    EXPECT_EQ(404, res404_2.code);
    EXPECT_EQ("Course Not Found", res404_2.body);

    crow::request req500;
    crow::response res500;
    req500.url_params = crow::query_string{"?deptCode=COMS&courseCode=exception"};
    controller.dropStudentFromCourse(req500, res500);
    EXPECT_EQ(500, res500.code);
    EXPECT_EQ("An error has occurred", res500.body);
}
