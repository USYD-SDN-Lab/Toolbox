# CMakeList.txt : CMake project for Test_Error, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ToolboxTestError")
project ("ToolboxTestFilerManager")

# Add source to this project's executable.
add_executable (ToolboxTestError "Tests/Test_Error/Test_Error.cpp")
add_executable (ToolboxTestFilerManager "Tests/Test_FileManager/Test_FileManager_Linux.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ToolboxTestError PROPERTY CXX_STANDARD 20)
  set_property(TARGET ToolboxTestFilerManager PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
