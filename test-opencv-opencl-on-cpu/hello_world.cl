__kernel void hello_world(const int input) {
	size_t gid0 = get_global_id(0);
	size_t gid1 = get_global_id(1);

	size_t gpid0 = get_group_id(0);
	size_t gpid1 = get_group_id(1);

	size_t lid0 = get_local_id(0);
	size_t lid1 = get_local_id(1);

	printf("[kernel (%2d,%2d)] group(%2d,%2d), local(%2d,%2d), hello_world\n", gid0,gid1, gpid0,gpid1, lid0,lid1);
}
