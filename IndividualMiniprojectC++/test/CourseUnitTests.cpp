/* Copyright 2024 Vidushi Bansal */
#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include "../include/Course.h"

Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");

TEST(CourseUnitTests, EnrollStudentTest)
{
    EXPECT_EQ(7*7, 49);
    //Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");

    for (int i = 1; i < 255; i++)
    {      
        //testcourse.setEnrolledStudentCount(i);

        printf("i: %d ", i);

        if (i < 250)
        {
            EXPECT_EQ(testcourse.enrollStudent(), true);
            EXPECT_EQ(testcourse.isCourseFull(), false);
        }
        else if (i==250)
        {
            EXPECT_EQ(testcourse.enrollStudent(), true);
            EXPECT_EQ(testcourse.isCourseFull(), true);
        }
        else
        {
            EXPECT_EQ(testcourse.enrollStudent(), false);
            EXPECT_EQ(testcourse.isCourseFull(), true);
        }
    }
}

// dropStudent
TEST(CourseUnitTests, DropStudentTest)
{
    //Course testDrop(250, "Griffin Newbold", "417 IAB", "11:40-12:55");

    testcourse.setEnrolledStudentCount(250);
    
    for (int i = 250; i > 0; i--)
    {        
        if (i == 0)
        {
            EXPECT_EQ(testcourse.dropStudent(), false);
        }
        else if (i > 0)
        {
            EXPECT_EQ(testcourse.dropStudent(), true);
        }        
    }
}

// getCourseLocation
TEST(CourseUnitTests, CourseLocationTest)
{
    //Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::string expectedResult = "417 IAB";
    EXPECT_EQ(testcourse.getCourseLocation(), expectedResult);
}

// display
TEST(CourseUnitTests, DisplayTest)
{
    //Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::string expectedResult = "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
    EXPECT_EQ(testcourse.display(), expectedResult);
}

//getInstructorName
TEST(CourseUnitTests, InstructorNameTest)
{
    //Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::string expectedResult = "Griffin Newbold";
    EXPECT_EQ(testcourse.getInstructorName(), expectedResult);
}

//getCoursetimeslot
TEST(CourseUnitTests, CourseTimeslotTest)
{
    //Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::string expectedResult = "11:40-12:55";
    EXPECT_EQ(testcourse.getCourseTimeSlot(), expectedResult);
}

//reassignInstructor
TEST(CourseUnitTests, reassignInstructorTest)
{
    std::string newInstructor = "Vidushi Bansal";
    testcourse.reassignInstructor(newInstructor);
    EXPECT_EQ(testcourse.getInstructorName(), newInstructor);
}

//reassignLocation
TEST(CourseUnitTests, reassignLocationTest)
{
    std::string newLocation = "401 MUDD";
    testcourse.reassignLocation(newLocation);
    EXPECT_EQ(testcourse.getCourseLocation(), newLocation);
}

//reassignTime
TEST(CourseUnitTests, reassignTimeTest)
{
    std::string newTimeslot = "11:10-12:55";
    testcourse.reassignTime(newTimeslot);
    EXPECT_EQ(testcourse.getCourseTimeSlot(), newTimeslot);
}

TEST(CourseUnitTests, serializedeserializeTest)
{
    testcourse.enrollStudent();
    
    std::ostringstream outStream;
    testcourse.serialize(outStream);

    Course deserializedCourse;
    std::istringstream inStream(outStream.str());
    deserializedCourse.deserialize(inStream);

    //EXPECT_EQ(testcourse.getEnrollmentCapacity(), deserializedCourse.getEnrollmentCapacity());
    //EXPECT_EQ(testcourse.enrolledStudentCount, deserializedCourse.enrolledStudentCount);
    EXPECT_EQ(testcourse.getCourseLocation(), deserializedCourse.getCourseLocation());
    EXPECT_EQ(testcourse.getInstructorName(), deserializedCourse.getInstructorName());
    EXPECT_EQ(testcourse.getCourseTimeSlot(), deserializedCourse.getCourseTimeSlot());
}