cmake_minimum_required(VERSION 3.12)

project(bcf_recruitment_task)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-pthread -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_RELEASE -O3)

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

add_executable(test3 tests/test3.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(test3 PUBLIC include/)
target_link_libraries(test3 gtest_main)

add_executable(test4 tests/test4.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(test4 PUBLIC include/)
target_link_libraries(test4 gtest_main)

add_executable(test5 tests/test5.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(test5 PUBLIC include/)
target_link_libraries(test5 gtest_main)

add_executable(test6 tests/test6.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(test6 PUBLIC include/)
target_link_libraries(test6 gtest_main)

add_executable(btest0 tests/btest0.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(btest0 PUBLIC include/)
target_link_libraries(btest0 gtest_main)

add_executable(btest1 tests/btest1.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(btest1 PUBLIC include/)
target_link_libraries(btest1 gtest_main)

add_executable(btest2 tests/btest2.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(btest2 PUBLIC include/)
target_link_libraries(btest2 gtest_main)

add_executable(btest3 tests/btest3.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(btest3 PUBLIC include/)
target_link_libraries(btest3 gtest_main)

add_executable(btest4 tests/btest4.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(btest4 PUBLIC include/)
target_link_libraries(btest4 gtest_main)

add_executable(btest5 tests/btest5.cpp src/DirectoryStatistics.cpp src/ThreadPool.cpp)
target_include_directories(btest5 PUBLIC include/)
target_link_libraries(btest5 gtest_main)

include(GoogleTest)
gtest_discover_tests(test0)
gtest_discover_tests(test1)
gtest_discover_tests(test2)
gtest_discover_tests(test3)
gtest_discover_tests(test4)
gtest_discover_tests(test5)
gtest_discover_tests(test6)

gtest_discover_tests(btest0)
gtest_discover_tests(btest1)
gtest_discover_tests(btest2)
gtest_discover_tests(btest3)
gtest_discover_tests(btest4)
gtest_discover_tests(btest5)
