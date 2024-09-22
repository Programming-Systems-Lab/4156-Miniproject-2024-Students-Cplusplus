// Copyright 2024 vcm2114
#include <string>

#ifndef _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_COURSE_H_
#define _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_COURSE_H_

class Course {
 private:
        int enrollmentCapacity;
        int enrolledStudentCount;
        std::string courseLocation;
        std::string instructorName;
        std::string courseTimeSlot;

 public:
        Course(int count, const std::string &instructorName,
        const std::string &courseLocation, const std::string &timeSlot);
        Course();

        std::string getCourseLocation() const;
        std::string getInstructorName() const;
        std::string getCourseTimeSlot() const;
        std::string display() const;


        bool isCourseFull() const;
        bool enrollStudent();
        bool dropStudent();

        void reassignInstructor(const std::string &newInstructorName);
        void reassignLocation(const std::string &newLocation);
        void reassignTime(const std::string &newTime);
        void setEnrolledStudentCount(int count);
        void serialize(std::ostream& out) const;
        void deserialize(std::istream& in);
};

#endif  // _USERS_VIRGILEMISON_DOCUMENTS_COLUMBIA_FALL24_ADV_SWE_4156_MINIPROJECT_2024_STUDENTS_CPLUSPLUS_INDIVIDUALMINIPROJECTCPP_INCLUDE_COURSE_H_"
