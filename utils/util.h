#pragma once
#include <thread>

class Util
{
public:
    static std::thread::id getThreadId();
};