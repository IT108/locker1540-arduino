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

# Include any dependencies generated for this target.
include CMakeFiles\uno_w5100.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\uno_w5100.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\uno_w5100.dir\flags.make

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Dhcp.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Dhcp.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Dhcp.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.s

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dns.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Dns.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dns.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Dns.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dns.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Dns.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Dns.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.s

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Ethernet.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Ethernet.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/Ethernet.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.s

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetClient.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetClient.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetClient.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.s

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetServer.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetServer.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetServer.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.s

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetUdp.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetUdp.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/EthernetUdp.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.s

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\socket.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/socket.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\socket.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/socket.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\socket.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/socket.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\socket.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.s

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.obj: CMakeFiles\uno_w5100.dir\flags.make
CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.obj: "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/utility/w5100.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.obj -c "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp"

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/utility/w5100.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp" > CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.i

CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_w5100.dir/C_/Program_Files_(x86)/Arduino/libraries/Ethernet/src/utility/w5100.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files (x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp" -o CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.s

# Object files for target uno_w5100
uno_w5100_OBJECTS = \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.obj" \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.obj" \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.obj" \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.obj" \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.obj" \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.obj" \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.obj" \
"CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.obj"

# External object files for target uno_w5100
uno_w5100_EXTERNAL_OBJECTS =

libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dhcp.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Dns.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\Ethernet.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetClient.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetServer.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\EthernetUdp.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\socket.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\C_\Program_Files_(x86)\Arduino\libraries\Ethernet\src\utility\w5100.cpp.obj
libuno_w5100.a: CMakeFiles\uno_w5100.dir\build.make
libuno_w5100.a: CMakeFiles\uno_w5100.dir\link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libuno_w5100.a"
	$(CMAKE_COMMAND) -P CMakeFiles\uno_w5100.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\uno_w5100.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles\uno_w5100.dir\build: libuno_w5100.a

.PHONY : CMakeFiles\uno_w5100.dir\build

CMakeFiles\uno_w5100.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\uno_w5100.dir\cmake_clean.cmake
.PHONY : CMakeFiles\uno_w5100.dir\clean

CMakeFiles\uno_w5100.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" E:\locker1540-arduino\eth E:\locker1540-arduino\eth E:\locker1540-arduino\eth\cmake-build-debug E:\locker1540-arduino\eth\cmake-build-debug E:\locker1540-arduino\eth\cmake-build-debug\CMakeFiles\uno_w5100.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\uno_w5100.dir\depend

