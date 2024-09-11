#!/usr/bin/sudo /bin/bash

set -e  # Exit immediately if a command exits with a non-zero status.

# Function to display usage information
usage() {
    echo "Usage: $0 [BASE_PATH]"
    echo "If BASE_PATH is not provided, the default path will be used."
    exit 1
}

# Check if help is requested
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    usage
fi

# Set BASE_PATH
BASE_PATH="${1:-$HOME/4156-Miniproject-2024-Students-Cplusplus/IndividualMiniprojectC++}"

# Define directories
BUILD_DIR="$BASE_PATH/build"
SRC_DIR="$BUILD_DIR/CMakeFiles/IndividualMiniprojectTests.dir/src"
TEST_DIR="$BUILD_DIR/CMakeFiles/IndividualMiniprojectTests.dir/test"
COVERAGE_DIR="$SRC_DIR/code_coverage"


# # Clean up
find "$SRC_DIR" "$TEST_DIR" "$BUILD_DIR" \
     -type f \( -name '*.o' -o -name '*.gcno' -o -name '*.gcov' -o -name '*.gcda' -o -name '*.info' \) \
     -delete

# Compile the project
make -C "$BUILD_DIR" || { echo "Compilation failed"; exit 1; }

# Run tests
"$BUILD_DIR/IndividualMiniprojectTests" || { echo "Tests failed"; exit 1; }

# Change to the source directory before running gcov
cd "$SRC_DIR" || { echo "Failed to change to source directory"; exit 1; }

# Run gcov
gcov ./*.cpp.gcno

# Return to the original directory
cd - || { echo "Failed to return to original directory"; exit 1; }

# Run lcov and generate coverage info
lcov --capture \
     --directory "$BASE_PATH" \
     --output-file "$BUILD_DIR/coverage.info" \
     --filter range \
     --ignore-errors inconsistent,empty,unused,path \
     --include "$BASE_PATH/src/*" \
     --exclude "$BASE_PATH/include/*" \

# Generate HTML report
genhtml --filter range \
        --ignore-errors inconsistent \
        "$BUILD_DIR/coverage.info" \
        --output-directory "$COVERAGE_DIR"

# Open the coverage report
if command -v xdg-open &> /dev/null; then
    xdg-open "$COVERAGE_DIR/src/index.html"
elif command -v open &> /dev/null; then
    open "$COVERAGE_DIR/src/index.html"
else
    echo "Coverage report generated at $COVERAGE_DIR/src/index.html"
fi

# # Clean up
find "$SRC_DIR" "$TEST_DIR" "$BUILD_DIR" \
     -type f \( -name '*.o' -o -name '*.gcno' -o -name '*.gcov' -o -name '*.gcda' -o -name '*.info' \) \
     -delete

echo "Coverage analysis complete. Results saved in $BUILD_DIR/coverage.info"