# Bugs

## General
* `src/MyApp.cpp` and `src/RouteController.cpp` should be added to `add_executable` in `CMakeLists.txt`

## Course.cpp
1. Remove duplicate `#include <string>`
2. Constructor: Initialize `enrolledStudentCount` to 0
3. `enrollStudent()`: 
   - Add capacity check
   - Fix return value (currently always returns `false`)
4. `isCourseFull()`: Invert the logic
5. `dropStudent()`: Ensure `enrolledStudentCount` doesn't go below 0
6. `getInstructorName()`: Should return `instructorName`
7. `getCourseTimeSlot()`: Should return `courseTimeSlot`
8. `reassignInstructor()`: 
   - Remove `cout` statement
   - Remove unnecessary `this->` usage

## Department.cpp
1. Remove duplicate `#include <map>`
2. Remove duplicate `#include <string>`
3. `getDepartmentChair()`: Return `departmentChair` instead of the string literal `"departmentChair"`
4. `dropPersonFromMajor()`: Ensure `numberOfMajors` doesn't go below 0
