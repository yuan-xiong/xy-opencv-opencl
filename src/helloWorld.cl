__kernel void helloWorld(__global const int * restrict arg) {
	size_t gid0 = get_global_id(0);
	size_t gid1 = get_global_id(1);
	//printf("[OpenCL kernel (%ld,%ld)] I am in.\n", gid1,gid0);
	//printf("[OpenCL kernel (%ld,%ld)] I am leaving...\n", gid1,gid0);
}
