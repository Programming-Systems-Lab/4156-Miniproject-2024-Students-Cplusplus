// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <gtest/gtest.h>
#include "MyApp.h"

TEST(MyAppTests, RunTest) {
    MyApp::run("setup");
    MyApp::onTermination();
    MyApp::run("");
    MyApp::onTermination();
}

TEST(MyAppTests, OverrideDatabaseAndGetterTest) {
    MyApp::run("setup");
    MyFileDatabase* temp_db = MyApp::getDatabase();
    EXPECT_EQ(MyApp::getDatabase()->display(), temp_db->display());
    MyFileDatabase* database1 = new MyFileDatabase(0, "database.bin");
    MyApp::overrideDatabase(database1);
    EXPECT_EQ(MyApp::getDatabase()->display(), database1->display());
}