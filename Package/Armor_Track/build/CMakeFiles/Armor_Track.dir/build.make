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
CMAKE_SOURCE_DIR = /home/hj/2024/RM_Detection_recode/Package/Armor_Track

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hj/2024/RM_Detection_recode/Package/Armor_Track/build

# Include any dependencies generated for this target.
include CMakeFiles/Armor_Track.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Armor_Track.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Armor_Track.dir/flags.make

CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.o: CMakeFiles/Armor_Track.dir/flags.make
CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.o: ../src/Armor_Track.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/2024/RM_Detection_recode/Package/Armor_Track/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.o -c /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/Armor_Track.cpp

CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/Armor_Track.cpp > CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.i

CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/Armor_Track.cpp -o CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.s

CMakeFiles/Armor_Track.dir/src/Kalman.cpp.o: CMakeFiles/Armor_Track.dir/flags.make
CMakeFiles/Armor_Track.dir/src/Kalman.cpp.o: ../src/Kalman.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/2024/RM_Detection_recode/Package/Armor_Track/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Armor_Track.dir/src/Kalman.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Armor_Track.dir/src/Kalman.cpp.o -c /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/Kalman.cpp

CMakeFiles/Armor_Track.dir/src/Kalman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Armor_Track.dir/src/Kalman.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/Kalman.cpp > CMakeFiles/Armor_Track.dir/src/Kalman.cpp.i

CMakeFiles/Armor_Track.dir/src/Kalman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Armor_Track.dir/src/Kalman.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/Kalman.cpp -o CMakeFiles/Armor_Track.dir/src/Kalman.cpp.s

CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.o: CMakeFiles/Armor_Track.dir/flags.make
CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.o: ../src/SpinTracker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/2024/RM_Detection_recode/Package/Armor_Track/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.o -c /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/SpinTracker.cpp

CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/SpinTracker.cpp > CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.i

CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/2024/RM_Detection_recode/Package/Armor_Track/src/SpinTracker.cpp -o CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.s

# Object files for target Armor_Track
Armor_Track_OBJECTS = \
"CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.o" \
"CMakeFiles/Armor_Track.dir/src/Kalman.cpp.o" \
"CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.o"

# External object files for target Armor_Track
Armor_Track_EXTERNAL_OBJECTS =

/home/hj/2024/RM_Detection_recode/Dynamic_library/libArmor_Track.so: CMakeFiles/Armor_Track.dir/src/Armor_Track.cpp.o
/home/hj/2024/RM_Detection_recode/Dynamic_library/libArmor_Track.so: CMakeFiles/Armor_Track.dir/src/Kalman.cpp.o
/home/hj/2024/RM_Detection_recode/Dynamic_library/libArmor_Track.so: CMakeFiles/Armor_Track.dir/src/SpinTracker.cpp.o
/home/hj/2024/RM_Detection_recode/Dynamic_library/libArmor_Track.so: CMakeFiles/Armor_Track.dir/build.make
/home/hj/2024/RM_Detection_recode/Dynamic_library/libArmor_Track.so: CMakeFiles/Armor_Track.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hj/2024/RM_Detection_recode/Package/Armor_Track/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library /home/hj/2024/RM_Detection_recode/Dynamic_library/libArmor_Track.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Armor_Track.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Armor_Track.dir/build: /home/hj/2024/RM_Detection_recode/Dynamic_library/libArmor_Track.so

.PHONY : CMakeFiles/Armor_Track.dir/build

CMakeFiles/Armor_Track.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Armor_Track.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Armor_Track.dir/clean

CMakeFiles/Armor_Track.dir/depend:
	cd /home/hj/2024/RM_Detection_recode/Package/Armor_Track/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hj/2024/RM_Detection_recode/Package/Armor_Track /home/hj/2024/RM_Detection_recode/Package/Armor_Track /home/hj/2024/RM_Detection_recode/Package/Armor_Track/build /home/hj/2024/RM_Detection_recode/Package/Armor_Track/build /home/hj/2024/RM_Detection_recode/Package/Armor_Track/build/CMakeFiles/Armor_Track.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Armor_Track.dir/depend

