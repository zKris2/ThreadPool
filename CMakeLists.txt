cmake_minimum_required(VERSION 3.10)

project(ThreadPool)

# 设置C++标准为 C++11
set(CMAKE_CXX_STANDARD 11)

find_library(UTIL_LIB libUtil.so PATHS ${CMAKE_SOURCE_DIR})

# 指定源文件
add_library(ThreadPool SHARED ThreadPool.cpp)

# 如果找到了UtilShared库，则添加可执行目标
if(UTIL_LIB)
   target_link_libraries(ThreadPool ${UTIL_LIB})
else()
   message(FATAL_ERROR "UtilShared library not found")
endif()
