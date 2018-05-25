cmake_minimum_required(VERSION 3.9)
project(MicroEngine)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

set(CMAKE_CXX_STANDARD 11)

# Include the Libtech project
add_subdirectory("engine/lib/libtech")
include_directories("engine/lib/libtech/include")

#include SDL
add_subdirectory("engine/lib/SDL")
include_directories("engine/lib/SDL/include")

file(GLOB_RECURSE ENGINE_SOURCES "engine/src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "engine/include/*.h")

include_directories("engine/include")

IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

# Setup the Static and Shared library builds
add_library(MICROENGINE STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})
add_library(MICROENGINED SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCES})

# Link to LIBTECH
target_link_libraries(MICROENGINE LIBTECH)
target_link_libraries(MICROENGINED LIBTECH)

# Link to SDL
target_link_libraries(MICROENGINE SDL2)
target_link_libraries(MICROENGINED SDL2)

# Add DEFINES to tell the engine to export functions and api
target_compile_definitions(MICROENGINE PRIVATE MICROENGINE_EXPORTS)
target_compile_definitions(MICROENGINED PRIVATE MICROENGINE_EXPORTS)

# Setup the tester project
file(GLOB TESTER_SOURCES "projects/tester/*.cpp")
file(GLOB TESTER_HEADERS "projects/tester/*.h")

# Create the EngineTester project and link it.
add_executable(EngineTester ${TESTER_HEADERS} ${TESTER_SOURCES})
target_link_libraries(EngineTester MICROENGINE)

IF(WIN32)

set_target_properties(MICROENGINE PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(MICROENGINED PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(EngineTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")

ENDIF(WIN32)
