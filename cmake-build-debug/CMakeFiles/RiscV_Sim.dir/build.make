# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\pedro\Documents\RiscV_Sim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\pedro\Documents\RiscV_Sim\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\RiscV_Sim.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\RiscV_Sim.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\RiscV_Sim.dir\flags.make

CMakeFiles\RiscV_Sim.dir\main.c.obj: CMakeFiles\RiscV_Sim.dir\flags.make
CMakeFiles\RiscV_Sim.dir\main.c.obj: ..\main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\pedro\Documents\RiscV_Sim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RiscV_Sim.dir/main.c.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\RiscV_Sim.dir\main.c.obj /FdCMakeFiles\RiscV_Sim.dir\ /FS -c C:\Users\pedro\Documents\RiscV_Sim\main.c
<<

CMakeFiles\RiscV_Sim.dir\main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RiscV_Sim.dir/main.c.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\RiscV_Sim.dir\main.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\pedro\Documents\RiscV_Sim\main.c
<<

CMakeFiles\RiscV_Sim.dir\main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RiscV_Sim.dir/main.c.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\RiscV_Sim.dir\main.c.s /c C:\Users\pedro\Documents\RiscV_Sim\main.c
<<

# Object files for target RiscV_Sim
RiscV_Sim_OBJECTS = \
"CMakeFiles\RiscV_Sim.dir\main.c.obj"

# External object files for target RiscV_Sim
RiscV_Sim_EXTERNAL_OBJECTS =

RiscV_Sim.exe: CMakeFiles\RiscV_Sim.dir\main.c.obj
RiscV_Sim.exe: CMakeFiles\RiscV_Sim.dir\build.make
RiscV_Sim.exe: CMakeFiles\RiscV_Sim.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\pedro\Documents\RiscV_Sim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable RiscV_Sim.exe"
	"C:\Program Files\JetBrains\CLion 2021.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\RiscV_Sim.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\RiscV_Sim.dir\objects1.rsp @<<
 /out:RiscV_Sim.exe /implib:RiscV_Sim.lib /pdb:C:\Users\pedro\Documents\RiscV_Sim\cmake-build-debug\RiscV_Sim.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\RiscV_Sim.dir\build: RiscV_Sim.exe
.PHONY : CMakeFiles\RiscV_Sim.dir\build

CMakeFiles\RiscV_Sim.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\RiscV_Sim.dir\cmake_clean.cmake
.PHONY : CMakeFiles\RiscV_Sim.dir\clean

CMakeFiles\RiscV_Sim.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\pedro\Documents\RiscV_Sim C:\Users\pedro\Documents\RiscV_Sim C:\Users\pedro\Documents\RiscV_Sim\cmake-build-debug C:\Users\pedro\Documents\RiscV_Sim\cmake-build-debug C:\Users\pedro\Documents\RiscV_Sim\cmake-build-debug\CMakeFiles\RiscV_Sim.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\RiscV_Sim.dir\depend

