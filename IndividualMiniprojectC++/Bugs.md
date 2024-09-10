# Bugs

## Course.cpp
* #include <string>: Duplicate include
* Constructor: enrolledStudentCount should be 0 when the class being constructed
* enrollStudent: does not check the capcity and always return false
* isCourseFull: the logic should be inverted
* dropStudent: enrolledStudentCount should not less than 0
* getInstructorName: it should return instructorName
* getCourseTimeSlot: it should return courseTimeSlot
* reassignInstructor: delete output. no need to use this-> here

## Department.cpp
* #include <map>: Duplicate include
* #include <string>: Duplicate include
* getDepartmentChair: Should return departmentChair not string "departmentChair"
* dropPersonFromMajor: Should make sure numberOfMajors no less than 0