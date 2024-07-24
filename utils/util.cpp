#include "util.h"

std::thread::id Util::getThreadId(){
    return std::this_thread::get_id();
}