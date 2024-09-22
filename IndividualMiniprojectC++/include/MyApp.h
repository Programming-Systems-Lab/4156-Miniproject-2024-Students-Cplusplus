// Copyright 2024 vcm2114
#ifndef _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_MYAPP_H_
#define _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_MYAPP_H_

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

#endif  // _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_MYAPP_H_"
