# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/clion-2023.1.3/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /opt/clion-2023.1.3/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug

# Include any dependencies generated for this target.
include src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/compiler_depend.make

# Include the progress variables for this target.
include src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/progress.make

# Include the compile flags for this target's objects.
include src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/flags.make

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/flags.make
src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o: src/buff_auto_aim/buff_auto_aim_autogen/mocs_compilation.cpp
src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o -MF CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o -c /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim/buff_auto_aim_autogen/mocs_compilation.cpp

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.i"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim/buff_auto_aim_autogen/mocs_compilation.cpp > CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.i

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.s"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim/buff_auto_aim_autogen/mocs_compilation.cpp -o CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.s

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/flags.make
src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o: /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/buff_auto_aim.cpp
src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o -MF CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o.d -o CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o -c /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/buff_auto_aim.cpp

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.i"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/buff_auto_aim.cpp > CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.i

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.s"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/buff_auto_aim.cpp -o CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.s

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/flags.make
src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o: /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/pnpsolver.cpp
src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o -MF CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o.d -o CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o -c /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/pnpsolver.cpp

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.i"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/pnpsolver.cpp > CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.i

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.s"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim/src/pnpsolver.cpp -o CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.s

# Object files for target buff_auto_aim
buff_auto_aim_OBJECTS = \
"CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o" \
"CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o"

# External object files for target buff_auto_aim
buff_auto_aim_EXTERNAL_OBJECTS =

src/buff_auto_aim/libbuff_auto_aim.a: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/buff_auto_aim_autogen/mocs_compilation.cpp.o
src/buff_auto_aim/libbuff_auto_aim.a: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/buff_auto_aim.cpp.o
src/buff_auto_aim/libbuff_auto_aim.a: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/src/pnpsolver.cpp.o
src/buff_auto_aim/libbuff_auto_aim.a: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/build.make
src/buff_auto_aim/libbuff_auto_aim.a: src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libbuff_auto_aim.a"
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && $(CMAKE_COMMAND) -P CMakeFiles/buff_auto_aim.dir/cmake_clean_target.cmake
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/buff_auto_aim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/build: src/buff_auto_aim/libbuff_auto_aim.a
.PHONY : src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/build

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/clean:
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim && $(CMAKE_COMMAND) -P CMakeFiles/buff_auto_aim.dir/cmake_clean.cmake
.PHONY : src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/clean

src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/depend:
	cd /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/src/buff_auto_aim /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim /home/zps/rm_power/rm_rune_tradition/rune_detector_tradition/cmake-build-debug/src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/buff_auto_aim/CMakeFiles/buff_auto_aim.dir/depend

