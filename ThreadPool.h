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

                int _thread_num;
                int _max_thread_num;
        public:
                ThreadPool(int nums = 3,int max_thread_num = 10);
                ~ThreadPool();
		void enqueue(FuncPtr func);
                void newWorker();
};
