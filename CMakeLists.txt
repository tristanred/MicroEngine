#
# MicroEngine Main CMakeLists
#

cmake_minimum_required(VERSION 3.9)
project(MicroEngine)

# Get the architecture of the machine
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

# Use C++ 11
set(CMAKE_CXX_STANDARD 11)


#
# Setup Dependencies
#

# Include the Libtech CMake project
add_subdirectory("engine/lib/libtech")
include_directories("engine/lib/libtech/include")

add_subdirectory("engine/lib/pugixml")
include_directories("engine/lib/pugixml/src")

# Setup Windows dependencies
IF(WIN32)
    include_directories("engine/lib/SDL/windows/include")
    include_directories("engine/lib/SDL_image/windows/include")
    include_directories("engine/lib/SDL_ttf/windows/include")

    find_library(
        SDL2_LIB
        NAMES SDL2
        HINTS "engine/lib/SDL/windows/lib/${ARCH}"
    )
    find_library(
        SDL2_IMAGE_LIB
        NAMES SDL2_image
        HINTS "engine/lib/SDL_image/windows/lib/${ARCH}"
    )
    find_library(
        SDL2_TTF_LIB
        NAMES SDL2_ttf
        HINTS "engine/lib/SDL_ttf/windows/lib/${ARCH}"
    )
ENDIF(WIN32)

# Setup Linux dependencies
IF(UNIX)
    include_directories("engine/lib/SDL/linux/include")
    include_directories("engine/lib/SDL_image/linux/include")
    include_directories("engine/lib/SDL_ttf/linux/include")

    find_path(
        SDL2_INCLUDE
        SDL.h
        HINTS $ENV{SDL2DIR}
        PATH_SUFFIXES
            include/SDL2
            include
        PATHS ${SDL2_SEARCH_PATHS}
    )
    find_path(
        SDL2_IMAGE_INCLUDE
        SDL_image.h
        HINTS
            ENV SDL2IMAGEDIR
            ENV SDL2DIR
        PATH_SUFFIXES
            SDL2
            # path suffixes to search inside ENV{SDLDIR}
            include/SDL2 include
        PATHS ${SDL2_IMAGE_PATH}
    )
    find_path(
        SDL2_TTF_INCLUDE
        SDL_ttf.h
        HINTS
            ENV SDL2TTFDIR
            ENV SDL2DIR
        PATH_SUFFIXES
            SDL2
            # path suffixes to search inside ENV{SDLDIR}
            include/SDL2 include
        PATHS ${SDL2_TTF_PATH}
    )
    find_library(
        SDL2_LIB
        NAMES SDL2
        #HINTS "../libs/linux/SDL/lib/x86"
    )
    find_library(
        SDL2_IMAGE_LIB
        NAMES SDL2_image
        #HINTS "../libs/linux/SDL_Image/lib/x86"
    )
    find_library(
        SDL2_TTF_LIB
        NAMES SDL2_ttf
        #HINTS "../libs/linux/SDL_ttf/lib/x86"
    )
ENDIF(UNIX)

#
# Setup common properties
#
IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

#
# Create projects
#

## MicroEngine sources
file(GLOB_RECURSE ENGINE_SOURCES "engine/src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "engine/include/*.h")

# Add the engine files to be included by others
include_directories("engine/include")

# Setup the Static and Shared library builds
add_library(MICROENGINE STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})
add_library(MICROENGINED SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCES})

# Link dependencies
target_link_libraries(MICROENGINE LIBTECH ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB} pugixml)
target_link_libraries(MICROENGINED LIBTECHD ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB} pugixml)

# Add DEFINES to tell the engine to export functions and api
target_compile_definitions(MICROENGINE PRIVATE MICROENGINE_EXPORTS)
target_compile_definitions(MICROENGINED PRIVATE MICROENGINE_EXPORTS)

# Setup the tester project
file(GLOB TESTER_SOURCES "projects/tester/*.cpp")
file(GLOB TESTER_HEADERS "projects/tester/*.h")

## EngineTester sources
add_executable(EngineTester ${TESTER_HEADERS} ${TESTER_SOURCES})
target_link_libraries(EngineTester MICROENGINE)


#
# Adjust project properties
#
IF(WIN32)

set_target_properties(MICROENGINE PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(MICROENGINED PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(EngineTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")

ENDIF(WIN32)

#
# Copy the dependencies to the output folder
#
IF(WIN32)
    #SDL2.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL/windows/lib/$(PlatformTarget)/SDL2.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )

    #SDL2_Image.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_image/windows/lib/$(PlatformTarget)/SDL2_image.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )
    
    #libjpeg-9.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_image/windows/lib/$(PlatformTarget)/libjpeg-9.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )
    
    #libpng16-16.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_image/windows/lib/$(PlatformTarget)/libpng16-16.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )
    
    #libtiff-5.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_image/windows/lib/$(PlatformTarget)/libtiff-5.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )
    
    #libwebp-4.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_image/windows/lib/$(PlatformTarget)/libwebp-4.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )

    #SDL2_ttf.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_ttf/windows/lib/$(PlatformTarget)/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )
    
    #libfreetype-6.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_ttf/windows/lib/$(PlatformTarget)/libfreetype-6.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )
    
    #zlib1.dll
    add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/engine/lib/SDL_image/windows/lib/$(PlatformTarget)/zlib1.dll"
        $<TARGET_FILE_DIR:MICROENGINE>
    )
    
    # Copy libtech
    add_custom_command(
        TARGET MICROENGINE POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/build/engine/lib/libtech/$(Configuration)/LIBTECHD.dll"
        $<TARGET_FILE_DIR:MICROENGINE>)
    
ENDIF(WIN32)

add_custom_command(
        TARGET MICROENGINE POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/engine/assets"
        $<TARGET_FILE_DIR:MICROENGINE>/assets/engine
)
