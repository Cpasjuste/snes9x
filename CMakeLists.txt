cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# delete cmake cache folder before changing this options
option(BUILD_SDL2 "Build with SDL2 support" ON)
option(BUILD_UNIX "Build with UNIX/X11 support" OFF)
option(BUILD_PSP2 "Build with PSP2 support" OFF)
option(BUILD_NX "Build with NX (SWITCH) support" OFF)

option(BUILD_SOUND "Build with audio support" ON)
option(BUILD_SCREENSHOT "Build with screenshot support" ON)
option(BUILD_NETPLAY "Build with screenshot support" OFF)
option(BUILD_GAMEPAD "Build with gamepad support" ON)
option(BUILD_GZIP "Build with gzip support" ON)
option(BUILD_ZIP "Build with zip support" ON)
option(BUILD_JMA "Build with jma support" OFF)
option(BUILD_DEBUGGER "Build with debugger support" OFF)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_DEBUG true CACHE BOOL "Debug build")
endif ()

# setup toolchain
include(CMakeListsToolchain.cmake)

project(snes9x)

##############
# SNES9X
##############
set(SNES9X_INC
        .
        apu
        apu/bapu
        apu/bapu/dsp
        apu/bapu/smp
        apu/bapu/snes
        filter
        )

file(GLOB SNES9X_SRC
        *.c*
        apu/*.c*
        apu/bapu/*.c*
        apu/bapu/dsp/*.c*
        apu/bapu/smp/*.c*
        filter/*.c*
        )

list(REMOVE_ITEM SNES9X_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/spc7110dec.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/spc7110emu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/srtcemu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/filter/xbrz.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/apu/bapu/smp/algorithms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/apu/bapu/smp/core.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/apu/bapu/smp/memory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/apu/bapu/smp/timing.cpp
        )

set(SNES9X_CFLAGS
        #-O3
        #-O0 -g
        -fomit-frame-pointer -std=c++11 -fno-exceptions
        -fno-rtti -pedantic -Wall -W -Wno-unused-parameter
        -DHAVE_LIBPNG -DHAVE_MKSTEMP -DHAVE_STRINGS_H
        -DHAVE_SYS_IOCTL_H -DHAVE_STDINT_H -DRIGHTSHIFT_IS_SAR
        -DGFX_MULTI_FORMAT
        )

set(SNES9X_LDFLAGS
        m z png
        )

#####################
# OPTIONS
#####################
if (BUILD_SOUND)
    list(APPEND SNES9X_CFLAGS -DUSE_THREADS)
    list(APPEND SNES9X_LDFLAGS pthread)
else()
    list(APPEND SNES9X_CFLAGS -DNOSOUND)
endif (BUILD_SOUND)
if (BUILD_SCREENSHOT)
endif (BUILD_SCREENSHOT)
if (BUILD_NETPLAY)
endif (BUILD_NETPLAY)
if (BUILD_GAMEPAD)
    list(APPEND SNES9X_CFLAGS -DJOYSTICK_SUPPORT)
endif (BUILD_GAMEPAD)
if (BUILD_GZIP)
    list(APPEND SNES9X_CFLAGS -DZLIB)
endif (BUILD_GZIP)
if (BUILD_ZIP)
    set(UNZIP_INC unzip)
    file(GLOB UNZIP_SRC unzip/*.c*)
    list(REMOVE_ITEM UNZIP_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/unzip/iowin32.c
            ${CMAKE_CURRENT_SOURCE_DIR}/unzip/minizip.c
            ${CMAKE_CURRENT_SOURCE_DIR}/unzip/miniunz.c
            )
    list(APPEND SNES9X_CFLAGS -DUNZIP_SUPPORT)
endif (BUILD_ZIP)
if (BUILD_JMA)
    set(JMA_INC jma)
    file(GLOB JMA_SRC jma/*.c*)
    list(APPEND SNES9X_CFLAGS -DJMA_SUPPORT)
endif (BUILD_JMA)
if (BUILD_DEBUGGER)
endif (BUILD_DEBUGGER)

#####################
# PLATORM SPECIFIC
#####################
if (BUILD_PSP2)
    #####################
    # PSP2 PLATORM
elseif (BUILD_NX)
    #####################
    # NX PLATORM
    #####################
elseif (BUILD_UNIX)
    #####################
    # UNIX PLATORM
    #####################
    set(UNIX_INC unix)
    file(GLOB UNIX_SRC unix/*.c*)
    list(APPEND SNES9X_CFLAGS -DUSE_XVIDEO -DUSE_XINERAMA -DMITSHM)
    list(APPEND SNES9X_LDFLAGS X11 Xext Xv Xinerama)
elseif (BUILD_SDL2)
    #####################
    # SDL2 PLATORM
    #####################
    set(SDL2_INC sdl2)
    file(GLOB SDL2_SRC sdl2/*.c*)
    list(APPEND SNES9X_CFLAGS -D__SDL2__)
    list(APPEND SNES9X_LDFLAGS SDL2)
endif (BUILD_PSP2)

#####################
# snes9x executable
#####################
add_executable(${CMAKE_PROJECT_NAME}.elf ${SNES9X_SRC} ${UNZIP_SRC} ${JMA_SRC} ${SDL2_SRC} ${UNIX_SRC})
target_include_directories(${CMAKE_PROJECT_NAME}.elf PRIVATE ${SNES9X_INC} ${UNZIP_INC} ${JMA_INC} ${SDL2_INC} ${UNIX_INC})
target_compile_options(${CMAKE_PROJECT_NAME}.elf PRIVATE ${SNES9X_CFLAGS})
target_link_libraries(${CMAKE_PROJECT_NAME}.elf ${SNES9X_LDFLAGS})

#####################
# PSP2 (vita) target
#####################
if (BUILD_PSP2)
    vita_create_self(${CMAKE_PROJECT_NAME}.self ${CMAKE_PROJECT_NAME}.elf)
    vita_create_vpk(${CMAKE_PROJECT_NAME}.vpk "OPENBOR01" ${CMAKE_PROJECT_NAME}.self
            VERSION "01.00" NAME "${CMAKE_PROJECT_NAME}")
endif (BUILD_PSP2)

#####################
# NX (SWITCH) target
#####################
if (BUILD_NX)
    add_custom_target(${CMAKE_PROJECT_NAME}.nro
            DEPENDS ${CMAKE_PROJECT_NAME}.elf
            COMMAND elf2nro ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.nro)
endif (BUILD_NX)
