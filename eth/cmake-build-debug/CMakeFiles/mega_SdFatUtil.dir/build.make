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
include CMakeFiles\mega_SdFatUtil.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\mega_SdFatUtil.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\mega_SdFatUtil.dir\flags.make

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.obj: CMakeFiles\mega_SdFatUtil.dir\flags.make
CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\SD\src\File.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/File.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\SD\src\File.cpp"

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/File.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\SD\src\File.cpp" > CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.i

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/File.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\SD\src\File.cpp" -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.s

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.obj: CMakeFiles\mega_SdFatUtil.dir\flags.make
CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\SD\src\SD.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/SD.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\SD\src\SD.cpp"

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/SD.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\SD\src\SD.cpp" > CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.i

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/SD.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\SD\src\SD.cpp" -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.s

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.obj: CMakeFiles\mega_SdFatUtil.dir\flags.make
CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/Sd2Card.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp"

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/Sd2Card.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp" > CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.i

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/Sd2Card.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp" -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.s

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.obj: CMakeFiles\mega_SdFatUtil.dir\flags.make
CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdFile.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/SdFile.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdFile.cpp"

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/SdFile.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdFile.cpp" > CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.i

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/SdFile.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdFile.cpp" -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.s

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.obj: CMakeFiles\mega_SdFatUtil.dir\flags.make
CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/SdVolume.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp"

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/SdVolume.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp" > CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.i

CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_SdFatUtil.dir/C_/Program_Files_(x86)/Arduino/libraries/SD/src/utility/SdVolume.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp" -o CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.s

# Object files for target mega_SdFatUtil
mega_SdFatUtil_OBJECTS = \
"CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.obj" \
"CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.obj" \
"CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.obj" \
"CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.obj" \
"CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.obj"

# External object files for target mega_SdFatUtil
mega_SdFatUtil_EXTERNAL_OBJECTS =

libmega_SdFatUtil.a: CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\File.cpp.obj
libmega_SdFatUtil.a: CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\SD.cpp.obj
libmega_SdFatUtil.a: CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\Sd2Card.cpp.obj
libmega_SdFatUtil.a: CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdFile.cpp.obj
libmega_SdFatUtil.a: CMakeFiles\mega_SdFatUtil.dir\C_\Program_Files_(x86)\Arduino\libraries\SD\src\utility\SdVolume.cpp.obj
libmega_SdFatUtil.a: CMakeFiles\mega_SdFatUtil.dir\build.make
libmega_SdFatUtil.a: CMakeFiles\mega_SdFatUtil.dir\link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libmega_SdFatUtil.a"
	$(CMAKE_COMMAND) -P CMakeFiles\mega_SdFatUtil.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mega_SdFatUtil.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles\mega_SdFatUtil.dir\build: libmega_SdFatUtil.a

.PHONY : CMakeFiles\mega_SdFatUtil.dir\build

CMakeFiles\mega_SdFatUtil.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mega_SdFatUtil.dir\cmake_clean.cmake
.PHONY : CMakeFiles\mega_SdFatUtil.dir\clean

CMakeFiles\mega_SdFatUtil.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\locker1540-arduino\eth D:\locker1540-arduino\eth D:\locker1540-arduino\eth\cmake-build-debug D:\locker1540-arduino\eth\cmake-build-debug D:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles\mega_SdFatUtil.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\mega_SdFatUtil.dir\depend

