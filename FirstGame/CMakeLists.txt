# CMakeList.txt : CMake project for FirstGame}, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (FirstGame "Main.cpp" "Game.cpp" "Game.hpp")

message(STATUS "Directory is in: ${OwnEngine}")

include_directories(OwnEngine)

target_include_directories(FirstGame PUBLIC OwnEngine)
target_link_directories(FirstGame PUBLIC OwnEngine)
target_link_libraries(FirstGame PUBLIC OwnEngine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FirstGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
