cmake_minimum_required(VERSION 3.2)
project(MyCompiler VERSION 1.0)

# ------------------------------------------------- #

set(CMAKE_CXX_STANDARD 17)

set(MAIN_SOURCE_FILE	${PROJECT_SOURCE_DIR}/src/main.cpp)
set(INCLUDE_DIRECTORY	${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIRECTORY	${PROJECT_SOURCE_DIR}/src)
set(TEST_DIRECTORY	    ${PROJECT_SOURCE_DIR}/test)
set(LIBRARY_DIRECTORY	${PROJECT_SOURCE_DIR}/lib)

# ------------------------------------------------- #

# Include headers

include_directories(${INCLUDE_DIRECTORY})

# Create variable SRC_FILES with all source files except for the main source file

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${SOURCE_DIRECTORY}/*.cpp)
list(REMOVE_ITEM SRC_FILES ${MAIN_SOURCE_FILE})

# Add main executable

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} ${MAIN_SOURCE_FILE})

# Set up tests

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ${TEST_DIRECTORY}/*.cpp)
foreach(TEST_FILE IN LISTS TEST_FILES)
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_FILE_NAME} ${SRC_FILES} ${TEST_FILE})
    target_link_libraries(${TEST_FILE_NAME} gtest_main)
    add_test(${TEST_FILE_NAME}_Tester ${TEST_FILE_NAME})
endforeach()