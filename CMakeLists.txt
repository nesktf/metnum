cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(metnum CXX)

set(CMAKE_CXX_STANDARD 17)

set(LIB_INCLUDE)
set(LIB_LINK)

find_package(Armadillo REQUIRED ARMADILLO)
list(APPEND LIB_INCLUDE ${ARMADILLO_INCLUDE_DIRS})
list(APPEND LIB_LINK ${ARMADILLO_LIBRARIES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -Wextra -Wpedantic -O0 -g2 -ggdb -Wno-psabi")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall -Wextra -Wpedantic -O3 -Wno-psabi")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
list(APPEND LIB_INCLUDE src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_LINK})
