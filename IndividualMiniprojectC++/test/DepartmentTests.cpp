// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <gtest/gtest.h>
#include "Department.h"

class DepartmentTests : public ::testing::Test {
protected:
    DepartmentTests(){
        // Data for COMS department
        auto coms1004 = std::make_shared<Course>(400, "Adam Cannon", "417 IAB", "11:40-12:55");
        auto coms3251 = std::make_shared<Course>(125, "Tony Dear", "402 CHANDLER", "1:10-3:40");
        courses["1004"] = coms1004;
        courses["3251"] = coms3251;

        department1 = new Department("COMS", courses, "Luca Carloni", 2700);
    }
    std::map<std::string, std::shared_ptr<Course>> courses;
    Department* department1;
    Department department2;
};

TEST_F(DepartmentTests, GetterTest) {

    EXPECT_EQ(department1->getNumberOfMajors(), 2700);
    EXPECT_EQ(department1->getDepartmentChair(), "Luca Carloni");
    
    std::map<std::string, std::shared_ptr<Course>> department1_courses = department1->getCourseSelection();
    for (const auto& it : department1_courses) {
        EXPECT_EQ(department1_courses[it.first]->getEnrolledStudentCount(), courses[it.first]->getEnrolledStudentCount());
        EXPECT_EQ(department1_courses[it.first]->getEnrollmentCapacity(), courses[it.first]->getEnrollmentCapacity());
        EXPECT_EQ(department1_courses[it.first]->getCourseLocation(), courses[it.first]->getCourseLocation());
        EXPECT_EQ(department1_courses[it.first]->getCourseTimeSlot(), courses[it.first]->getCourseTimeSlot());
        EXPECT_EQ(department1_courses[it.first]->getInstructorName(), courses[it.first]->getInstructorName());
    }
}

TEST_F(DepartmentTests, AddPersonToMajorTest) {
    ASSERT_EQ(department1->getNumberOfMajors(), 2700);
    for(int i=0; i<10 ; i++){
        department1->addPersonToMajor();
    }
    EXPECT_EQ(department1->getNumberOfMajors(), 2710);
}

TEST_F(DepartmentTests, DropPersonToMajorTest) {
    ASSERT_EQ(department1->getNumberOfMajors(), 2700);

    for(int i=0; i<10 ; i++){
        department1->dropPersonFromMajor();
    }
    EXPECT_EQ(department1->getNumberOfMajors(), 2690);

    for(int i=0; i<2700 ; i++){
        department1->dropPersonFromMajor();
    }
    EXPECT_EQ(department1->getNumberOfMajors(), 0);
}

TEST_F(DepartmentTests, CreateCourseTest) {
    courses["3827"] = std::make_shared<Course>(300, "Daniel Rubenstein", "207 Math", "11:40-12:55");
    department1->createCourse("3827", "Daniel Rubenstein","207 Math", "11:40-12:55", 300);
    
    std::map<std::string, std::shared_ptr<Course>> department1_courses = department1->getCourseSelection();
    for (const auto& it : department1_courses) {
        EXPECT_EQ(department1_courses[it.first]->getEnrolledStudentCount(), courses[it.first]->getEnrolledStudentCount());
        EXPECT_EQ(department1_courses[it.first]->getEnrollmentCapacity(), courses[it.first]->getEnrollmentCapacity());
        EXPECT_EQ(department1_courses[it.first]->getCourseLocation(), courses[it.first]->getCourseLocation());
        EXPECT_EQ(department1_courses[it.first]->getCourseTimeSlot(), courses[it.first]->getCourseTimeSlot());
        EXPECT_EQ(department1_courses[it.first]->getInstructorName(), courses[it.first]->getInstructorName());
    }
}

TEST_F(DepartmentTests, DisplayTest) {
    std::string expectedResult = 
        "COMS 1004: \nInstructor: Adam Cannon; Location: 417 IAB; Time: 11:40-12:55\n"
        "COMS 3251: \nInstructor: Tony Dear; Location: 402 CHANDLER; Time: 1:10-3:40\n";
    ASSERT_EQ(expectedResult, department1->display());
}

TEST_F(DepartmentTests, SerializeAndDeserializeTest) {
    std::stringstream ss;
    department1->serialize(ss);
    department2.deserialize(ss);

    EXPECT_EQ(department1->getDepartmentChair(), department2.getDepartmentChair());
    EXPECT_EQ(department1->getNumberOfMajors(), department2.getNumberOfMajors());

    std::map<std::string, std::shared_ptr<Course>> department1_courses = department1->getCourseSelection();
    std::map<std::string, std::shared_ptr<Course>> department2_courses = department2.getCourseSelection();

    for (const auto& it : department1_courses) {
        EXPECT_EQ(department1_courses[it.first]->getEnrolledStudentCount(), department2_courses[it.first]->getEnrolledStudentCount());
        EXPECT_EQ(department1_courses[it.first]->getEnrollmentCapacity(), department2_courses[it.first]->getEnrollmentCapacity());
        EXPECT_EQ(department1_courses[it.first]->getCourseLocation(), department2_courses[it.first]->getCourseLocation());
        EXPECT_EQ(department1_courses[it.first]->getCourseTimeSlot(), department2_courses[it.first]->getCourseTimeSlot());
        EXPECT_EQ(department1_courses[it.first]->getInstructorName(), department2_courses[it.first]->getInstructorName());
    }
}