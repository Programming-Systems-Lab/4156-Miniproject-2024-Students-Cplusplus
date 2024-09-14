cmake_minimum_required(VERSION 3.15)

project(IndividualMiniproject)

set(INCLUDE_PATHS external_libraries/boost_1_86_0 external_libraries/Crow-1.2.0-Darwin/include)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main project executable
add_executable(IndividualMiniproject 
    src/main.cpp 
    src/Course.cpp 
    src/Department.cpp 
    src/MyFileDatabase.cpp 
    src/RouteController.cpp
    src/MyApp.cpp
    src/Globals.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/ff233bdd4cac0a0bf6e5cd45bda3406814cb2796.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

# Include directories for main executable
target_include_directories(IndividualMiniproject PUBLIC 
    ${INCLUDE_PATHS} 
    include
#    /opt/homebrew/Cellar/asio/1.30.2/include
)

target_link_libraries(IndividualMiniproject PRIVATE 
    gtest 
    gtest_main
)

enable_testing()

# Test executable
add_executable(IndividualMiniprojectTests
  test/sample.cpp
  test/CourseUnitTests.cpp
  test/DepartmentUnitTests.cpp
  test/RouteControllerUnitTests.cpp
  src/Course.cpp
  src/Department.cpp
  src/MyFileDatabase.cpp
  src/RouteController.cpp
  src/MyApp.cpp
)

target_include_directories(IndividualMiniprojectTests PRIVATE 
    ${INCLUDE_PATHS} 
    include
#    /opt/homebrew/Cellar/asio/1.30.2/include
)

target_link_libraries(IndividualMiniprojectTests PRIVATE 
    gtest 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(IndividualMiniprojectTests)

# Find the cpplint program
find_program(CPPLINT cpplint)

if (CPPLINT)
    # List of source files to be checked by cpplint
    set(SOURCE_FILES
        src/main.cpp 
        src/Course.cpp 
        src/Department.cpp 
        src/MyFileDatabase.cpp 
        src/RouteController.cpp
        src/MyApp.cpp
        src/Globals.cpp
        test/sample.cpp
        test/CourseUnitTests.cpp
        test/DepartmentUnitTests.cpp
        test/RouteControllerUnitTests.cpp
    )

    # Custom target to run cpplint
    add_custom_target(
        cpplint
        COMMAND ${CPPLINT} --filter=-whitespace,-build/include_what_you_use ${SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cpplint for Google C++ Style Guide compliance"
    )
else()
    message(WARNING "cpplint not found! Skipping style checks.")
endif()

if (ENABLE_COVERAGE)
    # set comiler flags
    set(CMAKE_CXX_FLAGS "-O0 -coverage")

    # find required tools
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)

    # add coverage target
    add_custom_target(
        coverage
        # gather data
        COMMAND ${LCOV} --directory . --capture --output-file coverage.info
        # exclude header files
        COMMAND ${LCOV} --remove coverage.info '/usr/*' '*.h' '*main.cpp' '*test*' --output-file coverage.info
        COMMAND ${LCOV} --remove coverage.info '*MyApp.cpp' --output-file coverage.info
        # generate report
        COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

add_executable(CodeCoverage
  test/sample.cpp
  test/CourseUnitTests.cpp
  test/DepartmentUnitTests.cpp
  test/MyFileDatabaseUnitTests.cpp
  test/RouteControllerUnitTests.cpp
  src/Course.cpp
  src/Department.cpp
  src/MyFileDatabase.cpp
  src/RouteController.cpp
  src/MyApp.cpp
)

target_include_directories(CodeCoverage PRIVATE
    ${INCLUDE_PATHS}
    include
)

target_link_libraries(CodeCoverage PRIVATE
    gtest
    gtest_main
)

find_program(CPPCHECK cppcheck)
add_custom_target(
    cppcheck
    #COMMAND ${CPPCHECK} -I ../include/ --enable=all --inconclusive --library=posix --suppress=missingInclude --suppress=missingIncludeSystem --suppress=checkersReport --suppress=unusedFunction ../src/ ../test/
    COMMAND ${CPPCHECK} -I ../include/ --enable=all --library=posix --suppress=missingInclude --suppress=missingIncludeSystem --suppress=checkersReport --suppress=unusedFunction ../src/ ../test/
)
