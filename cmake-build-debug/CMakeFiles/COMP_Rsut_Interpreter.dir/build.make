# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/88/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/88/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/COMP_Rsut_Interpreter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/COMP_Rsut_Interpreter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/COMP_Rsut_Interpreter.dir/flags.make

CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.o: CMakeFiles/COMP_Rsut_Interpreter.dir/flags.make
CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.o   -c /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/main.c

CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/main.c > CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.i

CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/main.c -o CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.s

# Object files for target COMP_Rsut_Interpreter
COMP_Rsut_Interpreter_OBJECTS = \
"CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.o"

# External object files for target COMP_Rsut_Interpreter
COMP_Rsut_Interpreter_EXTERNAL_OBJECTS =

COMP_Rsut_Interpreter: CMakeFiles/COMP_Rsut_Interpreter.dir/main.c.o
COMP_Rsut_Interpreter: CMakeFiles/COMP_Rsut_Interpreter.dir/build.make
COMP_Rsut_Interpreter: CMakeFiles/COMP_Rsut_Interpreter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable COMP_Rsut_Interpreter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/COMP_Rsut_Interpreter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/COMP_Rsut_Interpreter.dir/build: COMP_Rsut_Interpreter

.PHONY : CMakeFiles/COMP_Rsut_Interpreter.dir/build

CMakeFiles/COMP_Rsut_Interpreter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/COMP_Rsut_Interpreter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/COMP_Rsut_Interpreter.dir/clean

CMakeFiles/COMP_Rsut_Interpreter.dir/depend:
	cd /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/cmake-build-debug /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/cmake-build-debug /home/pedro/Documents/CLionProjects/COMP_Rsut_Interpreter/cmake-build-debug/CMakeFiles/COMP_Rsut_Interpreter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/COMP_Rsut_Interpreter.dir/depend

