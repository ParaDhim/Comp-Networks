# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paras/Desktop/assignment2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paras/Desktop/assignment2/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/wrapping_integers_roundtrip.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/wrapping_integers_roundtrip.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/wrapping_integers_roundtrip.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/wrapping_integers_roundtrip.dir/flags.make

tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o: tests/CMakeFiles/wrapping_integers_roundtrip.dir/flags.make
tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o: /home/paras/Desktop/assignment2/tests/wrapping_integers_roundtrip.cc
tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o: tests/CMakeFiles/wrapping_integers_roundtrip.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/paras/Desktop/assignment2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o"
	cd /home/paras/Desktop/assignment2/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o -MF CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o.d -o CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o -c /home/paras/Desktop/assignment2/tests/wrapping_integers_roundtrip.cc

tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.i"
	cd /home/paras/Desktop/assignment2/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paras/Desktop/assignment2/tests/wrapping_integers_roundtrip.cc > CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.i

tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.s"
	cd /home/paras/Desktop/assignment2/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paras/Desktop/assignment2/tests/wrapping_integers_roundtrip.cc -o CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.s

# Object files for target wrapping_integers_roundtrip
wrapping_integers_roundtrip_OBJECTS = \
"CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o"

# External object files for target wrapping_integers_roundtrip
wrapping_integers_roundtrip_EXTERNAL_OBJECTS =

tests/wrapping_integers_roundtrip: tests/CMakeFiles/wrapping_integers_roundtrip.dir/wrapping_integers_roundtrip.cc.o
tests/wrapping_integers_roundtrip: tests/CMakeFiles/wrapping_integers_roundtrip.dir/build.make
tests/wrapping_integers_roundtrip: tests/libtcp_reciever_checks.a
tests/wrapping_integers_roundtrip: src/libtcp_reciever.a
tests/wrapping_integers_roundtrip: tests/CMakeFiles/wrapping_integers_roundtrip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/paras/Desktop/assignment2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wrapping_integers_roundtrip"
	cd /home/paras/Desktop/assignment2/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wrapping_integers_roundtrip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/wrapping_integers_roundtrip.dir/build: tests/wrapping_integers_roundtrip
.PHONY : tests/CMakeFiles/wrapping_integers_roundtrip.dir/build

tests/CMakeFiles/wrapping_integers_roundtrip.dir/clean:
	cd /home/paras/Desktop/assignment2/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/wrapping_integers_roundtrip.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/wrapping_integers_roundtrip.dir/clean

tests/CMakeFiles/wrapping_integers_roundtrip.dir/depend:
	cd /home/paras/Desktop/assignment2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paras/Desktop/assignment2 /home/paras/Desktop/assignment2/tests /home/paras/Desktop/assignment2/build /home/paras/Desktop/assignment2/build/tests /home/paras/Desktop/assignment2/build/tests/CMakeFiles/wrapping_integers_roundtrip.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/wrapping_integers_roundtrip.dir/depend

