# ThreadPool

## Introduce
- Implement a simple ThreadPool using c++11  
- Use Makefile to manage project

## Use posture
### Project Strcuture

ThreadPool :  

- ThreadPool.h 
- ThreadPool.cpp 
- main.cpp 
- Makefile

### Procedure
```
git clone https://github.com/zKris2/ThreadPool.git

make

# clean up *.o files
make clean

./ThreadPool
```

## Version Record
### First version

A simple ThreadPool framework that defines task function in main.cpp and add task via Function Pointer.

```
void func(){
	std::cout<<"test func ptr"<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main(){
	ThreadPool pool(3);
	pool.enqueue(func);
	return 0;
}
```

![img](images/1.png)


<hr>