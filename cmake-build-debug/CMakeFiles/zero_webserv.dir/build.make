# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gernesto/Desktop/webserv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gernesto/Desktop/webserv/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/zero_webserv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/zero_webserv.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/zero_webserv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zero_webserv.dir/flags.make

CMakeFiles/zero_webserv.dir/srcs/main.cpp.o: CMakeFiles/zero_webserv.dir/flags.make
CMakeFiles/zero_webserv.dir/srcs/main.cpp.o: ../srcs/main.cpp
CMakeFiles/zero_webserv.dir/srcs/main.cpp.o: CMakeFiles/zero_webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/zero_webserv.dir/srcs/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zero_webserv.dir/srcs/main.cpp.o -MF CMakeFiles/zero_webserv.dir/srcs/main.cpp.o.d -o CMakeFiles/zero_webserv.dir/srcs/main.cpp.o -c /Users/gernesto/Desktop/webserv/srcs/main.cpp

CMakeFiles/zero_webserv.dir/srcs/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zero_webserv.dir/srcs/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gernesto/Desktop/webserv/srcs/main.cpp > CMakeFiles/zero_webserv.dir/srcs/main.cpp.i

CMakeFiles/zero_webserv.dir/srcs/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zero_webserv.dir/srcs/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gernesto/Desktop/webserv/srcs/main.cpp -o CMakeFiles/zero_webserv.dir/srcs/main.cpp.s

CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o: CMakeFiles/zero_webserv.dir/flags.make
CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o: ../srcs/Utils.cpp
CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o: CMakeFiles/zero_webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o -MF CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o.d -o CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o -c /Users/gernesto/Desktop/webserv/srcs/Utils.cpp

CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gernesto/Desktop/webserv/srcs/Utils.cpp > CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.i

CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gernesto/Desktop/webserv/srcs/Utils.cpp -o CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.s

CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o: CMakeFiles/zero_webserv.dir/flags.make
CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o: ../srcs/Server.cpp
CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o: CMakeFiles/zero_webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o -MF CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o.d -o CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o -c /Users/gernesto/Desktop/webserv/srcs/Server.cpp

CMakeFiles/zero_webserv.dir/srcs/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zero_webserv.dir/srcs/Server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gernesto/Desktop/webserv/srcs/Server.cpp > CMakeFiles/zero_webserv.dir/srcs/Server.cpp.i

CMakeFiles/zero_webserv.dir/srcs/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zero_webserv.dir/srcs/Server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gernesto/Desktop/webserv/srcs/Server.cpp -o CMakeFiles/zero_webserv.dir/srcs/Server.cpp.s

CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o: CMakeFiles/zero_webserv.dir/flags.make
CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o: ../srcs/SimpSocket.cpp
CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o: CMakeFiles/zero_webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o -MF CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o.d -o CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o -c /Users/gernesto/Desktop/webserv/srcs/SimpSocket.cpp

CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gernesto/Desktop/webserv/srcs/SimpSocket.cpp > CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.i

CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gernesto/Desktop/webserv/srcs/SimpSocket.cpp -o CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.s

CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o: CMakeFiles/zero_webserv.dir/flags.make
CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o: ../srcs/Request.cpp
CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o: CMakeFiles/zero_webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o -MF CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o.d -o CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o -c /Users/gernesto/Desktop/webserv/srcs/Request.cpp

CMakeFiles/zero_webserv.dir/srcs/Request.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zero_webserv.dir/srcs/Request.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gernesto/Desktop/webserv/srcs/Request.cpp > CMakeFiles/zero_webserv.dir/srcs/Request.cpp.i

CMakeFiles/zero_webserv.dir/srcs/Request.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zero_webserv.dir/srcs/Request.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gernesto/Desktop/webserv/srcs/Request.cpp -o CMakeFiles/zero_webserv.dir/srcs/Request.cpp.s

CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o: CMakeFiles/zero_webserv.dir/flags.make
CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o: ../srcs/Config.cpp
CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o: CMakeFiles/zero_webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o -MF CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o.d -o CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o -c /Users/gernesto/Desktop/webserv/srcs/Config.cpp

CMakeFiles/zero_webserv.dir/srcs/Config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zero_webserv.dir/srcs/Config.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gernesto/Desktop/webserv/srcs/Config.cpp > CMakeFiles/zero_webserv.dir/srcs/Config.cpp.i

CMakeFiles/zero_webserv.dir/srcs/Config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zero_webserv.dir/srcs/Config.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gernesto/Desktop/webserv/srcs/Config.cpp -o CMakeFiles/zero_webserv.dir/srcs/Config.cpp.s

CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o: CMakeFiles/zero_webserv.dir/flags.make
CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o: ../srcs/Response.cpp
CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o: CMakeFiles/zero_webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o -MF CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o.d -o CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o -c /Users/gernesto/Desktop/webserv/srcs/Response.cpp

CMakeFiles/zero_webserv.dir/srcs/Response.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zero_webserv.dir/srcs/Response.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gernesto/Desktop/webserv/srcs/Response.cpp > CMakeFiles/zero_webserv.dir/srcs/Response.cpp.i

CMakeFiles/zero_webserv.dir/srcs/Response.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zero_webserv.dir/srcs/Response.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gernesto/Desktop/webserv/srcs/Response.cpp -o CMakeFiles/zero_webserv.dir/srcs/Response.cpp.s

# Object files for target zero_webserv
zero_webserv_OBJECTS = \
"CMakeFiles/zero_webserv.dir/srcs/main.cpp.o" \
"CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o" \
"CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o" \
"CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o" \
"CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o" \
"CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o" \
"CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o"

# External object files for target zero_webserv
zero_webserv_EXTERNAL_OBJECTS =

zero_webserv: CMakeFiles/zero_webserv.dir/srcs/main.cpp.o
zero_webserv: CMakeFiles/zero_webserv.dir/srcs/Utils.cpp.o
zero_webserv: CMakeFiles/zero_webserv.dir/srcs/Server.cpp.o
zero_webserv: CMakeFiles/zero_webserv.dir/srcs/SimpSocket.cpp.o
zero_webserv: CMakeFiles/zero_webserv.dir/srcs/Request.cpp.o
zero_webserv: CMakeFiles/zero_webserv.dir/srcs/Config.cpp.o
zero_webserv: CMakeFiles/zero_webserv.dir/srcs/Response.cpp.o
zero_webserv: CMakeFiles/zero_webserv.dir/build.make
zero_webserv: CMakeFiles/zero_webserv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable zero_webserv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zero_webserv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zero_webserv.dir/build: zero_webserv
.PHONY : CMakeFiles/zero_webserv.dir/build

CMakeFiles/zero_webserv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zero_webserv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zero_webserv.dir/clean

CMakeFiles/zero_webserv.dir/depend:
	cd /Users/gernesto/Desktop/webserv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gernesto/Desktop/webserv /Users/gernesto/Desktop/webserv /Users/gernesto/Desktop/webserv/cmake-build-debug /Users/gernesto/Desktop/webserv/cmake-build-debug /Users/gernesto/Desktop/webserv/cmake-build-debug/CMakeFiles/zero_webserv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zero_webserv.dir/depend
