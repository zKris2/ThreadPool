#include <iostream>
#include <functional>
#include <dlfcn.h>
#include <thread>

// extern "C" void initializeThreadPool();

// extern "C" void shutdownThreadPool();

// extern "C" void enqueueTask(std::function<void()> task);


void func(){
    std::cout << "test libso" << std::endl; 
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
void func1(int num){
    std::cout<<num<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
void func2(int num1,int num2){
    std::cout<<num1<<","<<num2<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
    // 加载共享库
    void* handle = dlopen("libThreadPool.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    // 清除之前的错误
    dlerror();

    // 获取函数指针
    typedef void (*initializeThreadPool_t)();
    initializeThreadPool_t initializeThreadPool = (initializeThreadPool_t)dlsym(handle, "initializeThreadPool");
    if (!initializeThreadPool) {
        std::cerr << "Cannot load symbol 'initializeThreadPool': " << dlerror() << '\n';
        dlclose(handle);
        return 1;
    }

    // 初始化线程池
    initializeThreadPool();

    // 现在可以调用 enqueueTask，例如：
    // 注意：你需要确保有一个正确的 std::function<void()> 传递给 enqueueTask
    typedef void (*enqueueTask_t)(std::function<void()>);
    enqueueTask_t enqueueTask = (enqueueTask_t)dlsym(handle, "enqueueTask");
    if (!enqueueTask) {
        std::cerr << "Cannot load symbol 'enqueueTask': " << dlerror() << '\n';
        dlclose(handle);
        return 1;
    }
    for(int i=0;i<11;i++)
        enqueueTask(func);

    // 关闭线程池
    typedef void (*shutdownThreadPool_t)();
    shutdownThreadPool_t shutdownThreadPool = (shutdownThreadPool_t)dlsym(handle, "shutdownThreadPool");
    if (!shutdownThreadPool) {
        std::cerr << "Cannot load symbol 'shutdownThreadPool': " << dlerror() << '\n';
        dlclose(handle);
        return 1;
    }

    shutdownThreadPool();

    // 卸载共享库
    dlclose(handle);

    return 0;
}
