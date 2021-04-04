cmake_minimum_required(VERSION 3.0.0)
project(asiosigth VERSION 0.1.0)


add_subdirectory(boost)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#include_directories("boost/boost")

include(CTest)
enable_testing()

add_executable(asiosigth main.cpp )
target_link_libraries( asiosigth PRIVATE Threads::Threads  boost)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
