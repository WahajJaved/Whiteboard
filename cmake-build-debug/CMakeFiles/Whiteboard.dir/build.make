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
CMAKE_COMMAND = /home/mani/snap/CLion-2019.3.2/clion-2019.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mani/snap/CLion-2019.3.2/clion-2019.3.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mani/Workspace/SideProject/Fiv/Whiteboard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Whiteboard.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Whiteboard.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Whiteboard.dir/flags.make

CMakeFiles/Whiteboard.dir/TCP_Client.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/TCP_Client.c.o: ../TCP_Client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Whiteboard.dir/TCP_Client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/TCP_Client.c.o   -c /home/mani/Workspace/SideProject/Fiv/Whiteboard/TCP_Client.c

CMakeFiles/Whiteboard.dir/TCP_Client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/TCP_Client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mani/Workspace/SideProject/Fiv/Whiteboard/TCP_Client.c > CMakeFiles/Whiteboard.dir/TCP_Client.c.i

CMakeFiles/Whiteboard.dir/TCP_Client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/TCP_Client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mani/Workspace/SideProject/Fiv/Whiteboard/TCP_Client.c -o CMakeFiles/Whiteboard.dir/TCP_Client.c.s

CMakeFiles/Whiteboard.dir/TCP_Server.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/TCP_Server.c.o: ../TCP_Server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Whiteboard.dir/TCP_Server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/TCP_Server.c.o   -c /home/mani/Workspace/SideProject/Fiv/Whiteboard/TCP_Server.c

CMakeFiles/Whiteboard.dir/TCP_Server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/TCP_Server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mani/Workspace/SideProject/Fiv/Whiteboard/TCP_Server.c > CMakeFiles/Whiteboard.dir/TCP_Server.c.i

CMakeFiles/Whiteboard.dir/TCP_Server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/TCP_Server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mani/Workspace/SideProject/Fiv/Whiteboard/TCP_Server.c -o CMakeFiles/Whiteboard.dir/TCP_Server.c.s

CMakeFiles/Whiteboard.dir/Whiteboard.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/Whiteboard.c.o: ../Whiteboard.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Whiteboard.dir/Whiteboard.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/Whiteboard.c.o   -c /home/mani/Workspace/SideProject/Fiv/Whiteboard/Whiteboard.c

CMakeFiles/Whiteboard.dir/Whiteboard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/Whiteboard.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mani/Workspace/SideProject/Fiv/Whiteboard/Whiteboard.c > CMakeFiles/Whiteboard.dir/Whiteboard.c.i

CMakeFiles/Whiteboard.dir/Whiteboard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/Whiteboard.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mani/Workspace/SideProject/Fiv/Whiteboard/Whiteboard.c -o CMakeFiles/Whiteboard.dir/Whiteboard.c.s

CMakeFiles/Whiteboard.dir/User.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/User.c.o: ../User.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Whiteboard.dir/User.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/User.c.o   -c /home/mani/Workspace/SideProject/Fiv/Whiteboard/User.c

CMakeFiles/Whiteboard.dir/User.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/User.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mani/Workspace/SideProject/Fiv/Whiteboard/User.c > CMakeFiles/Whiteboard.dir/User.c.i

CMakeFiles/Whiteboard.dir/User.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/User.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mani/Workspace/SideProject/Fiv/Whiteboard/User.c -o CMakeFiles/Whiteboard.dir/User.c.s

CMakeFiles/Whiteboard.dir/Topic.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/Topic.c.o: ../Topic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Whiteboard.dir/Topic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/Topic.c.o   -c /home/mani/Workspace/SideProject/Fiv/Whiteboard/Topic.c

CMakeFiles/Whiteboard.dir/Topic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/Topic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mani/Workspace/SideProject/Fiv/Whiteboard/Topic.c > CMakeFiles/Whiteboard.dir/Topic.c.i

CMakeFiles/Whiteboard.dir/Topic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/Topic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mani/Workspace/SideProject/Fiv/Whiteboard/Topic.c -o CMakeFiles/Whiteboard.dir/Topic.c.s

CMakeFiles/Whiteboard.dir/Message.c.o: CMakeFiles/Whiteboard.dir/flags.make
CMakeFiles/Whiteboard.dir/Message.c.o: ../Message.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Whiteboard.dir/Message.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Whiteboard.dir/Message.c.o   -c /home/mani/Workspace/SideProject/Fiv/Whiteboard/Message.c

CMakeFiles/Whiteboard.dir/Message.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Whiteboard.dir/Message.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mani/Workspace/SideProject/Fiv/Whiteboard/Message.c > CMakeFiles/Whiteboard.dir/Message.c.i

CMakeFiles/Whiteboard.dir/Message.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Whiteboard.dir/Message.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mani/Workspace/SideProject/Fiv/Whiteboard/Message.c -o CMakeFiles/Whiteboard.dir/Message.c.s

# Object files for target Whiteboard
Whiteboard_OBJECTS = \
"CMakeFiles/Whiteboard.dir/TCP_Client.c.o" \
"CMakeFiles/Whiteboard.dir/TCP_Server.c.o" \
"CMakeFiles/Whiteboard.dir/Whiteboard.c.o" \
"CMakeFiles/Whiteboard.dir/User.c.o" \
"CMakeFiles/Whiteboard.dir/Topic.c.o" \
"CMakeFiles/Whiteboard.dir/Message.c.o"

# External object files for target Whiteboard
Whiteboard_EXTERNAL_OBJECTS =

Whiteboard: CMakeFiles/Whiteboard.dir/TCP_Client.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/TCP_Server.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/Whiteboard.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/User.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/Topic.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/Message.c.o
Whiteboard: CMakeFiles/Whiteboard.dir/build.make
Whiteboard: CMakeFiles/Whiteboard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable Whiteboard"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Whiteboard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Whiteboard.dir/build: Whiteboard

.PHONY : CMakeFiles/Whiteboard.dir/build

CMakeFiles/Whiteboard.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Whiteboard.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Whiteboard.dir/clean

CMakeFiles/Whiteboard.dir/depend:
	cd /home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mani/Workspace/SideProject/Fiv/Whiteboard /home/mani/Workspace/SideProject/Fiv/Whiteboard /home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug /home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug /home/mani/Workspace/SideProject/Fiv/Whiteboard/cmake-build-debug/CMakeFiles/Whiteboard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Whiteboard.dir/depend

