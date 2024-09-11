// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include "Department.h"
#include <map>
#include <string>

#ifndef INDIVIDUALMINIPROJECTC___INCLUDE_MYFILEDATABASE_H_
#define INDIVIDUALMINIPROJECTC___INCLUDE_MYFILEDATABASE_H_

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

#endif // INDIVIDUALMINIPROJECTC___INCLUDE_MYFILEDATABASE_H_