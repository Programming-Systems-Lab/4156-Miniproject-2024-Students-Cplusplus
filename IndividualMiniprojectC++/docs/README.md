# Rough work
Use of CMake - What does it do? 
We were given **CMakeList.txt** file which contains configurations and build steps required to build the project. However, CMake cannot build it. It can merely create a **make file**, which in turn will call the compiler i.e. **g++** (in our case) to compile the project.

Cmake 	------->	    Make           ----------> 	            	g++
	create make file		   calls g++ for multiple files		   Actually compile

Why didn't we use g++ directly to compile?
g++ will compile each file separately hence we needed a tool (Make) to compile the whole project at once (useful for large projects)

We needed cmake and gcc (compiler). For this, we installed a tool called MSYS2 which used "pacman" to install these two. 
Build commands -> "cmake ." (created make files) then "make" (compilation of the project by calling g++)
