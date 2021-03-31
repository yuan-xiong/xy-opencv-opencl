//#include "../second.cl"
//#include "/home/xy18/yuan/test/opencl/opencv-opencl/test-opencv-header-for-opencl/build-xy/second.cl"
//#include "second.hpp"

__kernel void hello_world(const int input) {
	size_t gid0 = get_global_id(0);
	size_t gid1 = get_global_id(1);

	size_t gpid0 = get_group_id(0);
	size_t gpid1 = get_group_id(1);

	size_t lid0 = get_local_id(0);
	size_t lid1 = get_local_id(1);

	printf("[kernel hello_world (%2d,%2d)] group(%2d,%2d), local(%2d,%2d)\n", gid0,gid1, gpid0,gpid1, lid0,lid1);
	hello_again(input);
}
