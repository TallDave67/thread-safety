cmake_minimum_required(VERSION 3.16)
project(thread-safety)

set(CMAKE_VERBOSE_MAKEFILE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-std=c++20)
add_compile_options(-stdlib=libstdc++)

add_executable(thread-safety
  runnable.cpp  
  logger.cpp 
  main.cpp
)
target_link_libraries(thread-safety pthread)
