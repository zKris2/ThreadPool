#include "ThreadPool.h"
#include <iostream>

void func(){
	//std::cout<<"test func ptr"<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

extern "C" void test(); 

int main(int argc,char* argv[]){
	ThreadPool pool;
	
	for (size_t i = 0; i < 11; i++)
	{
		pool.enqueue(func);
	}

	return 0;
}
