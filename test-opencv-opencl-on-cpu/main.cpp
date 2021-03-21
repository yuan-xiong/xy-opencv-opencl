#include <iostream>
#include <fstream>
//#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>

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

void test_opencv_opencl_default() {
	std::cout << "[enter] " << __func__ << std::endl;

	cv::ocl::Context context = cv::ocl::Context::getDefault();
	std::cout << __func__ << " device:\t" << context.device(0).name() << std::endl;

	test_hello_world();
}

int main() {
	std::cout << "[enter] " << __func__ << std::endl;

	test_opencv_opencl_default();
	test_opencv_opencl_cpu();
	return 0;
}
