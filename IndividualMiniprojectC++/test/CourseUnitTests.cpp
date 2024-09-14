/** 
MIT License

Copyright (c) 2024 Programming Systems Lab @ Columbia University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gtest/gtest.h>
#include "Course.h" 

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
    std::string expectedResult = "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
    ASSERT_EQ(expectedResult, testCourse->display());
}

TEST_F(CourseUnitTests, EnrollStudentTest) {
    testCourse->setEnrolledStudentCount(0);  

    for (int i = 0; i < 250; ++i) {
        ASSERT_TRUE(testCourse->enrollStudent());
    }

    ASSERT_FALSE(testCourse->enrollStudent());
}

TEST_F(CourseUnitTests, DropStudentTest) {
    testCourse->setEnrolledStudentCount(10);  

    for (int i = 0; i < 5; ++i) {
        ASSERT_TRUE(testCourse->dropStudent());
    }
    ASSERT_EQ(testCourse->isCourseFull(), false);

    testCourse->setEnrolledStudentCount(0);  

    ASSERT_FALSE(testCourse->dropStudent()); 
}

TEST_F(CourseUnitTests, IsCourseFullTest) {
    testCourse->setEnrolledStudentCount(250);  
    ASSERT_TRUE(testCourse->isCourseFull());

    testCourse->setEnrolledStudentCount(249);  
    ASSERT_FALSE(testCourse->isCourseFull());

    testCourse->setEnrolledStudentCount(500);
    ASSERT_TRUE(testCourse->isCourseFull());
}

TEST_F(CourseUnitTests, ReassignInstructorTest) {
    testCourse->reassignInstructor("Dr. Bean");
    ASSERT_EQ(testCourse->getInstructorName(), "Dr. Bean");
}

TEST_F(CourseUnitTests, ReassignLocationTest) {
    testCourse->reassignLocation("613 Hamilton");
    ASSERT_EQ(testCourse->getCourseLocation(), "613 Hamilton");
}

TEST_F(CourseUnitTests, ReassignTimeTest) {
    testCourse->reassignTime("10:10-11:20");
    ASSERT_EQ(testCourse->getCourseTimeSlot(), "10:10-11:20");
}