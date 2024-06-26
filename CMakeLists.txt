﻿# CMakeList.txt : CMake project for Reluctor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
option(ReluctorOperations_build_tests "Build all of ReluctorOperations tests" OFF)

set(TARGET		ReluctorOperations)
set(HDR_DIR		include)
set(SRCS_DIR	src)
set(LIBRARIES	libs)

project(${TARGET} CXX)

Set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)

FetchContent_Declare(
    OperationArchitecture
    GIT_REPOSITORY    https://github.com/FL0WL0W/OperationArchitecture
    GIT_TAG           main
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(OperationArchitecture)
FetchContent_Declare(
    EmbeddedIOServices
    GIT_REPOSITORY    https://github.com/FL0WL0W/EmbeddedIOServices
    GIT_TAG           main
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(EmbeddedIOServices)
FetchContent_Declare(
    EmbeddedIOOperations
    GIT_REPOSITORY    https://github.com/FL0WL0W/EmbeddedIOOperations
    GIT_TAG           main
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(EmbeddedIOOperations)

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

# install library
install(TARGETS ${TARGET} LIBRARY DESTINATION lib)
install(DIRECTORY "${HDR_DIR}/" DESTINATION include)