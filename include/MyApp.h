// Copyright 2024 Jason Han
#ifndef MYAPP_H
#define MYAPP_H

#include "Course.h"
#include "Department.h"
#include "MyFileDatabase.h"
#include <map>
#include <string>

class MyApp {
public:
    static void run(const std::string& mode);
    static void onTermination();
    static void overrideDatabase(MyFileDatabase* testData);
    static MyFileDatabase* getDatabase();

private:
    static void setupDatabase();
    static void resetDataFile();

    static MyFileDatabase* myFileDatabase;
    static bool saveData;
};

#endif
