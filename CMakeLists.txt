# Copyright (C) 2025 Samuel Wyss
#
# This file is part of numericxx.
#
# Numericxx is free software: you can redistribute it and/or modify it under the terms of the GNU General
# Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# Numericxx is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with numericxx. If not, see
# <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(numericxx
        VERSION 0.0.1
        DESCRIPTION "A dead simple, header-only C++ numerical methods library that does nothing unexpected."
        HOMEPAGE_URL "https://github.com/samwyss/numericxx"
        LANGUAGES CXX
)

include(GNUInstallDirs)

add_library(numericxx
        INTERFACE include/numericxx.hpp
        include/ode/ode.hpp
        include/ode/forward_euler.hpp
)

target_include_directories(numericxx
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(numericxx INTERFACE cxx_std_23)

install(TARGETS numericxx
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("numericxxConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION include)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-O0 -Wall -g3)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG -Wall -march=native -mtune=native -fno-trapping-math -fno-math-errno -ffast-math -flto)
    add_link_options(-flto)
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_options(-O2 -g3 -DNDEBUG -Wall -march=native -mtune=native -fno-omit-frame-pointer -fno-trapping-math -fno-math-errno)
endif ()

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

find_package(fmt QUIET)
if (NOT fmt_FOUND)
    message(STATUS "library `{fmt}` not found ... installing locally now")
    FetchContent_Declare(fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 12.0.0
            GIT_PROGRESS TRUE
            GIT_SHALLOW TRUE
            EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(fmt)
else ()
    message(STATUS "library `{fmt}` found on system")
endif ()

add_executable(numericxx_dummy main.cpp)
target_link_libraries(numericxx_dummy PUBLIC numericxx fmt::fmt)
