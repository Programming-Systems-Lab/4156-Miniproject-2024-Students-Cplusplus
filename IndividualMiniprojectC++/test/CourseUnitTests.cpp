// Copyright 2024 Richard Cruz-Silva
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

TEST_F(CourseUnitTests, EmptyConstructor) {
  Course emptyCourse;
  std::string expectedLocation = "";
  ASSERT_EQ(expectedLocation, emptyCourse.getCourseLocation());
}

TEST_F(CourseUnitTests, enrollStudent) {
  if (testCourse->isCourseFull()) {
    ASSERT_FALSE(testCourse->enrollStudent());
  } else {
    ASSERT_TRUE(testCourse->enrollStudent());
  }
}

TEST_F(CourseUnitTests, dropStudent) {
  testCourse->setEnrolledStudentCount(50);
  ASSERT_TRUE(testCourse->dropStudent());
  testCourse->setEnrolledStudentCount(0);
  ASSERT_FALSE(testCourse->dropStudent());
}

TEST_F(CourseUnitTests, InstructorName) {
  ASSERT_EQ(testCourse->getInstructorName(), "Griffin Newbold");
  std::string newInstructor = "New Teach";
  testCourse->reassignInstructor(newInstructor);
  ASSERT_EQ(testCourse->getInstructorName(), newInstructor);
}

TEST_F(CourseUnitTests, TimeSlot) {
  ASSERT_EQ(testCourse->getCourseTimeSlot(), "11:40-12:55");
  std::string newTime = "10:40-11:55";
  testCourse->reassignTime(newTime);
  ASSERT_EQ(testCourse->getCourseTimeSlot(), newTime);
}

TEST_F(CourseUnitTests, Location) {
  ASSERT_EQ(testCourse->getCourseLocation(), "417 IAB");
  std::string newLocation = "420 ACB";
  testCourse->reassignLocation(newLocation);
  ASSERT_EQ(testCourse->getCourseLocation(), newLocation);
}

TEST_F(CourseUnitTests, serilaize) {
  testCourse->serialize(std::cout);
}

TEST_F(CourseUnitTests, deserialize) {
  //testCourse->deserialize(std::cin);
}