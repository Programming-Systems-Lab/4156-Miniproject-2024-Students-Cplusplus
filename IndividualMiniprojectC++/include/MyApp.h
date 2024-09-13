#include <string>
#include <map>
#include <memory>
#include "Course.h"
#include "Department.h"
#include "MyFileDatabase.h"

#pragma once

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

