# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/corki/eskf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/corki/eskf/build

# Include any dependencies generated for this target.
include CMakeFiles/gps_imu_fusion.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gps_imu_fusion.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gps_imu_fusion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gps_imu_fusion.dir/flags.make

CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o: CMakeFiles/gps_imu_fusion.dir/flags.make
CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o: ../app/gps_imu_fusion.cpp
CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o: CMakeFiles/gps_imu_fusion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corki/eskf/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o -MF CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o.d -o CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o -c /home/corki/eskf/app/gps_imu_fusion.cpp

CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/corki/eskf/app/gps_imu_fusion.cpp > CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.i

CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/corki/eskf/app/gps_imu_fusion.cpp -o CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.s

# Object files for target gps_imu_fusion
gps_imu_fusion_OBJECTS = \
"CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o"

# External object files for target gps_imu_fusion
gps_imu_fusion_EXTERNAL_OBJECTS =

gps_imu_fusion: CMakeFiles/gps_imu_fusion.dir/app/gps_imu_fusion.cpp.o
gps_imu_fusion: CMakeFiles/gps_imu_fusion.dir/build.make
gps_imu_fusion: libDEPS.so
gps_imu_fusion: /usr/lib/x86_64-linux-gnu/libglog.so
gps_imu_fusion: GeographicLib/liblibGeographiccc.so
gps_imu_fusion: CMakeFiles/gps_imu_fusion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/corki/eskf/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gps_imu_fusion"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gps_imu_fusion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gps_imu_fusion.dir/build: gps_imu_fusion
.PHONY : CMakeFiles/gps_imu_fusion.dir/build

CMakeFiles/gps_imu_fusion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gps_imu_fusion.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gps_imu_fusion.dir/clean

CMakeFiles/gps_imu_fusion.dir/depend:
	cd /home/corki/eskf/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/corki/eskf /home/corki/eskf /home/corki/eskf/build /home/corki/eskf/build /home/corki/eskf/build/CMakeFiles/gps_imu_fusion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gps_imu_fusion.dir/depend

