// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <string>
#include <map>
#include <memory>

#include "Course.h"

#ifndef INDIVIDUALMINIPROJECTC___INCLUDE_DEPARTMENT_H_
#define INDIVIDUALMINIPROJECTC___INCLUDE_DEPARTMENT_H_



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

#endif // INDIVIDUALMINIPROJECTC___INCLUDE_DEPARTMENT_H_