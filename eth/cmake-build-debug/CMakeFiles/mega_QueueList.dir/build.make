# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\locker1540-arduino\eth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\locker1540-arduino\eth\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\mega_QueueList.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\mega_QueueList.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\mega_QueueList.dir\flags.make

# Object files for target mega_QueueList
mega_QueueList_OBJECTS =

# External object files for target mega_QueueList
mega_QueueList_EXTERNAL_OBJECTS =

libmega_QueueList.a: CMakeFiles\mega_QueueList.dir\build.make
libmega_QueueList.a: CMakeFiles\mega_QueueList.dir\link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library libmega_QueueList.a"
	$(CMAKE_COMMAND) -P CMakeFiles\mega_QueueList.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mega_QueueList.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles\mega_QueueList.dir\build: libmega_QueueList.a

.PHONY : CMakeFiles\mega_QueueList.dir\build

CMakeFiles\mega_QueueList.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mega_QueueList.dir\cmake_clean.cmake
.PHONY : CMakeFiles\mega_QueueList.dir\clean

CMakeFiles\mega_QueueList.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\locker1540-arduino\eth D:\locker1540-arduino\eth D:\locker1540-arduino\eth\cmake-build-debug D:\locker1540-arduino\eth\cmake-build-debug D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles\mega_QueueList.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\mega_QueueList.dir\depend

