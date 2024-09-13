cmake_minimum_required(VERSION 3.15)

project(IndividualMiniproject)

set(CMAKE_OSX_DEPLOYMENT_TARGET "13.6")
set(INCLUDE_PATHS external_libraries/boost_1_86_0 external_libraries/Crow/include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)


#clang-tidy (remove this and the if conditional directly below if you don't want to use clang-tidy)
find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
#if(CLANG_TIDY_EXE)
    #set(CMAKE_CXX_CLANG_TIDY"${CLANG_TIDY_EXE};-checks=-*,modernize-*,performance-*;-header-filter=^${CMAKE_SOURCE_DIR}/src/.*")
#endif()

# Code coverage
set(CMAKE_BUILD_TYPE Debug)  # Ensure debug build for coverage

# Use GCC for coverage
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("Using GCC for code coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()



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

#clang-tidy
set_target_properties(IndividualMiniproject PROPERTIES
    CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=clang-analyzer-*,bugprone-*;-header-filter=^${CMAKE_SOURCE_DIR}/src/.*"
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
    /opt/homebrew/Cellar/asio/1.30.2/include
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
  src/Course.cpp
  src/Department.cpp
  src/MyFileDatabase.cpp
)

target_include_directories(IndividualMiniprojectTests PRIVATE 
    ${INCLUDE_PATHS} 
    include
    /opt/homebrew/Cellar/asio/1.30.2/include
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
