#pragma once
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>

class ThreadPool{
        private:
                std::vector<std::thread> _workers;
                std::queue<std::function<void()>> _tasks;
                std::mutex _mtx;
                std::condition_variable _condition;

                bool isStop;

                int _thread_num;
                int _max_thread_num;
        public:
                ThreadPool(int nums = 3,int max_thread_num = 10);
                ~ThreadPool();

                template<typename Func, typename... Args>
                void enqueue(Func&& func, Args&&... args){
                        {
                                std::unique_lock<std::mutex> lock(_mtx);
                                
                                if(isStop)
                                        throw std::runtime_error("enqueue on stopped ThreadPool");

                                if(_workers.size() >= _thread_num && _thread_num < _max_thread_num){
                                        newWorker();
                                        _thread_num++;
                                }
                                _tasks.push(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
                        }
                        _condition.notify_one();
                }

                 // 新的 enqueue 方法，接受 std::function<void()>
                 template< typename... Args>
                void enqueue(std::function<void()> task,Args&&... args) {
                        {
                                std::unique_lock<std::mutex> lock(_mtx);
                                
                                if(isStop)
                                        throw std::runtime_error("enqueue on stopped ThreadPool");

                                if(_workers.size() >= _thread_num && _thread_num < _max_thread_num){
                                        newWorker();
                                        _thread_num++;
                                }
                                 _tasks.push(task);  // 将任务添加到队列
                        }
                        _condition.notify_one();
                }
        private:
                void newWorker();
};
