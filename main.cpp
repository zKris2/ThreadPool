#include "ThreadPool.h"

#include <iostream>
#include <memory>

void func(int num){
    std::cout<<num<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
void func2(int num1,int num2){
    std::cout<<num1<<","<<num2<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

std::shared_ptr<ThreadPool> pool;

int main(int argc,char* argv[]){
    
    pool = std::make_shared<ThreadPool>();

    for (size_t i = 0; i < 11; i++)
    {
        pool->enqueue(func2,i,i+1);
    }

    return 0;
}
