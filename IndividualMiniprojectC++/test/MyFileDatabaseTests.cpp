// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <gtest/gtest.h>
#include "MyFileDatabase.h"

class MyFileDatabaseTests : public ::testing::Test {
protected:
    MyFileDatabaseTests(){
        // Data for COMS department
        auto coms1004 = std::make_shared<Course>(400, "Adam Cannon", "417 IAB", "11:40-12:55");
        auto coms3251 = std::make_shared<Course>(125, "Tony Dear", "402 CHANDLER", "1:10-3:40");
        courses["1004"] = coms1004;
        courses["3251"] = coms3251;

        department1 = new Department("COMS", courses, "Luca Carloni", 2700);
        departments["COMS"] = *department1;
    }
    MyFileDatabase database1{1, "database.bin"};
    std::map<std::string, std::shared_ptr<Course>> courses;
    std::map<std::string, Department> departments;
    Department* department1;
};

TEST_F(MyFileDatabaseTests, SetterTest) {
    database1.setMapping(departments);
}