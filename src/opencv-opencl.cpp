#include <vector>
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
	size_t localSize[]  = {8, 8};
	bool success = kernel.run(2, globalSize, localSize, sync);
	if(success) {
		std::cout << "Succeeded to run OpenCL kernel: " << __func__ << std::endl;
	} else {
		std::cout << "Failed to run OpenCL kernel: " << __func__ << std::endl;
	}
}

void dumpOpenCL() {
	if(!cv::ocl::haveOpenCL()) {
		std::cout << "OpenCL is not available, leaving..." << std::endl;
		return;
	}

	std::vector< cv::ocl::PlatformInfo > platform_info;
	cv::ocl::setUseOpenCL(true);
	cv::ocl::getPlatfomsInfo(platform_info);

	for (int i = 0; i < platform_info.size(); i++) {
		cv::ocl::PlatformInfo sdk = platform_info.at(i);
		for (int j = 0; j < sdk.deviceNumber(); j++) {
			cv::ocl::Device device;
			device.TYPE_GPU;
			sdk.getDevice(device, j);

			std::cout << "\n*********************\n Device " << i + 1 << std::endl;
			std::cout << "Vendor ID: " << device.vendorID() << std::endl;
			std::cout << "Vendor name: " << device.vendorName() << std::endl;
			std::cout << "Name: " << device.name() << std::endl;
			std::cout << "Driver version: " << device.driverVersion() << std::endl;
			std::cout << "available: " << device.available() << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "[-] GPU context" << std::endl;
	cv::ocl::Context context;
	if (!context.create(cv::ocl::Device::TYPE_GPU))
	{
		std::cout << "Failed creating the context..." << std::endl;
		return;
	}
	std::cout << context.ndevices() << " GPU devices are detected." << std::endl; //This bit provides an overview of the OpenCL devices you have in your computer
	for (int i = 0; i < context.ndevices(); i++)
	{
		cv::ocl::Device device = context.device(i);
		std::cout << "name:              " << device.name() << std::endl;
		std::cout << "available:         " << device.available() << std::endl;
		std::cout << "imageSupport:      " << device.imageSupport() << std::endl;
		std::cout << "OpenCL_C_Version:  " << device.OpenCL_C_Version() << std::endl;
		std::cout << std::endl;
	}

	std::cout << "[-] CPU context" << std::endl;
	cv::ocl::Context cpuContext;
	if (!cpuContext.create(cv::ocl::Device::TYPE_CPU))
	{
		std::cout << "Failed creating the context..." << std::endl;
		return;
	}
	std::cout << cpuContext.ndevices() << " CPU devices are detected." << std::endl; //This bit provides an overview of the OpenCL devices you have in your computer
	for (int i = 0; i < cpuContext.ndevices(); i++)
	{
		cv::ocl::Device device = cpuContext.device(i);
		std::cout << "name:              " << device.name() << std::endl;
		std::cout << "available:         " << device.available() << std::endl;
		std::cout << "imageSupport:      " << device.imageSupport() << std::endl;
		std::cout << "OpenCL_C_Version:  " << device.OpenCL_C_Version() << std::endl;
		std::cout << std::endl;
	}
}

void testOpenCLKernel() {
	dumpOpenCL();

#if 0
	//cv::ocl::Context context = cv::ocl::Context::getDefault();
	//cv::ocl::Device device = context.device(0);

	cv::ocl::Context context;
	//if(!context.create(cv::ocl::Device::TYPE_CPU)) {
	if(!context.create(cv::ocl::Device::TYPE_ALL)) {
		std::cout << "Failed to create context for CPU, leaving..." << std::endl;
		return;
	}

	std::cout << "*************************************************" << std::endl;
	for(int i=0; i<context.ndevices(); ++i) {
		cv::ocl::Device device = context.device(i);
		std::cout << "Name\t" << device.name() << std::endl;
		std::cout << "OpenCL\t" << device.OpenCL_C_Version() << std::endl;
		std::cout << std::endl;
	}
#endif

	helloWorld();
}

