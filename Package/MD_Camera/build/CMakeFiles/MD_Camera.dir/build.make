# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/build

# Include any dependencies generated for this target.
include CMakeFiles/MD_Camera.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MD_Camera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MD_Camera.dir/flags.make

CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.o: CMakeFiles/MD_Camera.dir/flags.make
CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.o: ../src/MD_Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.o -c /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/src/MD_Camera.cpp

CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/src/MD_Camera.cpp > CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.i

CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/src/MD_Camera.cpp -o CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.s

# Object files for target MD_Camera
MD_Camera_OBJECTS = \
"CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.o"

# External object files for target MD_Camera
MD_Camera_EXTERNAL_OBJECTS =

/home/steins_xin/CLionProjects/RM_Detection_install/Dynamic_library/libMD_Camera.so: CMakeFiles/MD_Camera.dir/src/MD_Camera.cpp.o
/home/steins_xin/CLionProjects/RM_Detection_install/Dynamic_library/libMD_Camera.so: CMakeFiles/MD_Camera.dir/build.make
/home/steins_xin/CLionProjects/RM_Detection_install/Dynamic_library/libMD_Camera.so: CMakeFiles/MD_Camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/steins_xin/CLionProjects/RM_Detection_install/Dynamic_library/libMD_Camera.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MD_Camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MD_Camera.dir/build: /home/steins_xin/CLionProjects/RM_Detection_install/Dynamic_library/libMD_Camera.so

.PHONY : CMakeFiles/MD_Camera.dir/build

CMakeFiles/MD_Camera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MD_Camera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MD_Camera.dir/clean

CMakeFiles/MD_Camera.dir/depend:
	cd /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/build /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/build /home/steins_xin/CLionProjects/RM_Detection_install/Package/MD_Camera/build/CMakeFiles/MD_Camera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MD_Camera.dir/depend

