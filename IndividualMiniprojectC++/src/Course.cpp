// Copyright 2024 Chun-Yao Hsieh @ Columbia University. All rights reserved.
#include "Course.h"
#include <iostream>

/**
 * Constructs a new Course object with the given parameters. Initial count starts at 0.
 *
 * @param instructorName     The name of the instructor teaching the course.
 * @param courseLocation     The location where the course is held.
 * @param timeSlot           The time slot of the course.
 * @param capacity           The maximum number of students that can enroll in the course.
 */
Course::Course(int capacity, const std::string &instructorName, const std::string &courseLocation, const std::string &timeSlot)
    : enrollmentCapacity(capacity), enrolledStudentCount(0), courseLocation(courseLocation), instructorName(instructorName), courseTimeSlot(timeSlot) {}

/**
 * Constructs a default Course object with the default parameters.
 *
 */
Course::Course() : enrollmentCapacity(0), enrolledStudentCount(0), courseLocation(""), instructorName(""), courseTimeSlot("") {}

/**
 * Enrolls a student in the course if there is space available.
 *
 * @return true if the student is successfully enrolled, false otherwise.
 */
bool Course::enrollStudent()
{
    if (!isCourseFull())
    {
        enrolledStudentCount++;
        return true;
    }
    return false;
}

/**
 * Drops a student from the course if a student is enrolled.
 *
 * @return true if the student is successfully dropped, false otherwise.
 */
bool Course::dropStudent()
{
    if (enrolledStudentCount > 0)
    {
        enrolledStudentCount--;
        return true;
    }
    return false;
}

int Course::getEnrolledStudentCount() const
{
    return enrolledStudentCount;
}

int Course::getEnrollmentCapacity() const
{
    return enrollmentCapacity;
}

std::string Course::getCourseLocation() const
{
    return courseLocation;
}

std::string Course::getInstructorName() const
{
    return instructorName;
}

std::string Course::getCourseTimeSlot() const
{
    return courseTimeSlot;
}

std::string Course::display() const
{
    return "\nInstructor: " + instructorName + "; Location: " + courseLocation + "; Time: " + courseTimeSlot;}

void Course::reassignInstructor(const std::string &newInstructorName)
{
    instructorName = newInstructorName;
}

void Course::reassignLocation(const std::string &newLocation)
{
    courseLocation = newLocation;
}

void Course::reassignTime(const std::string &newTime)
{
    courseTimeSlot = newTime;
}

void Course::setEnrolledStudentCount(int count)
{
    enrolledStudentCount = count;
}

bool Course::isCourseFull() const
{
    return enrollmentCapacity <= enrolledStudentCount;
}

void Course::serialize(std::ostream &out) const
{
    out.write(reinterpret_cast<const char *>(&enrollmentCapacity), sizeof(enrollmentCapacity));
    out.write(reinterpret_cast<const char *>(&enrolledStudentCount), sizeof(enrolledStudentCount));

    size_t locationLen = courseLocation.length();
    out.write(reinterpret_cast<const char *>(&locationLen), sizeof(locationLen));
    out.write(courseLocation.c_str(), locationLen);

    size_t instructorLen = instructorName.length();
    out.write(reinterpret_cast<const char *>(&instructorLen), sizeof(instructorLen));
    out.write(instructorName.c_str(), instructorLen);

    size_t timeSlotLen = courseTimeSlot.length();
    out.write(reinterpret_cast<const char *>(&timeSlotLen), sizeof(timeSlotLen));
    out.write(courseTimeSlot.c_str(), timeSlotLen);
}

void Course::deserialize(std::istream &in)
{
    in.read(reinterpret_cast<char *>(&enrollmentCapacity), sizeof(enrollmentCapacity));
    in.read(reinterpret_cast<char *>(&enrolledStudentCount), sizeof(enrolledStudentCount));

    size_t locationLen;
    in.read(reinterpret_cast<char *>(&locationLen), sizeof(locationLen));
    courseLocation.resize(locationLen);
    in.read(&courseLocation[0], locationLen);

    size_t instructorLen;
    in.read(reinterpret_cast<char *>(&instructorLen), sizeof(instructorLen));
    instructorName.resize(instructorLen);
    in.read(&instructorName[0], instructorLen);

    size_t timeSlotLen;
    in.read(reinterpret_cast<char *>(&timeSlotLen), sizeof(timeSlotLen));
    courseTimeSlot.resize(timeSlotLen);
    in.read(&courseTimeSlot[0], timeSlotLen);
}
