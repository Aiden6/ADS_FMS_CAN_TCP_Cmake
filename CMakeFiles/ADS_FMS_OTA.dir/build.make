# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/amygo/ADS_FMS_Cmake_CAN_TCP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amygo/ADS_FMS_Cmake_CAN_TCP

# Include any dependencies generated for this target.
include CMakeFiles/ADS_FMS_OTA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ADS_FMS_OTA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ADS_FMS_OTA.dir/flags.make

CMakeFiles/ADS_FMS_OTA.dir/main.cc.o: CMakeFiles/ADS_FMS_OTA.dir/flags.make
CMakeFiles/ADS_FMS_OTA.dir/main.cc.o: main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amygo/ADS_FMS_Cmake_CAN_TCP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ADS_FMS_OTA.dir/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ADS_FMS_OTA.dir/main.cc.o -c /home/amygo/ADS_FMS_Cmake_CAN_TCP/main.cc

CMakeFiles/ADS_FMS_OTA.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ADS_FMS_OTA.dir/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amygo/ADS_FMS_Cmake_CAN_TCP/main.cc > CMakeFiles/ADS_FMS_OTA.dir/main.cc.i

CMakeFiles/ADS_FMS_OTA.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ADS_FMS_OTA.dir/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amygo/ADS_FMS_Cmake_CAN_TCP/main.cc -o CMakeFiles/ADS_FMS_OTA.dir/main.cc.s

CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.requires:

.PHONY : CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.requires

CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.provides: CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/ADS_FMS_OTA.dir/build.make CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.provides

CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.provides.build: CMakeFiles/ADS_FMS_OTA.dir/main.cc.o


# Object files for target ADS_FMS_OTA
ADS_FMS_OTA_OBJECTS = \
"CMakeFiles/ADS_FMS_OTA.dir/main.cc.o"

# External object files for target ADS_FMS_OTA
ADS_FMS_OTA_EXTERNAL_OBJECTS =

ADS_FMS_OTA: CMakeFiles/ADS_FMS_OTA.dir/main.cc.o
ADS_FMS_OTA: CMakeFiles/ADS_FMS_OTA.dir/build.make
ADS_FMS_OTA: lib/libADS_FMS_OTA_LIB.so
ADS_FMS_OTA: CMakeFiles/ADS_FMS_OTA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amygo/ADS_FMS_Cmake_CAN_TCP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ADS_FMS_OTA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ADS_FMS_OTA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ADS_FMS_OTA.dir/build: ADS_FMS_OTA

.PHONY : CMakeFiles/ADS_FMS_OTA.dir/build

CMakeFiles/ADS_FMS_OTA.dir/requires: CMakeFiles/ADS_FMS_OTA.dir/main.cc.o.requires

.PHONY : CMakeFiles/ADS_FMS_OTA.dir/requires

CMakeFiles/ADS_FMS_OTA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ADS_FMS_OTA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ADS_FMS_OTA.dir/clean

CMakeFiles/ADS_FMS_OTA.dir/depend:
	cd /home/amygo/ADS_FMS_Cmake_CAN_TCP && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amygo/ADS_FMS_Cmake_CAN_TCP /home/amygo/ADS_FMS_Cmake_CAN_TCP /home/amygo/ADS_FMS_Cmake_CAN_TCP /home/amygo/ADS_FMS_Cmake_CAN_TCP /home/amygo/ADS_FMS_Cmake_CAN_TCP/CMakeFiles/ADS_FMS_OTA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ADS_FMS_OTA.dir/depend

