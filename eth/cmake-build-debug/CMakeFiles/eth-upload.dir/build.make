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
CMAKE_SOURCE_DIR = E:\locker1540-arduino\eth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\locker1540-arduino\eth\cmake-build-debug

# Utility rule file for eth-upload.

# Include the progress variables for this target.
include CMakeFiles\eth-upload.dir\progress.make

CMakeFiles\eth-upload: eth.elf
	echo >nul && "C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude.exe" "-CC:/Program Files (x86)/Arduino/hardware/tools/avr/etc/avrdude.conf" -patmega2560 -cwiring -b115200 -PCOM4 -D -V -Uflash:w:E:/locker1540-arduino/eth/cmake-build-debug/eth.hex:i -Ueeprom:w:E:/locker1540-arduino/eth/cmake-build-debug/eth.eep:i

eth-upload: CMakeFiles\eth-upload
eth-upload: CMakeFiles\eth-upload.dir\build.make

.PHONY : eth-upload

# Rule to build all files generated by this target.
CMakeFiles\eth-upload.dir\build: eth-upload

.PHONY : CMakeFiles\eth-upload.dir\build

CMakeFiles\eth-upload.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\eth-upload.dir\cmake_clean.cmake
.PHONY : CMakeFiles\eth-upload.dir\clean

CMakeFiles\eth-upload.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" E:\locker1540-arduino\eth E:\locker1540-arduino\eth E:\locker1540-arduino\eth\cmake-build-debug E:\locker1540-arduino\eth\cmake-build-debug E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles\eth-upload.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\eth-upload.dir\depend

