# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

include("cmake/toolchain.cmake")
include("cmake/add_sources.cmake")

project(m4naos VERSION 0.1.1 LANGUAGES C)

include("cmake/git.cmake")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS_DEBUG "-O0 -g -ggdb -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-Os -flto")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(LINKER_SCRIPT "m4naos.ld")

add_definitions(-DM4NAOS_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DM4NAOS_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DM4NAOS_VERSION_PATCH=${PROJECT_VERSION_PATCH})
add_definitions(-DM4NAOS_VERSION_GIT=${PROJECT_VERSION_GIT})

add_definitions(-DM4NAOS_VERSION_MAJOR_STR="${PROJECT_VERSION_MAJOR}")
add_definitions(-DM4NAOS_VERSION_MINOR_STR="${PROJECT_VERSION_MINOR}")
add_definitions(-DM4NAOS_VERSION_PATCH_STR="${PROJECT_VERSION_PATCH}")
add_definitions(-DM4NAOS_VERSION_GIT_STR="${PROJECT_VERSION_GIT}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose build type: None Debug Release RelWithDebInfo MinSizeRel"
    FORCE)
endif()

include_directories(include)
link_directories(${CMAKE_SOURCE_DIR})

# Create executable
add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${CPU_OPTIONS} -T${LINKER_SCRIPT})
set_property(TARGET ${PROJECT_NAME} PROPERTY
  LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})

# Visit every subdirectory
add_subdirectory(arch)
add_subdirectory(kernel)
add_subdirectory(init)
add_subdirectory(lib)
add_subdirectory(drivers)

# Custom Targets
add_custom_command(OUTPUT ${PROJECT_NAME}.bin DEPENDS ${PROJECT_NAME}
  COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME} ${PROJECT_NAME}.bin)

add_custom_command(OUTPUT ${PROJECT_NAME}.lst DEPENDS ${PROJECT_NAME}
  COMMAND ${CMAKE_OBJDUMP} -S ${PROJECT_NAME} > ${PROJECT_NAME}.lst)

add_custom_command(OUTPUT ${PROJECT_NAME}.sym DEPENDS ${PROJECT_NAME}
  COMMAND ${CMAKE_NM} -C -l -n -S ${PROJECT_NAME} > ${PROJECT_NAME}.sym)

add_custom_target(bin ALL DEPENDS ${PROJECT_NAME}.bin)
add_custom_target(lst ALL DEPENDS ${PROJECT_NAME}.lst)
add_custom_target(sym ALL DEPENDS ${PROJECT_NAME}.sym)
add_custom_target(tags COMMAND git ls-files ${PROJECT_SOURCE_DIR} | etags -)
