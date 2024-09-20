/* Copyright 2024 Vidushi Bansal */

#include "../include/Course.h" 
#include <gtest/gtest.h>

//Course* CourseUnitTests::testCourse1 = nullptr;


TEST(CourseUnitTests, EnrollStudentTest) {    
    Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");    

    for(int i = 0; i<255; i++){
        
        testcourse.setEnrolledStudentCount(i);

        if(i<250){            
            EXPECT_EQ(testcourse.enrollStudent(), true);
            EXPECT_EQ(testcourse.isCourseFull(), false);
        }
        else{
            EXPECT_EQ(testcourse.enrollStudent(), false);
            EXPECT_EQ(testcourse.isCourseFull(), true);
        }   
    }
}

//dropStudent
TEST(CourseUnitTests, DropStudentTest) {
    Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");    

    for(int i = 0; i<255; i++){
        
        testcourse.setEnrolledStudentCount(i);

        if(i=0){
            EXPECT_EQ(testcourse.dropStudent(), false);
        }
        else if(i>0 && i<=250){            
            EXPECT_EQ(testcourse.dropStudent(), true);
        }
        else{
            EXPECT_EQ(testcourse.enrollStudent(), false);
        }   
    }
}

//getCourseLocation
TEST(CourseUnitTests, CourseLocationTest) {
    Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::string expectedResult = "417 IAB";
    EXPECT_EQ(testcourse.getCourseLocation(), expectedResult);
}

//display
TEST(CourseUnitTests, DisplayTest) {
    Course testcourse(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::string expectedResult = "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
    EXPECT_EQ(testcourse.display(), expectedResult);
}