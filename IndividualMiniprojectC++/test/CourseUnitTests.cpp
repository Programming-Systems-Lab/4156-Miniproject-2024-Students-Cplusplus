// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <gtest/gtest.h>
#include "Course.h"
#include <sstream>

class CourseUnitTests : public ::testing::Test {
protected:
    CourseUnitTests(){
        course1 = new Course(50, "Adam Cannon", "417 IAB", "13:10-14:25");
    }
    Course* course1;
    Course course2;
};

TEST_F(CourseUnitTests, ReassignAndGetterTest) {
    course1->reassignInstructor("Kaiser, Gail");
    course1->reassignLocation("833 MUD");
    course1->reassignTime("10:10am-11:25");

    EXPECT_EQ(course1->getEnrolledStudentCount(), 0);
    EXPECT_EQ(course1->getEnrollmentCapacity(), 50);
    EXPECT_EQ(course1->getInstructorName(), "Kaiser, Gail");
    EXPECT_EQ(course1->getCourseLocation(), "833 MUD");
    EXPECT_EQ(course1->getCourseTimeSlot(), "10:10am-11:25");
    
}

TEST_F(CourseUnitTests, EnrollStudentTest) {
    for(int i = 0; i < 50; i++){
        EXPECT_EQ(course1->enrollStudent(), true);
    }
    EXPECT_EQ(course1->enrollStudent(), false);
}

TEST_F(CourseUnitTests, DropStudentTest) {
    course1->setEnrolledStudentCount(50);
    for(int i = 0; i < 50; i++){
        EXPECT_EQ(course1->dropStudent(), true);
    }
    EXPECT_EQ(course1->dropStudent(), false);
}

TEST_F(CourseUnitTests, DisplayTest) {
    std::string expectedResult = "\nInstructor: Adam Cannon; Location: 417 IAB; Time: 13:10-14:25";
    ASSERT_EQ(expectedResult, course1->display());
}

TEST_F(CourseUnitTests, SerializeAndDeserializeTest) {
    course1->setEnrolledStudentCount(30);
    std::stringstream ss;

    course1->serialize(ss);
    course2.deserialize(ss);

    EXPECT_EQ(course1->getEnrolledStudentCount(), course2.getEnrolledStudentCount());
    EXPECT_EQ(course1->getEnrollmentCapacity(), course2.getEnrollmentCapacity());
    EXPECT_EQ(course1->getCourseLocation(), course2.getCourseLocation());
    EXPECT_EQ(course1->getInstructorName(), course2.getInstructorName());
    EXPECT_EQ(course1->getCourseTimeSlot(), course2.getCourseTimeSlot());
}