// Copyright 2024 vcm2114
#include <string>
#include <map>
#include "Course.h"
#ifndef _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_DEPARTMENT_H_
#define _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_DEPARTMENT_H_

#include <memory>

class Department {
 public:
        Department(std::string deptCode, std::map<std::string, std::shared_ptr<Course>> courses,
                std::string departmentChair, int numberOfMajors);

        Department();

        int getNumberOfMajors() const;
        void serialize(std::ostream& out) const;
        void deserialize(std::istream& in);
        void addPersonToMajor();
        void dropPersonFromMajor();
        void addCourse(std::string courseId, std::shared_ptr<Course> course);
        void createCourse(std::string courseId, std::string instructorName, std::string courseLocation,
                        std::string courseTimeSlot, int capacity);
        std::string display() const;
        std::string getDepartmentChair() const;
        std::map<std::string, std::shared_ptr<Course>> getCourseSelection() const;

 private:
        int numberOfMajors;
        std::string deptCode;
        std::string departmentChair;
        std::map<std::string, std::shared_ptr<Course>> courses;
};



#endif  // _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_DEPARTMENT_H_"
