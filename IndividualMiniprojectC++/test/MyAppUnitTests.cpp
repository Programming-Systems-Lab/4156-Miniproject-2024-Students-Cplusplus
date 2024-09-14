#include <gtest/gtest.h>
#include "MyApp.h"
#include "MyFileDatabase.h"
#include "Department.h"
#include "Course.h"
#include <fstream>

// Define constants
const std::string testFilePath = "testfile.bin";

// Utility function to clear the test file
void clearTestFile() {
    std::remove(testFilePath.c_str());
}

class MyAppUnitTests : public ::testing::Test {
protected:
    static MyApp* app;

    static void SetUpTestSuite() {
        clearTestFile(); // Ensure the test file is clean
        app = new MyApp();
    }

    static void TearDownTestSuite() {
        delete app;
        clearTestFile(); // Clean up the test file
    }
};

MyApp* MyAppUnitTests::app = nullptr;

TEST_F(MyAppUnitTests, RunSetupModeTest) {
    app->run("setup");

    MyFileDatabase* db = app->getDatabase();
    ASSERT_NE(db, nullptr);
    ASSERT_EQ(db->getDepartmentMapping().size(), 5);
}

TEST_F(MyAppUnitTests, RunStartupModeTest) {
    app->run("startup");

    MyFileDatabase* db = app->getDatabase();
    ASSERT_NE(db, nullptr);
}

TEST_F(MyAppUnitTests, OverrideDatabaseTest) {
    app->run("startup");
    
    MyFileDatabase* newDb = new MyFileDatabase(0, "override_testfile.bin");
    app->overrideDatabase(newDb);

    MyFileDatabase* currentDb = app->getDatabase();
    ASSERT_EQ(currentDb, newDb);

    delete currentDb; // Clean up the overridden database
}

TEST_F(MyAppUnitTests, OnTerminationTest) {
    app->run("setup");
    app->onTermination();

    // Check that the file was created and contains data
    std::ifstream inFile(testFilePath, std::ios::binary);
    ASSERT_TRUE(inFile.is_open());
    inFile.close();
    
    // Check if file is correctly created by attempting to read data
    MyFileDatabase db(0, testFilePath);
    ASSERT_EQ(db.getDepartmentMapping().size(), 5);
}

TEST_F(MyAppUnitTests, ResetDataFileTest) {
    app->run("setup");

    // Reset the file and check contents
    std::ifstream inFile(testFilePath, std::ios::binary);
    ASSERT_TRUE(inFile.is_open());

    MyFileDatabase db(0, testFilePath);
    auto mapping = db.getDepartmentMapping();
    
    ASSERT_EQ(mapping.size(), 5);

    // Further assertions can be added to check specific departments and courses
    ASSERT_NE(mapping.find("COMS"), mapping.end());
    ASSERT_NE(mapping.find("ECON"), mapping.end());
    ASSERT_NE(mapping.find("IEOR"), mapping.end());
    ASSERT_NE(mapping.find("CHEM"), mapping.end());
    ASSERT_NE(mapping.find("PHYS"), mapping.end());
}