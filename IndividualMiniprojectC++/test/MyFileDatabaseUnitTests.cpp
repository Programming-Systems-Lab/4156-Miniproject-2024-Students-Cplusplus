#include <gtest/gtest.h>
#include "MyFileDatabase.h"
#include "Department.h"
#include "Course.h"
#include <fstream>

class MyFileDatabaseUnitTests : public ::testing::Test {
protected:
    static const std::string testFilePath;
    static MyFileDatabase* testDatabase;
    static Department testDepartment;
    static std::shared_ptr<Course> testCourse;

    static void SetUpTestSuite() {
        // Set up a test course
        testCourse = std::make_shared<Course>(30, "Dr. Smith", "101 Main", "9:00-10:00");
        
        // Set up a test department with the test course
        std::map<std::string, std::shared_ptr<Course>> courses;
        courses["CS101"] = testCourse;
        testDepartment = Department("CS", courses, "Dr. Taylor", 500);

        // Set up the test database
        testDatabase = new MyFileDatabase(0, testFilePath);
        testDatabase->setMapping({{"CS", testDepartment}});
    }

    static void TearDownTestSuite() {
        delete testDatabase;
        std::remove(testFilePath.c_str()); 
    }
};

const std::string MyFileDatabaseUnitTests::testFilePath = "test_database.dat";
MyFileDatabase* MyFileDatabaseUnitTests::testDatabase = nullptr;
Department MyFileDatabaseUnitTests::testDepartment;
std::shared_ptr<Course> MyFileDatabaseUnitTests::testCourse;

TEST_F(MyFileDatabaseUnitTests, SaveContentsToFileTest) {

    testDatabase->saveContentsToFile();

    MyFileDatabase newDatabase(0, testFilePath);
    auto mapping = newDatabase.getDepartmentMapping();

    ASSERT_EQ(mapping.size(), 1);
    ASSERT_TRUE(mapping.find("CS") != mapping.end());

    const auto& dept = mapping["CS"];
    ASSERT_EQ(dept.getNumberOfMajors(), 500);
    ASSERT_EQ(dept.getDepartmentChair(), "Dr. Taylor");
    const auto& courses = dept.getCourseSelection();
    ASSERT_EQ(courses.size(), 1);
    ASSERT_EQ(courses.at("CS101")->getInstructorName(), "Dr. Smith");
}

TEST_F(MyFileDatabaseUnitTests, DeserializeObjectFromFileTest) {
    testDatabase->saveContentsToFile();

    MyFileDatabase newDatabase(0, testFilePath);
    auto mapping = newDatabase.getDepartmentMapping();

    ASSERT_EQ(mapping.size(), 1);
    ASSERT_TRUE(mapping.find("CS") != mapping.end());

    const auto& dept = mapping["CS"];
    ASSERT_EQ(dept.getNumberOfMajors(), 500);
    ASSERT_EQ(dept.getDepartmentChair(), "Dr. Taylor");
    const auto& courses = dept.getCourseSelection();
    ASSERT_EQ(courses.size(), 1);
    ASSERT_EQ(courses.at("CS101")->getInstructorName(), "Dr. Smith");
}

TEST_F(MyFileDatabaseUnitTests, SetAndGetMappingTest) {
    MyFileDatabase db(0, testFilePath);
    db.setMapping({{"CS", testDepartment}});
    auto mapping = db.getDepartmentMapping();

    ASSERT_EQ(mapping.size(), 1);
    ASSERT_TRUE(mapping.find("CS") != mapping.end());
    ASSERT_EQ(mapping["CS"].getNumberOfMajors(), 500);
}

TEST_F(MyFileDatabaseUnitTests, DisplayTest) {
    testDatabase->saveContentsToFile(); // Save contents to file
    std::string expectedDisplay = "For the CS department:\nCS CS101: \nInstructor: Dr. Smith; Location: 101 Main; Time: 9:00-10:00\n";

    ASSERT_EQ(testDatabase->display(), expectedDisplay);
}