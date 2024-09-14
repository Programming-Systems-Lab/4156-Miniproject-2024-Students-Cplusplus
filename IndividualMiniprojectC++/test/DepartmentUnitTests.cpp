#include <memory>
#include <gtest/gtest.h>
#include "Department.h" 
#include "Course.h"

class DepartmentUnitTests : public ::testing::Test {
protected:
    static Department* testDepartment;

    static void SetUpTestSuite() {
        std::map<std::string, std::shared_ptr<Course>> courses;
        courses["CS101"] = std::make_shared<Course>(30, "Dr. Jacob", "101 Main", "9:00-10:00");
        testDepartment = new Department("CS", courses, "Dr. Bean", 500);
    }

    static void TearDownTestSuite() {
        delete testDepartment;
    }
};

Department* DepartmentUnitTests::testDepartment = nullptr;

TEST_F(DepartmentUnitTests, GetDepartmentChairTest) {
    ASSERT_EQ("Dr. Bean", testDepartment->getDepartmentChair());
}

TEST_F(DepartmentUnitTests, GetNumberOfMajorsTest) {
    ASSERT_EQ(500, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, AddPersonToMajorTest) {
    testDepartment->addPersonToMajor();
    ASSERT_EQ(501, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, DropPersonFromMajorTest) {
    testDepartment->dropPersonFromMajor();
    ASSERT_EQ(500, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, DropPersonBelowZeroTest) {
    testDepartment->dropPersonFromMajor();
    for (int i = 0; i < 500; ++i) {
        testDepartment->dropPersonFromMajor();
    }
    ASSERT_EQ(0, testDepartment->getNumberOfMajors());

    // Test if the count doesn't go below zero
    testDepartment->dropPersonFromMajor();
    ASSERT_EQ(0, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, AddCourseTest) {
    std::shared_ptr<Course> newCourse = std::make_shared<Course>(20, "Dr. Lee", "213 CSC", "9:00-11:00");
    testDepartment->addCourse("CS102", newCourse);
    auto courses = testDepartment->getCourseSelection();
    ASSERT_EQ(2, courses.size());
    ASSERT_EQ("213 CSC", courses["CS102"]->getCourseLocation());
}

TEST_F(DepartmentUnitTests, CreateCourseTest) {
    testDepartment->createCourse("CS103", "Dr. Cooper", "303 CSC", "11:00-12:00", 40);
    auto courses = testDepartment->getCourseSelection();
    ASSERT_EQ(3, courses.size());
    ASSERT_EQ("Dr. Cooper", courses["CS103"]->getInstructorName());
}

