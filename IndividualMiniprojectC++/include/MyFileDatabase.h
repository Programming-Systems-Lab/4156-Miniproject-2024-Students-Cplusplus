// Copyright 2024 vcm2114
#include "Department.h"
#include <map>
#include <string>

#ifndef _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_MYFILEDATABASE_H_
#define _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_MYFILEDATABASE_H_

class MyFileDatabase {
 public:
        MyFileDatabase(int flag, const std::string& filePath);

        void setMapping(const std::map<std::string, Department>& mapping);
        void saveContentsToFile() const;
        void deSerializeObjectFromFile();

        std::map<std::string, Department> getDepartmentMapping() const;
        std::string display() const;

 private:
        std::map<std::string, Department> departmentMapping;
        std::string filePath;
};

#endif  // _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_MYFILEDATABASE_H_"
