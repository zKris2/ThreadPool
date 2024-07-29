# CMake最低版本号要求
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(test_threadpool_so)

# 设置C++标准为 C++11
set(CMAKE_CXX_STANDARD 11)

# 查找ThreadPool共享库
find_library(THREADPOOL_LIB libThreadPool.so PATHS ${CMAKE_SOURCE_DIR})

add_executable(test_threadpool_so test_ThreadPool.cpp)

# 如果找到了库，则添加可执行目标
if(THREADPOOL_LIB)
    target_link_libraries(test_threadpool_so ${THREADPOOL_LIB} dl pthread)
else()
    message(FATAL_ERROR "ThreadPool library not found")
endif()
