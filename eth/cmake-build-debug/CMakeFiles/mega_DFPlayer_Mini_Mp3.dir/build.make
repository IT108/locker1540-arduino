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
CMAKE_SOURCE_DIR = E:\locker1540-arduino\eth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\locker1540-arduino\eth\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/flags.make

CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.obj: CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/flags.make
CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.obj: C:/Program\ Files\ (x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_DFPlayer_Mini_Mp3.dir\C_\Program_Files_(x86)\Arduino\libraries\DFPlayer_Mini_Mp3\DFPlayer_Mini_Mp3.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\DFPlayer_Mini_Mp3\DFPlayer_Mini_Mp3.cpp"

CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\DFPlayer_Mini_Mp3\DFPlayer_Mini_Mp3.cpp" > CMakeFiles\mega_DFPlayer_Mini_Mp3.dir\C_\Program_Files_(x86)\Arduino\libraries\DFPlayer_Mini_Mp3\DFPlayer_Mini_Mp3.cpp.i

CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\DFPlayer_Mini_Mp3\DFPlayer_Mini_Mp3.cpp" -o CMakeFiles\mega_DFPlayer_Mini_Mp3.dir\C_\Program_Files_(x86)\Arduino\libraries\DFPlayer_Mini_Mp3\DFPlayer_Mini_Mp3.cpp.s

# Object files for target mega_DFPlayer_Mini_Mp3
mega_DFPlayer_Mini_Mp3_OBJECTS = \
"CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.obj"

# External object files for target mega_DFPlayer_Mini_Mp3
mega_DFPlayer_Mini_Mp3_EXTERNAL_OBJECTS =

libmega_DFPlayer_Mini_Mp3.a: CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/C_/Program_Files_(x86)/Arduino/libraries/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp.obj
libmega_DFPlayer_Mini_Mp3.a: CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/build.make
libmega_DFPlayer_Mini_Mp3.a: CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmega_DFPlayer_Mini_Mp3.a"
	$(CMAKE_COMMAND) -P CMakeFiles\mega_DFPlayer_Mini_Mp3.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mega_DFPlayer_Mini_Mp3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/build: libmega_DFPlayer_Mini_Mp3.a

.PHONY : CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/build

CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mega_DFPlayer_Mini_Mp3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/clean

CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\locker1540-arduino\eth E:\locker1540-arduino\eth E:\locker1540-arduino\eth\cmake-build-debug E:\locker1540-arduino\eth\cmake-build-debug E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles\mega_DFPlayer_Mini_Mp3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mega_DFPlayer_Mini_Mp3.dir/depend

