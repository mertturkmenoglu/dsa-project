# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/mert/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mert/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mert/codes/dsa-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mert/codes/dsa-project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/dsa_project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dsa_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dsa_project.dir/flags.make

CMakeFiles/dsa_project.dir/main.c.o: CMakeFiles/dsa_project.dir/flags.make
CMakeFiles/dsa_project.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mert/codes/dsa-project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dsa_project.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dsa_project.dir/main.c.o   -c /home/mert/codes/dsa-project/main.c

CMakeFiles/dsa_project.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dsa_project.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mert/codes/dsa-project/main.c > CMakeFiles/dsa_project.dir/main.c.i

CMakeFiles/dsa_project.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dsa_project.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mert/codes/dsa-project/main.c -o CMakeFiles/dsa_project.dir/main.c.s

# Object files for target dsa_project
dsa_project_OBJECTS = \
"CMakeFiles/dsa_project.dir/main.c.o"

# External object files for target dsa_project
dsa_project_EXTERNAL_OBJECTS =

dsa_project: CMakeFiles/dsa_project.dir/main.c.o
dsa_project: CMakeFiles/dsa_project.dir/build.make
dsa_project: CMakeFiles/dsa_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mert/codes/dsa-project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable dsa_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dsa_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dsa_project.dir/build: dsa_project

.PHONY : CMakeFiles/dsa_project.dir/build

CMakeFiles/dsa_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dsa_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dsa_project.dir/clean

CMakeFiles/dsa_project.dir/depend:
	cd /home/mert/codes/dsa-project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mert/codes/dsa-project /home/mert/codes/dsa-project /home/mert/codes/dsa-project/cmake-build-debug /home/mert/codes/dsa-project/cmake-build-debug /home/mert/codes/dsa-project/cmake-build-debug/CMakeFiles/dsa_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dsa_project.dir/depend

