// Copyright 2024 Jason Han
#include "Course.h"
#include <gtest/gtest.h>

class CourseUnitTests : public ::testing::Test {
protected:
    static Course* testCourse;

    static void SetUpTestSuite() {
        testCourse = new Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    }

    static void TearDownTestSuite() {
        delete testCourse;
    }
};

Course* CourseUnitTests::testCourse = nullptr;

TEST_F(CourseUnitTests, ToStringTest) {
    std::string expectedResult =
        "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
    ASSERT_EQ(expectedResult, testCourse->display());
}
