#include <iostream>
#include <chrono>
#include "threads.hpp"

void threadCallback(int *threadId) {
	int count = 0;

	for(int i=0; i<M; ++i) {
		if(i % 1000 == 0)
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
		for(int j=0; j<N; ++j) {

			//std::cout << threadId << std::endl;
			//std::cout << __func__ << "[" << *threadId << "] count:\t" << count++ << std::endl;
		}
	}
}
