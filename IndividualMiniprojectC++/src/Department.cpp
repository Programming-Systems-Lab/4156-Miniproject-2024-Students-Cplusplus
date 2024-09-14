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

#include "Department.h"
#include "Course.h"
#include <map>
#include <string>
#include <sstream>
#include <memory>


/**
 * Constructs a new Department object with the given parameters.
 *
 * @param deptCode         The code of the department.
 * @param courses          A HashMap containing courses offered by the department.
 * @param departmentChair  The name of the department chair.
 * @param numberOfMajors   The number of majors in the department.
 */
Department::Department(std::string departmentCode, std::map<std::string, std::shared_ptr<Course>> coursesList,
                std::string departmentChairName, int majorCount)
    : departmentChair(departmentChairName), deptCode(departmentCode), numberOfMajors(majorCount), courses(coursesList) {}

Department::Department() : numberOfMajors(0) {}

/**
 * Gets the number of majors in the department.
 *
 * @return The number of majors.
 */
int Department::getNumberOfMajors() const {
    return numberOfMajors;
}

/**
 * Gets the name of the department chair.
 *
 * @return The name of the department chair.
 */
std::string Department::getDepartmentChair() const {
    return departmentChair; 
}

/**
 * Gets the courses offered by the department.
 *
 * @return A HashMap containing courses offered by the department.
 */
std::map<std::string, std::shared_ptr<Course>> Department::getCourseSelection() const {
    return courses;
}

/**
 * Increases the number of majors in the department by one.
 */
void Department::increaseNumOfMajor() {
    numberOfMajors++;
}

/**
 * Decreases the number of majors in the department by one if it's greater than zero.
 */
void Department::decreaseNumOfMajor() {
    numberOfMajors--;
}

/**
 * Adds a new course to the department's course selection. Return if
 * the a course with the same ID exists.
 *
 * @param courseId The ID of the course to add.
 * @param course   The Course object to add.
 */
void Department::addCourse(std::string courseId, std::shared_ptr<Course> course) {
    if (courses.find(courseId) == courses.end()){
        return;
    }
    courses[courseId] = course;
}

/**
 * Creates and adds a new course to the department's course selection.
 *
 * @param courseId           The ID of the new course.
 * @param instructorName     The name of the instructor teaching the course.
 * @param courseLocation     The location where the course is held.
 * @param courseTimeSlot     The time slot of the course.
 * @param capacity           The maximum number of students that can enroll in the course.
 */
void Department::createCourse(std::string courseId, std::string instructorName, std::string courseLocation,
                              std::string courseTimeSlot, int capacity) {
    std::shared_ptr<Course> newCourse = std::make_shared<Course>(capacity, instructorName, courseLocation, courseTimeSlot);
    addCourse(courseId, newCourse);
}

/**
 * Returns a string representation of the department, including its code and the courses offered.
 *
 * @return A string representing the department.
 */
std::string Department::display() const {
    std::ostringstream result;
    for (const auto& it : courses) {
        result << deptCode << " " << it.first << ": " << it.second->display() << "\n";
    }
    return result.str(); 
}

void Department::serialize(std::ostream& out) const {
    size_t deptCodeLen = deptCode.length();
    out.write(reinterpret_cast<const char*>(&deptCodeLen), sizeof(deptCodeLen));
    out.write(deptCode.c_str(), deptCodeLen);

    size_t chairLen = departmentChair.length();
    out.write(reinterpret_cast<const char*>(&chairLen), sizeof(chairLen));
    out.write(departmentChair.c_str(), chairLen);

    out.write(reinterpret_cast<const char*>(&numberOfMajors), sizeof(numberOfMajors));

    size_t mapSize = courses.size();
    out.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));
    for (const auto& it : courses) {
        size_t courseIdLen = it.first.length();
        out.write(reinterpret_cast<const char*>(&courseIdLen), sizeof(courseIdLen));
        out.write(it.first.c_str(), courseIdLen);
        it.second->serialize(out);
    }
}

void Department::deserialize(std::istream& in) {
    size_t deptCodeLen;
    in.read(reinterpret_cast<char*>(&deptCodeLen), sizeof(deptCodeLen));
    deptCode.resize(deptCodeLen);
    in.read(&deptCode[0], deptCodeLen);

    size_t chairLen;
    in.read(reinterpret_cast<char*>(&chairLen), sizeof(chairLen));
    departmentChair.resize(chairLen);
    in.read(&departmentChair[0], chairLen);

    in.read(reinterpret_cast<char*>(&numberOfMajors), sizeof(numberOfMajors));

    size_t mapSize;
    in.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
    for (size_t i = 0; i < mapSize; ++i) {
        size_t courseIdLen;
        in.read(reinterpret_cast<char*>(&courseIdLen), sizeof(courseIdLen));
        std::string courseId(courseIdLen, ' ');
        in.read(&courseId[0], courseIdLen);
        std::shared_ptr<Course> course = std::make_shared<Course>();
        course->deserialize(in);
        courses[courseId] = course;
    }
}
