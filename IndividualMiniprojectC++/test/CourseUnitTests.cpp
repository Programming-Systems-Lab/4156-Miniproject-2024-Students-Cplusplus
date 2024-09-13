#include <gtest/gtest.h>
#include "Course.h"

class CourseUnitTests : public ::testing::Test {
 protected:
    static Course* testCourse;
    static Course* testCourse2;
    static Course* testCourse3;

    static void SetUpTestSuite() {
        testCourse = new Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
        testCourse2 = new Course(600, "Griffin Newbold", "417 IAB", "11:40-12:55");
        testCourse3 = new Course();
    }

    static void TearDownTestSuite() {
        delete testCourse;
        delete testCourse2;
        delete testCourse3;
    }
};


Course* CourseUnitTests::testCourse = nullptr;
Course* CourseUnitTests::testCourse2 = nullptr;
Course* CourseUnitTests::testCourse3 = nullptr;

TEST_F(CourseUnitTests, ToStringTest) {
    std::string expectedResult = "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
    ASSERT_EQ(expectedResult, testCourse->display());
}

TEST_F(CourseUnitTests, EnrollStudentTest) {
    ASSERT_TRUE(testCourse2->enrollStudent());
}

TEST_F(CourseUnitTests, DropStudentTest) {
    ASSERT_FALSE(testCourse3->dropStudent());
}

TEST_F(CourseUnitTests, IsCourseFullTest) {
    ASSERT_FALSE(testCourse->isCourseFull());
}