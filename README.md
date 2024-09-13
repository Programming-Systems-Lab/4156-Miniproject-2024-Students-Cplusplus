# Welcome Students of 4156
Please follow the assignment specifications on Courseworks when completing this project.

SETUP:
-   Used cpplint as the style checker tool for Google's C++ standard. After performing "pip install cpplint", I went over to        IndividualMiniProject/src and ran the command cpplint <file_name.cpp> for each of the files I had. 


-   Used clang-tidy as the static analysis tool for my code. I performed "brew install llvm" first, then using one of the links I've
referenced in README, I added the llvm/bin directory location to my PATH in .zshrc (export PATH="/usr/local/opt/llvm/bin:$PATH"). 
This allowed "clang-tidy" to be recognized by the system, and then I proceeded to add
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*;-quiet")
    endif()
to my CMakeLists.txt. Quick side note - I struggled for a while because running clang-tidy manually on my terminal for specific files
worked fine, but it did not seem to change the outputs at all when I tried to build the executable using cmake. It turned out to be
because I did not change any of the source files, so what I had to do was run the command "make clean" and then run "make" again from
the build directory. Usage of clang-tidy drastically slows down the build process, however. Feel free to remove this part from 
CMakeLists when building if you want it to be done faster. 


- Used gcc for coverage analysis
    pip install govr
    brew install gcc
    Navigate to build directory, then:
    cmake -DCMAKE_C_COMPILER=/opt/homebrew/bin/gcc-14 -DCMAKE_CXX_COMPILER=/opt/homebrew/bin/g++-14 ..
    make

    ./IndividualMiniproject setup   (control + c after this command is run)
    ./IndividualMiniprojectTests

    gcovr --root .. \
      --object-directory . \
      --gcov-executable /opt/homebrew/bin/gcov-14 \
      --html --html-details \
      -o coverage.html \
      -v

    open coverage.html

    "rm -rf *" in the build directory for new builds if trying to run code coverage tests again.
    **Keep in mind that my mac is apple silicon, so the installation directories may differ if using an older model.

CODE EXPLANATION:


