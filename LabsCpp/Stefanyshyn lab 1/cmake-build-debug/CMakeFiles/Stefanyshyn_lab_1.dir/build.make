# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Stefanyshyn_lab_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Stefanyshyn_lab_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Stefanyshyn_lab_1.dir/flags.make

CMakeFiles/Stefanyshyn_lab_1.dir/main.c.obj: CMakeFiles/Stefanyshyn_lab_1.dir/flags.make
CMakeFiles/Stefanyshyn_lab_1.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Stefanyshyn_lab_1.dir/main.c.obj"
	C:\Users\Jul\Documents\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Stefanyshyn_lab_1.dir\main.c.obj   -c "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\main.c"

CMakeFiles/Stefanyshyn_lab_1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Stefanyshyn_lab_1.dir/main.c.i"
	C:\Users\Jul\Documents\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\main.c" > CMakeFiles\Stefanyshyn_lab_1.dir\main.c.i

CMakeFiles/Stefanyshyn_lab_1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Stefanyshyn_lab_1.dir/main.c.s"
	C:\Users\Jul\Documents\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\main.c" -o CMakeFiles\Stefanyshyn_lab_1.dir\main.c.s

# Object files for target Stefanyshyn_lab_1
Stefanyshyn_lab_1_OBJECTS = \
"CMakeFiles/Stefanyshyn_lab_1.dir/main.c.obj"

# External object files for target Stefanyshyn_lab_1
Stefanyshyn_lab_1_EXTERNAL_OBJECTS =

Stefanyshyn_lab_1.exe: CMakeFiles/Stefanyshyn_lab_1.dir/main.c.obj
Stefanyshyn_lab_1.exe: CMakeFiles/Stefanyshyn_lab_1.dir/build.make
Stefanyshyn_lab_1.exe: CMakeFiles/Stefanyshyn_lab_1.dir/linklibs.rsp
Stefanyshyn_lab_1.exe: CMakeFiles/Stefanyshyn_lab_1.dir/objects1.rsp
Stefanyshyn_lab_1.exe: CMakeFiles/Stefanyshyn_lab_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Stefanyshyn_lab_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Stefanyshyn_lab_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Stefanyshyn_lab_1.dir/build: Stefanyshyn_lab_1.exe

.PHONY : CMakeFiles/Stefanyshyn_lab_1.dir/build

CMakeFiles/Stefanyshyn_lab_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Stefanyshyn_lab_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Stefanyshyn_lab_1.dir/clean

CMakeFiles/Stefanyshyn_lab_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1" "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1" "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\cmake-build-debug" "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\cmake-build-debug" "C:\Users\Jul\CLionProjects\Stefanyshyn lab 1\cmake-build-debug\CMakeFiles\Stefanyshyn_lab_1.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Stefanyshyn_lab_1.dir/depend

