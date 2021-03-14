#include <iostream>
#include <chrono>
#include "threads.hpp"

void threadCallback(int *threadId) {
	int count = 0;

	for(int i=0; i<M; ++i) {
		for(int j=0; j<N; ++j) {
			//std::this_thread::sleep_for(std::chrono::milliseconds(30));

			//std::cout << threadId << std::endl;
			//std::cout << __func__ << "[" << *threadId << "] count:\t" << count++ << std::endl;
		}
	}
}
