#include "ThreadPool.h"
#include "utils/util.h"

#include <iostream>

ThreadPool::ThreadPool(int nums,int max_thread_num)
        :_thread_num(nums),_max_thread_num(max_thread_num),isStop(false)
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
                                void(*task)(void);
                                {
                                        std::unique_lock<std::mutex> lock(_mtx);
                                        _condition.wait(lock,[this]{return isStop||!_tasks.empty(); });
                                        if(isStop && _tasks.empty())
                                                return;
                                        task = std::move(_tasks.front());
                                        _tasks.pop();	
                                        std::cout << "ThreadId[" << Util::getThreadId() << "]" << std::endl;
                                }
                                if(task)
                                        task();
                        }
                });
}

void ThreadPool::enqueue(FuncPtr func){
        {
                std::unique_lock<std::mutex> lock(_mtx);

                if(isStop)
                        throw std::runtime_error("enqueue on stopped ThreadPool");
                if(_workers.size() >= _thread_num && _thread_num < _max_thread_num){
                        newWorker();
                        _thread_num++;
                }
                _tasks.emplace(func);
        }
        _condition.notify_one();
}
