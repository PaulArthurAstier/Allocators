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
CMAKE_SOURCE_DIR = "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build"

# Include any dependencies generated for this target.
include CMakeFiles/AllocatorsAndMemoryPool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AllocatorsAndMemoryPool.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AllocatorsAndMemoryPool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AllocatorsAndMemoryPool.dir/flags.make

CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o: CMakeFiles/AllocatorsAndMemoryPool.dir/flags.make
CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o: ../main.cpp
CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o: CMakeFiles/AllocatorsAndMemoryPool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o -MF CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o.d -o CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o -c "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/main.cpp"

CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.i"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/main.cpp" > CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.i

CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.s"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/main.cpp" -o CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.s

CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o: CMakeFiles/AllocatorsAndMemoryPool.dir/flags.make
CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o: ../allocator.cpp
CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o: CMakeFiles/AllocatorsAndMemoryPool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o -MF CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o.d -o CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o -c "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/allocator.cpp"

CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.i"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/allocator.cpp" > CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.i

CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.s"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/allocator.cpp" -o CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.s

# Object files for target AllocatorsAndMemoryPool
AllocatorsAndMemoryPool_OBJECTS = \
"CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o" \
"CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o"

# External object files for target AllocatorsAndMemoryPool
AllocatorsAndMemoryPool_EXTERNAL_OBJECTS =

AllocatorsAndMemoryPool: CMakeFiles/AllocatorsAndMemoryPool.dir/main.cpp.o
AllocatorsAndMemoryPool: CMakeFiles/AllocatorsAndMemoryPool.dir/allocator.cpp.o
AllocatorsAndMemoryPool: CMakeFiles/AllocatorsAndMemoryPool.dir/build.make
AllocatorsAndMemoryPool: CMakeFiles/AllocatorsAndMemoryPool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AllocatorsAndMemoryPool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AllocatorsAndMemoryPool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AllocatorsAndMemoryPool.dir/build: AllocatorsAndMemoryPool
.PHONY : CMakeFiles/AllocatorsAndMemoryPool.dir/build

CMakeFiles/AllocatorsAndMemoryPool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AllocatorsAndMemoryPool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AllocatorsAndMemoryPool.dir/clean

CMakeFiles/AllocatorsAndMemoryPool.dir/depend:
	cd "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators" "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators" "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build" "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build" "/mnt/d/OneDrive/Desktop/Year 4/APC/Topic 1 Allocators/Allocators/build/CMakeFiles/AllocatorsAndMemoryPool.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/AllocatorsAndMemoryPool.dir/depend

