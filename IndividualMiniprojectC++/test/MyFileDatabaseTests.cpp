// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <gtest/gtest.h>
#include "MyFileDatabase.h"

class MyFileDatabaseTests : public ::testing::Test {
protected:
    MyFileDatabaseTests(){
        // Data for COMS department
        auto coms3251 = std::make_shared<Course>(125, "Tony Dear", "402 CHANDLER", "1:10-3:40");
        courses["3251"] = coms3251;

        department1 = new Department("COMS", courses, "Luca Carloni", 2700);
        departments["COMS"] = *department1;
    }
    MyFileDatabase database1{1, "database.bin"};
    std::map<std::string, std::shared_ptr<Course>> courses;
    std::map<std::string, Department> departments;
    Department* department1;
};

TEST_F(MyFileDatabaseTests, GetterAndSetterTest) {
    database1.setMapping(departments);
    std::map<std::string, Department> temp_departments;
    temp_departments = database1.getDepartmentMapping();
    EXPECT_EQ(temp_departments["COMS"].display(), departments["COMS"].display());
}

TEST_F(MyFileDatabaseTests, SaveAndReadContentsToFileTest) {
    database1.setMapping(departments);
    database1.saveContentsToFile();
    MyFileDatabase database2{0, "database.bin"};
    std::string expectedResult = "For the COMS department:\nCOMS 3251: \nInstructor: Tony Dear; Location: 402 CHANDLER; Time: 1:10-3:40\n\n";
    ASSERT_EQ(expectedResult, database2.display());
}

