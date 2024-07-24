#pragma once
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

using FuncPtr = void(*)();

class ThreadPool{
        private:
                std::vector<std::thread> _workers;
                std::queue<FuncPtr> _tasks;
                std::mutex _mtx;
                std::condition_variable _condition;

                bool isStop;
        public:
                ThreadPool(size_t nums);
                ~ThreadPool();
		void enqueue(FuncPtr func);
};
