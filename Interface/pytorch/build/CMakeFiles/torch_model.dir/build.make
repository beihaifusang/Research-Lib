# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/tangliyao/.local/lib/python3.6/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/tangliyao/.local/lib/python3.6/site-packages/cmake/data/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tangliyao/Research-Lib/Interface/pytorch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tangliyao/Research-Lib/Interface/pytorch/build

# Include any dependencies generated for this target.
include CMakeFiles/torch_model.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/torch_model.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/torch_model.dir/flags.make

CMakeFiles/torch_model.dir/torch_model.cpp.o: CMakeFiles/torch_model.dir/flags.make
CMakeFiles/torch_model.dir/torch_model.cpp.o: ../torch_model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tangliyao/Research-Lib/Interface/pytorch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/torch_model.dir/torch_model.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/torch_model.dir/torch_model.cpp.o -c /home/tangliyao/Research-Lib/Interface/pytorch/torch_model.cpp

CMakeFiles/torch_model.dir/torch_model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/torch_model.dir/torch_model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tangliyao/Research-Lib/Interface/pytorch/torch_model.cpp > CMakeFiles/torch_model.dir/torch_model.cpp.i

CMakeFiles/torch_model.dir/torch_model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/torch_model.dir/torch_model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tangliyao/Research-Lib/Interface/pytorch/torch_model.cpp -o CMakeFiles/torch_model.dir/torch_model.cpp.s

# Object files for target torch_model
torch_model_OBJECTS = \
"CMakeFiles/torch_model.dir/torch_model.cpp.o"

# External object files for target torch_model
torch_model_EXTERNAL_OBJECTS =

torch_model: CMakeFiles/torch_model.dir/torch_model.cpp.o
torch_model: CMakeFiles/torch_model.dir/build.make
torch_model: /usr/local/include/libtorch/lib/libtorch.so
torch_model: /usr/local/include/libtorch/lib/libc10.so
torch_model: /usr/lib/x86_64-linux-gnu/libcuda.so
torch_model: /usr/local/cuda/lib64/libnvrtc.so
torch_model: /usr/local/cuda/lib64/libnvToolsExt.so
torch_model: /usr/local/cuda/lib64/libcudart.so
torch_model: /usr/local/include/libtorch/lib/libc10_cuda.so
torch_model: /usr/local/include/libtorch/lib/libc10_cuda.so
torch_model: /usr/local/include/libtorch/lib/libc10.so
torch_model: /usr/local/cuda/lib64/libcufft.so
torch_model: /usr/local/cuda/lib64/libcurand.so
torch_model: /usr/lib/x86_64-linux-gnu/libcudnn.so
torch_model: /usr/local/cuda/lib64/libculibos.a
torch_model: /usr/local/cuda/lib64/libculibos.a
torch_model: /usr/lib/x86_64-linux-gnu/libcublas.so
torch_model: /usr/local/cuda/lib64/libcudart.so
torch_model: CMakeFiles/torch_model.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tangliyao/Research-Lib/Interface/pytorch/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable torch_model"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/torch_model.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/torch_model.dir/build: torch_model

.PHONY : CMakeFiles/torch_model.dir/build

CMakeFiles/torch_model.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/torch_model.dir/cmake_clean.cmake
.PHONY : CMakeFiles/torch_model.dir/clean

CMakeFiles/torch_model.dir/depend:
	cd /home/tangliyao/Research-Lib/Interface/pytorch/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tangliyao/Research-Lib/Interface/pytorch /home/tangliyao/Research-Lib/Interface/pytorch /home/tangliyao/Research-Lib/Interface/pytorch/build /home/tangliyao/Research-Lib/Interface/pytorch/build /home/tangliyao/Research-Lib/Interface/pytorch/build/CMakeFiles/torch_model.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/torch_model.dir/depend
