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
CMAKE_SOURCE_DIR = /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build

# Include any dependencies generated for this target.
include profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/depend.make

# Include the progress variables for this target.
include profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/progress.make

# Include the compile flags for this target's objects.
include profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/flags.make

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o: profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/flags.make
profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o: ../profile_branch_bias/ProfileBranchBias.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/profile_branch_bias && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o -c /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/profile_branch_bias/ProfileBranchBias.cpp

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.i"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/profile_branch_bias && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/profile_branch_bias/ProfileBranchBias.cpp > CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.i

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.s"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/profile_branch_bias && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/profile_branch_bias/ProfileBranchBias.cpp -o CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.s

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.requires:

.PHONY : profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.requires

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.provides: profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.requires
	$(MAKE) -f profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/build.make profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.provides.build
.PHONY : profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.provides

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.provides.build: profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o


# Object files for target ProfileBranchBias
ProfileBranchBias_OBJECTS = \
"CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o"

# External object files for target ProfileBranchBias
ProfileBranchBias_EXTERNAL_OBJECTS =

profile_branch_bias/libProfileBranchBias.so: profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o
profile_branch_bias/libProfileBranchBias.so: profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/build.make
profile_branch_bias/libProfileBranchBias.so: profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libProfileBranchBias.so"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/profile_branch_bias && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProfileBranchBias.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/build: profile_branch_bias/libProfileBranchBias.so

.PHONY : profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/build

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/requires: profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/ProfileBranchBias.cpp.o.requires

.PHONY : profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/requires

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/clean:
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/profile_branch_bias && $(CMAKE_COMMAND) -P CMakeFiles/ProfileBranchBias.dir/cmake_clean.cmake
.PHONY : profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/clean

profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/depend:
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/profile_branch_bias /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/profile_branch_bias /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/ProfileBranchBias/build/profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : profile_branch_bias/CMakeFiles/ProfileBranchBias.dir/depend

