// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <gtest/gtest.h>
#include "Course.h" 

class CourseUnitTests : public ::testing::Test {
protected:
    CourseUnitTests(){
        COMS1002W = new Course(50, "Cannon, Adam", "417 IAB", "13:10-14:25");
    }
    Course* COMS1002W;
};

TEST_F(CourseUnitTests, ReassignAndGetterTest) {
    COMS1002W->reassignInstructor("Kaiser, Gail");
    COMS1002W->reassignLocation("833 MUD");
    COMS1002W->reassignTime("10:10am-11:25");

    EXPECT_EQ(COMS1002W->getInstructorName(), "Kaiser, Gail");
    EXPECT_EQ(COMS1002W->getCourseLocation(), "833 MUD");
    EXPECT_EQ(COMS1002W->getCourseTimeSlot(), "10:10am-11:25");
}

TEST_F(CourseUnitTests, EnrollStudentTest) {
    for(int i = 0; i < 50; i++){
        EXPECT_EQ(COMS1002W->enrollStudent(), true);
    }
    EXPECT_EQ(COMS1002W->enrollStudent(), false);
}

TEST_F(CourseUnitTests, DropStudentTest) {
    COMS1002W->setEnrolledStudentCount(50);
    for(int i = 0; i < 50; i++){
        EXPECT_EQ(COMS1002W->dropStudent(), true);
    }
    EXPECT_EQ(COMS1002W->dropStudent(), false);
}

TEST_F(CourseUnitTests, ToStringTest) {
    std::string expectedResult = "\nInstructor: Cannon, Adam; Location: 417 IAB; Time: 13:10-14:25";
    ASSERT_EQ(expectedResult, COMS1002W->display());
}
