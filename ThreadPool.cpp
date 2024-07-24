#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(size_t nums){
        isStop = false;

        for(size_t i=0;i<nums;i++){
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
					}
					if(task)
						task();
                                }
                        });
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

void ThreadPool::enqueue(FuncPtr func){
	std::cout<<"new task"<<std::endl;
        {
                std::unique_lock<std::mutex> lock(_mtx);

                if(isStop)
                        throw std::runtime_error("enqueue on stopped ThreadPool");
                _tasks.emplace(func);
        }
        _condition.notify_one();
}
