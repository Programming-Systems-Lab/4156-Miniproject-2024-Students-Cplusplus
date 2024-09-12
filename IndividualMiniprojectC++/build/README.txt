To build the project change your present working directory to this directory and then run the following commands:

cmake .. 
make 
make cpplint -for style checking

If you ever need to clean up some files make clean is always an option

LCOV: Code coverage:
The code coverage library requires lcov and genhtml.

Do these in the build directory:

cmake -DENABLE_COVERAGE=true .. && make
./CodeCoverage;  make coverage

The first command builds the targets and executables,
the second one generates the report in build/coverage/index.html
that can be viewed in a browser.

