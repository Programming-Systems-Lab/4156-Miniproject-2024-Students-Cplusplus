#include <fstream>
#include <gtest/gtest.h>
#include "Department.h"

class DepartmentUnitTests : public ::testing::Test {
 protected:
    static Department* testDepartment;
    static Department* testDepartment2;
    static Department* testDepartment3;

    static void SetUpTestSuite() {
        auto course1 = std::make_shared<Course>(150,
        "Dr. Smith", "Room 101", "MWF 10:00-11:00 AM");
        auto course2 = std::make_shared<Course>(200,
        "Prof. Johnson", "Room 102", "TR 2:00-3:30 PM");
        std::map<std::string, std::shared_ptr<Course>> courses = {
            {"CS101", course1},
            {"CS102", course2}
        };
        testDepartment = new Department("CS", courses,
         "Dr. Jameson", 120);
        testDepartment2 = new Department();
        testDepartment3 = new Department("CS", courses
        , "Dr. Jameson", 120);
    }

    static void TearDownTestSuite() {
        delete testDepartment;
        delete testDepartment2;
        delete testDepartment3;
    }
};

Department* DepartmentUnitTests::testDepartment = nullptr;
Department* DepartmentUnitTests::testDepartment2 = nullptr;
Department* DepartmentUnitTests::testDepartment3 = nullptr;

TEST_F(DepartmentUnitTests, AddPersonToMajorTest) {
    testDepartment2->addPersonToMajor();
    ASSERT_EQ(1, testDepartment2->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, getDepartmentChairTest) {
    ASSERT_EQ("Dr. Jameson", testDepartment->getDepartmentChair());
}

TEST_F(DepartmentUnitTests, removePersonFromMajorTest) {
    testDepartment->dropPersonFromMajor();
    ASSERT_EQ(119, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, displayTest) {
     std::ostringstream expected;
     expected << "CS CS101: \nInstructor: Dr. Smith; Location: Room 101; Time: MWF 10:00-11:00 AM\nCS CS102:"
     <<" \nInstructor: Prof. Johnson; Location: Room 102; Time: TR 2:00-3:30 PM\n";
    ASSERT_EQ(expected.str(), testDepartment->display());
}


TEST_F(DepartmentUnitTests, SerializeAndDeserializeTest) {
    std::string binaryFile = "testfile.bin";

    static Department* originalDept = testDepartment3;
    std::ofstream outFile(binaryFile, std::ios::binary);
    ASSERT_TRUE(outFile.is_open()) << "Failed to open file for writing.";
    originalDept->serialize(outFile);
    outFile.close();

    static Department* deserializedDept = new Department();
    std::ifstream inFile(binaryFile, std::ios::binary);
    ASSERT_TRUE(inFile.is_open()) << "Failed to open file for reading.";
    deserializedDept->deserialize(inFile);
    inFile.close();

    EXPECT_EQ(originalDept->display(), deserializedDept->display());
    EXPECT_EQ(originalDept->getDepartmentChair(), deserializedDept->getDepartmentChair());
    EXPECT_EQ(originalDept->getNumberOfMajors(), deserializedDept->getNumberOfMajors());

    std::remove(binaryFile.c_str());
}

