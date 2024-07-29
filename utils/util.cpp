#include "util.h"

std::thread::id Util::getThreadId(){
    return std::this_thread::get_id();
}

extern "C" std::thread::id getThreadId(){
    return std::this_thread::get_id();
}