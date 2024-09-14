#include <string>
#include <map>
#include "Course.h"
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <map>
#include <string>
#include <memory>

class Department {
    public:
        Department(std::string departmentCode, std::map<std::string, std::shared_ptr<Course>> coursesList,
                std::string departmentChairName, int majorCount);

        Department();

        int getNumberOfMajors() const;
        void serialize(std::ostream& out) const;
        void deserialize(std::istream& in);
        void increaseNumOfMajor();
        void decreaseNumOfMajor();
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



#endif