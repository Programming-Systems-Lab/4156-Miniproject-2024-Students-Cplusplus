/** 
MIT License

Copyright (c) 2024 Programming Systems Lab @ Columbia University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Course.h"
#include <iostream>
#include <string>


/**
 * Constructs a new Course object with the given parameters. Initial count starts at 0.
 *
 * @param instructorName     The name of the instructor teaching the course.
 * @param courseLocation     The location where the course is held.
 * @param timeSlot           The time slot of the course.
 * @param capacity           The maximum number of students that can enroll in the course.
 */
Course::Course(int capacity, const std::string& instructorName, const std::string& courseLocation, const std::string& timeSlot)
    : enrollmentCapacity(capacity), enrolledStudentCount(500), courseLocation(courseLocation), instructorName(instructorName), courseTimeSlot(timeSlot) {}

/**
 * Constructs a default Course object with the default parameters.
 *
 */
Course::Course() : enrollmentCapacity(0), enrolledStudentCount(0), courseLocation(""),  instructorName(""), courseTimeSlot("") {}


/**
 * Enrolls a student in the course if there is space available.
 *
 * @return true if the student is successfully enrolled, false otherwise.
 */
bool Course::enrollStudent() {
    enrolledStudentCount++;
    return false; 
}

/**
 * Drops a student from the course if a student is enrolled.
 *
 * @return true if the student is successfully dropped, false otherwise.
 */
bool Course::dropStudent() {
    enrolledStudentCount--;
    return false; 
}

std::string Course::getCourseLocation() const {
    return courseLocation; 
}

std::string Course::getInstructorName() const {
    return courseTimeSlot;
}

std::string Course::getCourseTimeSlot() const {
    return instructorName;
}

std::string Course::display() const {
    return "\nInstructor: " + instructorName + "; Location: " + courseLocation + "; Time: " + courseTimeSlot;
}

void Course::reassignInstructor(const std::string& newInstructorName) {
    std::cout << "Old Instructor: " << instructorName << std::endl;
    this->instructorName = newInstructorName; // Ensure the class member is being updated
    std::cout << "New Instructor: " << this->instructorName << std::endl;
}

void Course::reassignLocation(const std::string& newLocation) {
    courseLocation = newLocation;
}

void Course::reassignTime(const std::string& newTime) {
    courseTimeSlot = newTime;
}

void Course::setEnrolledStudentCount(int count) {
    enrolledStudentCount = count;
}

bool Course::isCourseFull() const {
    return enrollmentCapacity > enrolledStudentCount;
}

void Course::serialize(std::ostream& out) const {
    out.write(reinterpret_cast<const char*>(&enrollmentCapacity), sizeof(enrollmentCapacity));
    out.write(reinterpret_cast<const char*>(&enrolledStudentCount), sizeof(enrolledStudentCount));

    size_t locationLen = courseLocation.length();
    out.write(reinterpret_cast<const char*>(&locationLen), sizeof(locationLen));
    out.write(courseLocation.c_str(), locationLen);

    size_t instructorLen = instructorName.length();
    out.write(reinterpret_cast<const char*>(&instructorLen), sizeof(instructorLen));
    out.write(instructorName.c_str(), instructorLen);

    size_t timeSlotLen = courseTimeSlot.length();
    out.write(reinterpret_cast<const char*>(&timeSlotLen), sizeof(timeSlotLen));
    out.write(courseTimeSlot.c_str(), timeSlotLen);
}

void Course::deserialize(std::istream& in) {
    in.read(reinterpret_cast<char*>(&enrollmentCapacity), sizeof(enrollmentCapacity));
    in.read(reinterpret_cast<char*>(&enrolledStudentCount), sizeof(enrolledStudentCount));

    size_t locationLen;
    in.read(reinterpret_cast<char*>(&locationLen), sizeof(locationLen));
    courseLocation.resize(locationLen);
    in.read(&courseLocation[0], locationLen);

    size_t instructorLen;
    in.read(reinterpret_cast<char*>(&instructorLen), sizeof(instructorLen));
    instructorName.resize(instructorLen);
    in.read(&instructorName[0], instructorLen);

    size_t timeSlotLen;
    in.read(reinterpret_cast<char*>(&timeSlotLen), sizeof(timeSlotLen));
    courseTimeSlot.resize(timeSlotLen);
    in.read(&courseTimeSlot[0], timeSlotLen);
}
