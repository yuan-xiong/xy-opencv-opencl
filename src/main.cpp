#include <iostream>
#include <vector>
#include "threads.hpp"

int nThreads = 1;

void test_loop();
void test_loop_10();
void test_loop_10K();
void test_loop_1M();
void test_loop_1G();

void test_loop_1G() {
	for(int i=0; i<1000*1000*1000; ++i) {
		test_loop_10();
	}
}

void test_loop_1M() {
	for(int i=0; i<1000*1000; ++i) {
		test_loop_10K();
	}
}

void test_loop_10K() {
	for(int i=0; i<10*1000; ++i) {
	}
}

void test_loop_10() {
	for(int i=0; i<10; ++i) {
		//test_loop_1G();
	}
}

void test_loop() {
	std::cout << "[enter] " << __func__ << std::endl;

	//test_loop_10();
	//test_loop_1G();
	//test_loop_10K();
	test_loop_1M();
}

void test_threads() {
	std::cout << "[enter] " << __func__ << std::endl;
	// get cpu cores
	//nThreads = std::thread::hardware_concurrency();
	nThreads = 7;
	std::vector<int> threadIds(nThreads);
	std::vector<std::thread> threads(nThreads);

	for(int i=0; i<nThreads; ++i) {
		threadIds[i] = i;
		std::cout << "[start thread] " << threadIds[i] << std::endl;
		threads[i] = std::thread(threadCallback, &threadIds[i]);
	}
	for(int i=0; i<nThreads; ++i) {
		threads[i].join();
	}
}

int main(int argc, char **argv) {
	std::cout << "[enter] " << __func__ << std::endl;

	//test_loop();
	test_threads();
	return 0;
}
