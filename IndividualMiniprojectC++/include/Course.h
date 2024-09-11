// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include <string>
#ifndef INDIVIDUALMINIPROJECTC___INCLUDE_COURSE_H_
#define INDIVIDUALMINIPROJECTC___INCLUDE_COURSE_H_

class Course {
    private:
        int enrollmentCapacity;
        int enrolledStudentCount;
        std::string courseLocation;
        std::string instructorName;
        std::string courseTimeSlot;
    
    public:
        Course(int count, const std::string &instructorName, const std::string &courseLocation, const std::string &timeSlot);
        Course();

        int getEnrollmentCapacity() const;
        int getEnrolledStudentCount() const;
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

#endif // INDIVIDUALMINIPROJECTC___INCLUDE_COURSE_H_