#include <gtest/gtest.h>
#include "Department.h"

class DepartmentUnitTests : public ::testing::Test {
 protected:
    static Department* testDepartment;
    static Department* testDepartment2;

    static void SetUpTestSuite() {
        auto course1 = std::make_shared<Course>(150,
        "Dr. Smith", "Room 101", "MWF 10:00-11:00 AM");
        auto course2 = std::make_shared<Course>(200,
        "Prof. Johnson", "Room 102", "TR 2:00-3:30 PM");
        std::map<std::string, std::shared_ptr<Course>> courses = {
            {"CS101", course1},
            {"CS102", course2}
        };
        testDepartment = new Department("CS", courses,
         "Dr. Jameson", 120);
        testDepartment2 = new Department();
    }

    static void TearDownTestSuite() {
        delete testDepartment;
        delete testDepartment2;
    }
};

Department* DepartmentUnitTests::testDepartment = nullptr;
Department* DepartmentUnitTests::testDepartment2 = nullptr;

TEST_F(DepartmentUnitTests, AddPersonToMajorTest) {
    testDepartment2->addPersonToMajor();
    ASSERT_EQ(1, testDepartment2->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, getDepartmentChairTest) {
    ASSERT_EQ("Dr. Jameson", testDepartment->getDepartmentChair());
}

TEST_F(DepartmentUnitTests, removePersonFromMajorTest) {
    testDepartment->dropPersonFromMajor();
    ASSERT_EQ(119, testDepartment->getNumberOfMajors());
}