#include "ThreadPool.h"
#include <iostream>

void func(){
	std::cout<<"test func ptr"<<std::endl;
	// while (1)
	// {
	// 	/* code */
	// }
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main(){
	ThreadPool pool(3);
	pool.enqueue(func);
	return 0;
}
