// Copyright 2024 Richard Cruz-Silva
#include <gtest/gtest.h>
#include "RouteController.h"
#include "MyApp.h"

class RouteControllerUnitTests : public ::testing::Test {
 protected:
  static RouteController* testController;

  static void SetUpTestSuite() {
    MyApp::run("");

    crow::SimpleApp app;
    app.signal_clear();

    testController = new RouteController();
    testController->initRoutes(app);
    testController->setDatabase(MyApp::getDatabase());
  }

  static void TearDownTestSuite() {
    delete testController;
  }
};

RouteController* RouteControllerUnitTests::testController = nullptr;

TEST_F(RouteControllerUnitTests, index) {
  crow::response res;
  testController->index(res);

  std::string expectedString = "Welcome, in order to make an API call direct your browser or Postman to an endpoint "
                               "\n\nThis can be done using the following format: \n\nhttp://127.0.0.1:8080/endpoint?arg=value";
  ASSERT_EQ(res.body, expectedString);
}

TEST_F(RouteControllerUnitTests, retrieveDepartment) {
  crow::request req;
  crow::response res;

  testController->retrieveDepartment(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, retrieveCourse) {
  crow::request req;
  crow::response res;

  testController->retrieveCourse(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, isCourseFull) {
  crow::request req;
  crow::response res;

  testController->isCourseFull(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, getMajorCountFromDept) {
  crow::request req;
  crow::response res;

  testController->getMajorCountFromDept(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, identifyDeptChair) {
  crow::request req;
  crow::response res;

  testController->identifyDeptChair(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, findCourseLocation) {
  crow::request req;
  crow::response res;

  testController->findCourseLocation(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, findCourseInstructor) {
  crow::request req;
  crow::response res;

  testController->findCourseInstructor(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, findCourseTime) {
  crow::request req;
  crow::response res;

  testController->findCourseTime(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, addMajorToDept) {
  crow::request req;
  crow::response res;

  testController->addMajorToDept(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, setEnrollmentCount) {
  crow::request req;
  crow::response res;

  testController->setEnrollmentCount(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, setCourseLocation) {
  crow::request req;
  crow::response res;

  testController->setCourseLocation(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, setCourseInstructor) {
  crow::request req;
  crow::response res;

  testController->setCourseInstructor(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, setCourseTime) {
  crow::request req;
  crow::response res;

  testController->setCourseTime(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, removeMajorFromDept) {
  crow::request req;
  crow::response res;

  testController->removeMajorFromDept(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}

TEST_F(RouteControllerUnitTests, dropStudentFromCourse) {
  crow::request req;
  crow::response res;

  testController->dropStudentFromCourse(req, res);

  ASSERT_EQ("An error has occurred", res.body);
}