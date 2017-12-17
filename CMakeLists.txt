
cmake_minimum_required(VERSION 2.8)

project(LogicToolbox)
set(PROJECT_VERSION 0.1)
set(PROJECT_BRIEF "\"Toolbox for logic computations\"")

include(${CMAKE_SOURCE_DIR}/cmake/SetEnv.cmake)

# Enable/disable testing
option(TESTS_ENABLED "Enable automatic tests" ON)
# Enable/disable testCoverage coverage
option(COVERAGE_ENABLED "Enable test coverage" OFF)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/src)



if(COVERAGE_ENABLED)
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -fPIC -O0 -ggdb -fprofile-arcs -ftest-coverage")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -ggdb")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "Compiler does not support C++11")
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
            )
endif(DOXYGEN_FOUND)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(GRAPHVIZ_ROOT)
    set(_GRAPHVIZ_INCLUDE_DIR ${GRAPHVIZ_ROOT}/include)
    set(_GRAPHVIZ_LIBRARY_DIR ${GRAPHVIZ_ROOT}/lib)
endif()

find_path(GRAPHVIZ_INCLUDE_DIR         NAMES graphviz/cgraph.h
        HINTS ${_GRAPHVIZ_INCLUDE_DIR})
find_library(GRAPHVIZ_CDT_LIBRARY      NAMES cdt
        HINTS ${_GRAPHVIZ_LIBRARY_DIR})
find_library(GRAPHVIZ_GVC_LIBRARY      NAMES gvc
        HINTS ${_GRAPHVIZ_LIBRARY_DIR})
find_library(GRAPHVIZ_CGRAPH_LIBRARY   NAMES cgraph
        HINTS ${_GRAPHVIZ_LIBRARY_DIR})
find_library(GRAPHVIZ_PATHPLAN_LIBRARY NAMES pathplan
        HINTS ${_GRAPHVIZ_LIBRARY_DIR})

if(GRAPHVIZ_INCLUDE_DIR AND GRAPHVIZ_CDT_LIBRARY AND GRAPHVIZ_GVC_LIBRARY
        AND GRAPHVIZ_CGRAPH_LIBRARY AND GRAPHVIZ_PATHPLAN_LIBRARY)
    set(GRAPHVIZ_FOUND TRUE)
else()
    set(GRAPHVIZ_FOUND FALSE)
endif()

# Ok, now compute the version
if(GRAPHVIZ_FOUND)
    set(FIND_GRAPHVIZ_VERSION_SOURCE
            "#include <graphviz/graphviz_version.h>\n#include <stdio.h>\n int main()\n {\n printf(\"%s\",PACKAGE_VERSION);return 1;\n }\n")
    set(FIND_GRAPHVIZ_VERSION_SOURCE_FILE ${CMAKE_BINARY_DIR}/CMakeTmp/FindGRAPHVIZ.cxx)
    file(WRITE "${FIND_GRAPHVIZ_VERSION_SOURCE_FILE}" "${FIND_GRAPHVIZ_VERSION_SOURCE}")

    set(FIND_GRAPHVIZ_VERSION_ADD_INCLUDES
            "-DINCLUDE_DIRECTORIES:STRING=${GRAPHVIZ_INCLUDE_DIR}")

    try_run(RUN_RESULT COMPILE_RESULT
            ${CMAKE_BINARY_DIR}
            ${FIND_GRAPHVIZ_VERSION_SOURCE_FILE}
            CMAKE_FLAGS "${FIND_GRAPHVIZ_VERSION_ADD_INCLUDES}"
            RUN_OUTPUT_VARIABLE GRAPHVIZ_VERSION)

    if(COMPILE_RESULT AND RUN_RESULT EQUAL 1)
        message(STATUS "Graphviz version: ${GRAPHVIZ_VERSION}")
    else()
        message(FATAL_ERROR "Unable to compile or run the graphviz version detection program.")
    endif()

    set(GRAPHVIZ_INCLUDE_DIRS ${GRAPHVIZ_INCLUDE_DIR} ${GRAPHVIZ_INCLUDE_DIR}/graphviz)

    if(NOT Graphviz_FIND_QUIETLY)
        message(STATUS "Graphviz include: ${GRAPHVIZ_INCLUDE_DIRS}")
        message(STATUS "Graphviz libraries: ${GRAPHVIZ_CDT_LIBRARY} ${GRAPHVIZ_GVC_LIBRARY} ${GRAPHVIZ_CGRAPH_LIBRARY} ${GRAPHVIZ_PATHPLAN_LIBRARY}")
    endif()
endif()

if(Graphviz_FIND_REQUIRED AND NOT GRAPHVIZ_FOUND)
    message(FATAL_ERROR "Could not find GraphViz.")
endif()

if(TESTS_ENABLED)
    add_subdirectory(testCoverage)
endif()

add_subdirectory(src)
add_subdirectory(test)

include(${CMAKE_SOURCE_DIR}/cmake/InstallConfig.cmake)
# vim:ft=cmake