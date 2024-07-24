#include <iostream>

extern "C" {
    void test(){
        std::cout << "test libfunc" << std::endl;
    }
}