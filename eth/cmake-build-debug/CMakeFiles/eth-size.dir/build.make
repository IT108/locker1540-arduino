# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\locker1540-arduino\eth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\locker1540-arduino\eth\cmake-build-debug

# Utility rule file for eth-size.

# Include the progress variables for this target.
include CMakeFiles/eth-size.dir/progress.make

CMakeFiles/eth-size: eth.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Calculating eth image size"
	"C:\Program Files\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe" -DFIRMWARE_IMAGE=D:/locker1540-arduino/eth/cmake-build-debug/eth.elf -DMCU=atmega2560 -DEEPROM_IMAGE=D:/locker1540-arduino/eth/cmake-build-debug/eth.eep -P D:/locker1540-arduino/eth/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

eth-size: CMakeFiles/eth-size
eth-size: CMakeFiles/eth-size.dir/build.make

.PHONY : eth-size

# Rule to build all files generated by this target.
CMakeFiles/eth-size.dir/build: eth-size

.PHONY : CMakeFiles/eth-size.dir/build

CMakeFiles/eth-size.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\eth-size.dir\cmake_clean.cmake
.PHONY : CMakeFiles/eth-size.dir/clean

CMakeFiles/eth-size.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\locker1540-arduino\eth D:\locker1540-arduino\eth D:\locker1540-arduino\eth\cmake-build-debug D:\locker1540-arduino\eth\cmake-build-debug D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles\eth-size.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eth-size.dir/depend

