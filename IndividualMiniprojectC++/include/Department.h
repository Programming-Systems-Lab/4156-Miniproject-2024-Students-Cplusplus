#include <string>
#include <map>
#include "Course.h"
#include <memory>

#pragma once

using String_to_Course = std::map<std::string, std::shared_ptr<Course>>;

class Department {
 public:
        Department(std::string deptCode, std::map<std::string,
                 std::shared_ptr<Course>> courses,
                 std::string departmentChair, int numberOfMajors);

        Department();

        int getNumberOfMajors() const;
        void serialize(std::ostream& out) const;
        void deserialize(std::istream& in);
        void addPersonToMajor();
        void dropPersonFromMajor();
        void addCourse(std::string courseId, std::shared_ptr<Course> course);
        void createCourse(std::string courseId,
                        std::string instructorName, std::string courseLocation,
                        std::string courseTimeSlot, int capacity);
        std::string display() const;
        std::string getDepartmentChair() const;
        String_to_Course getCourseSelection() const;

 private:
        int numberOfMajors;
        std::string deptCode;
        std::string departmentChair;
        String_to_Course courses;
};
