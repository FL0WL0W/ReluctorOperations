# CMakeList.txt : CMake project for Reluctor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.30[3.30])
option(ReluctorOperations_build_tests "Build all of ReluctorOperations tests" OFF)

set(TARGET		        ReluctorOperations)
set(HDR_DIR		        include)
set(SRCS_DIR	        src)
set(LIBRARIES_DIR	    ${CMAKE_SOURCE_DIR}/libs)

project(${TARGET} CXX)

Set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)

FetchContent_Declare(
    OperationArchitecture
    GIT_REPOSITORY    https://github.com/FL0WL0W/OperationArchitecture
    GIT_TAG           main
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    SOURCE_DIR  ${LIBRARIES_DIR}/OperationArchitecture
)
FetchContent_MakeAvailable(OperationArchitecture)
execute_process(COMMAND git pull WORKING_DIRECTORY ${LIBRARIES_DIR}/OperationArchitecture)
FetchContent_Declare(
    EmbeddedIOServices
    GIT_REPOSITORY    https://github.com/FL0WL0W/EmbeddedIOServices
    GIT_TAG           main
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    SOURCE_DIR  ${LIBRARIES_DIR}/EmbeddedIOServices
)
FetchContent_MakeAvailable(EmbeddedIOServices)
execute_process(COMMAND git pull WORKING_DIRECTORY ${LIBRARIES_DIR}/EmbeddedIOServices)
FetchContent_Declare(
    EmbeddedIOOperations
    GIT_REPOSITORY    https://github.com/FL0WL0W/EmbeddedIOOperations
    GIT_TAG           main
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    SOURCE_DIR  ${LIBRARIES_DIR}/EmbeddedIOOperations
)
FetchContent_MakeAvailable(EmbeddedIOOperations)
execute_process(COMMAND git pull WORKING_DIRECTORY ${LIBRARIES_DIR}/EmbeddedIOOperations)

# headers are always in include/
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS ${HDR_DIR}/*.h)
include_directories(${HDR_DIR})
# sources are always in src/
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS ${SRCS_DIR}/*.cpp)

# create library
add_library(${TARGET} STATIC ${HDRS} ${SRCS})
target_include_directories(${TARGET} PUBLIC ${HDR_DIR})
target_link_libraries(${TARGET} OperationArchitecture)
target_link_libraries(${TARGET} EmbeddedIOServices)
target_link_libraries(${TARGET} EmbeddedIOOperations)

if(ReluctorOperations_build_tests)
    #include test
    add_subdirectory(test)
endif()