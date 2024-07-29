cmake_minimum_required(VERSION 3.10)

project(Util)

# 设置C++标准为 C++11
set(CMAKE_CXX_STANDARD 11)

# 指定源文件
add_library(Util SHARED util.cpp)

# 链接必要的库（如果有）
target_link_libraries(Util PRIVATE ${CMAKE_THREAD_LIBS_INIT})
