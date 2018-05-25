cmake_minimum_required(VERSION 3.9)
project(MicroEngine)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

set(CMAKE_CXX_STANDARD 11)

include_directories("engine/include")

file(GLOB ENGINE_SOURCES "engine/src/*.cpp")
file(GLOB ENGINE_HEADERS "engine/include/*.h")

IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

add_library(MICROENGINE STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})
add_library(MICROENGINED SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCES})

target_compile_definitions(MICROENGINE PRIVATE LIBTECH_EXPORTS)
target_compile_definitions(MICROENGINED PRIVATE LIBTECH_EXPORTS)

# Setup the tester project
file(GLOB TESTER_SOURCES "projects/tester/*.cpp")
file(GLOB TESTER_HEADERS "projects/tester/*.h")

add_executable(EngineTester ${TESTER_HEADERS} ${TESTER_SOURCES})
target_link_libraries(EngineTester MICROENGINE)

IF(WIN32)

set_target_properties(MICROENGINE PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(MICROENGINED PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(EngineTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")

ENDIF(WIN32)
