#ifndef MYAPP_H
#define MYAPP_H

#include <string>
#include <map>
#include "Course.h"
#include "Department.h"
#include "MyFileDatabase.h"

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
