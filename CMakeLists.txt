cmake_minimum_required(VERSION 3.12)

project(bcf_recruitment_task)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -pthread)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} src/main.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
include_directories(${googletest_SOURCE_DIR}/googletest/include/gtest)

enable_testing()

add_executable(test0 tests/test0.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(test0 PUBLIC include/)
target_link_libraries(test0 gtest_main)

add_executable(test1 tests/test1.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(test1 PUBLIC include/)
target_link_libraries(test1 gtest_main)

add_executable(test2 tests/test2.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(test2 PUBLIC include/)
target_link_libraries(test2 gtest_main)

include(GoogleTest)
gtest_discover_tests(test0)
gtest_discover_tests(test1)
gtest_discover_tests(test2)
