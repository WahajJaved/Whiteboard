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
CMAKE_COMMAND = /home/wj/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/wj/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wj/Workspace/FreelanceProjects/Whiteboard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Whiteboard.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Whiteboard.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Whiteboard.dir/flags.make

CMakeFiles/Whiteboard.dir/TCP_Client.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/TCP_Client.c.o: ../TCP_Client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Whiteboard.dir/TCP_Client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/TCP_Client.c.o   -c /home/wj/Workspace/FreelanceProjects/Whiteboard/TCP_Client.c

CMakeFiles/Whiteboard.dir/TCP_Client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/TCP_Client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wj/Workspace/FreelanceProjects/Whiteboard/TCP_Client.c > CMakeFiles/Whiteboard.dir/TCP_Client.c.i

CMakeFiles/Whiteboard.dir/TCP_Client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/TCP_Client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wj/Workspace/FreelanceProjects/Whiteboard/TCP_Client.c -o CMakeFiles/Whiteboard.dir/TCP_Client.c.s

CMakeFiles/Whiteboard.dir/TCP_Server.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/TCP_Server.c.o: ../TCP_Server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Whiteboard.dir/TCP_Server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/TCP_Server.c.o   -c /home/wj/Workspace/FreelanceProjects/Whiteboard/TCP_Server.c

CMakeFiles/Whiteboard.dir/TCP_Server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/TCP_Server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wj/Workspace/FreelanceProjects/Whiteboard/TCP_Server.c > CMakeFiles/Whiteboard.dir/TCP_Server.c.i

CMakeFiles/Whiteboard.dir/TCP_Server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/TCP_Server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wj/Workspace/FreelanceProjects/Whiteboard/TCP_Server.c -o CMakeFiles/Whiteboard.dir/TCP_Server.c.s

# Object files for target Whiteboard
Whiteboard_OBJECTS = \
"CMakeFiles/Whiteboard.dir/TCP_Client.c.o" \
"CMakeFiles/Whiteboard.dir/TCP_Server.c.o"

# External object files for target Whiteboard
Whiteboard_EXTERNAL_OBJECTS =

Whiteboard: CMakeFiles/Whiteboard.dir/TCP_Client.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/TCP_Server.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/build.make
Whiteboard: CMakeFiles/Whiteboard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Whiteboard"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Whiteboard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Whiteboard.dir/build: Whiteboard

.PHONY : CMakeFiles/Whiteboard.dir/build

CMakeFiles/Whiteboard.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Whiteboard.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Whiteboard.dir/clean

CMakeFiles/Whiteboard.dir/depend:
	cd /home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wj/Workspace/FreelanceProjects/Whiteboard /home/wj/Workspace/FreelanceProjects/Whiteboard /home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug /home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug /home/wj/Workspace/FreelanceProjects/Whiteboard/cmake-build-debug/CMakeFiles/Whiteboard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Whiteboard.dir/depend

