#include <iostream>
#include <fstream>
//#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>
#include <thread>

void test_hello_world() {
	std::cout << "[enter] " << __func__ << std::endl;
	
	std::string file = "../hello_world.cl";
	std::ifstream ifs(file);
	if(ifs.fail()) {
		std::cout << "Failed to load OpenCL file:\t" << file << std::endl;
		return;
	}

	std::string source((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	cv::ocl::ProgramSource programSource(source.c_str());

	cv::ocl::Program program;
	std::string buildOption = cv::format("-D TIMES=%d", 1000);
	std::string errmsg;
	program.create(programSource, buildOption, errmsg);

	cv::ocl::Kernel kernel("hello_world" ,program);
	int input = 100;
	kernel.set(0, input);

	size_t global_size[] = {8, 8};
	size_t local_size[]  = {2, 4};
	bool success = kernel.run(2, global_size, local_size, true);
	if(success) {
		std::cout << "Running OpenCL kernel successfully." << std::endl;
	} else {
		std::cout << "Running OpenCL kernel failed." << std::endl;
	}
}

#if 0
void test_opencv_opencl_cpu() {
	std::cout << "[enter] " << __func__ << std::endl;

	cv::ocl::OpenCLExecutionContext execContext = cv::ocl::OpenCLExecutionContext::getCurrent();
	std::cout << __func__ << " current device:\t" << execContext.getDevice().name() << std::endl;
	
	//cv::ocl::Context context = cv::ocl::Context::create(":GPU:0");
	cv::ocl::Context context = cv::ocl::Context::create(":CPU:0");
	execContext = cv::ocl::OpenCLExecutionContext::create(context, context.device(0));
	std::cout << __func__ << " new device:\t" << execContext.getDevice().name() << std::endl;

	std::cout << __func__ << " set execContext of device:\t" << execContext.getDevice().name() << std::endl;
	cv::ocl::OpenCLExecutionContextScope scope(execContext);

	test_hello_world();
}
#endif

void test_opencv_opencl_default() {
	std::cout << "[enter] " << __func__ << std::endl;

	//cv::ocl::Context context = cv::ocl::Context::getDefault();
	//std::cout << __func__ << " device:\t" << context.device(0).name() << std::endl;

	test_hello_world();
}

void thread_do(int threadid) {
	int count = 0;

	for(int i=0; i<1000*1000; ++i) {
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::cout << __func__ << " " << threadid << ": " << ++count << std::endl;

		// thread unsafe here
		cv::ocl::OpenCLExecutionContext execContext = cv::ocl::OpenCLExecutionContext::getCurrent();
		std::cout << __func__ << " current device:\t" << execContext.getDevice().name() << std::endl;

		cv::ocl::Context context;
		if(threadid % 2) {
			std::cout << __func__ << " " << threadid << ": create GPU context..." << std::endl;
			context = cv::ocl::Context::create(":GPU:0");
		} else {
			std::cout << __func__ << " " << threadid << ": create CPU context..." << std::endl;
			context = cv::ocl::Context::create(":CPU:0");
		}

		execContext = cv::ocl::OpenCLExecutionContext::create(context, context.device(0));
		std::cout << __func__ << " new device:\t" << execContext.getDevice().name() << std::endl;

		std::cout << __func__ << " set execContext of device:\t" << execContext.getDevice().name() << std::endl;
		cv::ocl::OpenCLExecutionContextScope scope(execContext);
	}
}

void test_opencv_opencl_multiple_contexts_with_multiple_devices() {
	std::cout << "[enter] " << __func__ << std::endl;

	const int N = 20;
	std::vector<std::thread> threads(N);

	for(int i=0; i<N; ++i) {
		threads[i] = std::thread(thread_do, i);
	}
	for(int i=0; i<N; ++i) {
		threads[i].join();
	}

	std::cout << "All threads joined." << std::endl;
}

void test_opencv_header_for_opencl() {
	std::cout << "[enter] " << __func__ << std::endl;

	test_hello_world();
}

int main() {
	//std::cout << "[enter] " << __func__ << std::endl;

	//test_opencv_opencl_default();
	//test_opencv_opencl_cpu();

	//test_opencv_opencl_multiple_contexts_with_multiple_devices();
	test_opencv_header_for_opencl();

	return 0;
}
