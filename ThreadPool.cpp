#include "ThreadPool.h"
#include "utils/util.h"

#include <iostream>

ThreadPool::ThreadPool(int nums,int max_thread_num)
        :isStop(false),_thread_num(nums),_max_thread_num(max_thread_num)
{
        for(size_t i = 0; i < _thread_num; i++){
                newWorker();
        }
}

ThreadPool::~ThreadPool(){
        {
                std::unique_lock<std::mutex> lock(_mtx);
                isStop = true;
        }
        _condition.notify_all();
        for(std::thread &worker : _workers)
                worker.join();
        std::cout<<"ThreadPool is stopped!"<<std::endl;
}

void ThreadPool::newWorker(){
    _workers.emplace_back(
            [this]{
                    for(;;){
                            std::function<void()> task;
                            {
                                    std::unique_lock<std::mutex> lock(_mtx);
                                    _condition.wait(lock,[this]{return isStop||!_tasks.empty(); });
                                    if(isStop && _tasks.empty())
                                            return;
                                    // 使用 std::bind 创建一个 std::function<void()> 对象
                                    task = _tasks.front();
                                    _tasks.pop();       
                                    std::cout << "ThreadId[" << Util::getThreadId() << "]" << std::endl;
                            }
                            if(task)
                                    task(); // 调用 task 中的函数
                    }
            });
}

ThreadPool* globalPool = nullptr;

extern "C" void initializeThreadPool() {
    globalPool = new ThreadPool();
}

extern "C" void shutdownThreadPool() {
    delete globalPool;
    globalPool = nullptr;
}

extern "C" void enqueueTask(std::function<void()> task) {
    if (globalPool != nullptr) {
        globalPool->enqueue(task);
    }
}