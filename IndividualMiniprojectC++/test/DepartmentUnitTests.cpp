// Copyright 2024 Richard Cruz-Silva
#include <gtest/gtest.h>
#include "Department.h"

class DepartmentUnitTests : public ::testing::Test {
 protected:
  static Department* testDepartment;

  static void SetUpTestSuite() {
    std::string times[] = {"11:40-12:55", "4:10-5:25",
                          "10:10-11:25", "2:40-3:55"};
    std::string locations[] = {"417 IAB", "309 HAV", "301 URIS"};

    // Data for COMS department
    auto coms1004 = std::make_shared<Course>(400, "Adam Cannon",
                                            locations[0], times[0]);
    coms1004->setEnrolledStudentCount(249);
    auto coms3134 = std::make_shared<Course>(250, "Brian Borowski",
                                            locations[2], times[1]);
    coms3134->setEnrolledStudentCount(242);
    auto coms3157 = std::make_shared<Course>(400, "Jae Lee",
                                            locations[0], times[1]);
    coms3157->setEnrolledStudentCount(311);
    auto coms3203 = std::make_shared<Course>(250, "Ansaf Salleb-Aouissi",
                                            locations[2], times[2]);
    coms3203->setEnrolledStudentCount(215);
    auto coms3261 = std::make_shared<Course>(150, "Josh Alman",
                                            locations[0], times[3]);
    coms3261->setEnrolledStudentCount(140);
    auto coms3251 = std::make_shared<Course>(125, "Tony Dear",
                                            "402 CHANDLER", "1:10-3:40");
    coms3251->setEnrolledStudentCount(99);
    auto coms3827 = std::make_shared<Course>(300, "Daniel Rubenstein",
                                            "207 Math", times[2]);
    coms3827->setEnrolledStudentCount(283);
    auto coms4156 = std::make_shared<Course>(120, "Gail Kaiser",
                                            "501 NWC", times[2]);
    coms4156->setEnrolledStudentCount(109);

    std::map<std::string, std::shared_ptr<Course>> courses;
    courses["1004"] = coms1004;
    courses["3134"] = coms3134;
    courses["3157"] = coms3157;
    courses["3203"] = coms3203;
    courses["3261"] = coms3261;
    courses["3251"] = coms3251;
    courses["3827"] = coms3827;
    courses["4156"] = coms4156;

    testDepartment = new Department("COMS", courses, "Luca Carloni", 2700);
  }

  static void TearDownTestSuite() {
    for (auto& item : testDepartment->getCourseSelection())
      item.second.reset();
    delete testDepartment;
  }
};

Department* DepartmentUnitTests::testDepartment = nullptr;

TEST_F(DepartmentUnitTests, emptyConstructor) {
  Department department;
  ASSERT_EQ(department.getNumberOfMajors(), 0);
}

TEST_F(DepartmentUnitTests, NumberOfMajors) {
  ASSERT_EQ(testDepartment->getNumberOfMajors(), 2700);
  testDepartment->addPersonToMajor();
  ASSERT_EQ(testDepartment->getNumberOfMajors(), 2701);
  testDepartment->dropPersonFromMajor();
  testDepartment->dropPersonFromMajor();
  ASSERT_EQ(testDepartment->getNumberOfMajors(), 2699);
}

TEST_F(DepartmentUnitTests, DepartmentChair) {
  ASSERT_EQ(testDepartment->getDepartmentChair(), "Luca Carloni");
}

TEST_F(DepartmentUnitTests, ToString) {
  std::ostringstream expectedString;
  for (const auto& it : testDepartment->getCourseSelection()) {
    expectedString << "COMS" << " " << it.first << ": "
    << it.second->display() << "\n";
  }
  ASSERT_EQ(expectedString.str(), testDepartment->display());
}

TEST_F(DepartmentUnitTests, AddCourses) {
  auto courses = testDepartment->getCourseSelection();
  std::string newId = "9999";
  ASSERT_EQ(courses.find(newId), courses.end());
  testDepartment->createCourse(newId, "Albert Einstein", "111 ABC",
                               "1:10-3:40", 60);
  courses = testDepartment->getCourseSelection();
  ASSERT_NE(courses.find(newId), courses.end());
}