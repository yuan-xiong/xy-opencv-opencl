#include "opencv-opencl.hpp"

void helloWorld() {
	static cv::ocl::Kernel kernel;
	if(kernel.empty()) {
		//std::string file = "helloWorld.cl";
		std::string file = "/home/xy18/yuan/test/opencl/opencv-opencl/src/helloWorld.cl";
		std::ifstream ifs(file);
		if(ifs.fail()) {
			std::cout << "Failed to load OpenCL file: " << file << ", leaving..." << std::endl;
			return;
		}
		std::string kernelSource((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		cv::ocl::ProgramSource source(kernelSource);
		int count = 1000;
		//kernel.create(file, source, cv::format("-D COUNT=%d", 1000));
		//kernel.create("hello_world", source, cv::format("-D COUNT=1000"));
		kernel.create("helloWorld", source, cv::format("-D COUNT=%d", count));
	}

	cv::UMat arg(1, 1, CV_32SC1, 1);
	kernel.set(0, cv::ocl::KernelArg::PtrReadOnly(arg));

	bool sync = true;
	size_t globalSize[] = {32, 32};
	size_t localSize[]  = {16, 16};
	bool success = kernel.run(2, globalSize, localSize, sync);
	if(success) {
		std::cout << "Succeeded to run OpenCL kernel: " << __func__ << std::endl;
	} else {
		std::cout << "Failed to run OpenCL kernel: " << __func__ << std::endl;
	}
}

void testOpenCLKernel() {
	helloWorld();
}

