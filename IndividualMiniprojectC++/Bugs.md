# Bugs

## Course.cpp
* Constructor: enrolledStudentCount should be 0 when the class being constructed
* enrollStudent: does not check the capcity and always return false
* isCourseFull: the logic should be inverted
* dropStudent: enrolledStudentCount should not less than 0
* getInstructorName: it should return instructorName
* getCourseTimeSlot: it should return courseTimeSlot
* reassignInstructor: delete output. no need to use this-> here 