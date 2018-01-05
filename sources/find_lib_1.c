#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
	void *dl_h = dlopen("./libcap.so", RTLD_LAZY);

	if(!dl_h) {
		printf("Failed to find needed lib :(\n");
		exit(-1);
	}

	void *addr = dlsym(dl_h, "cap_init");
	if(!addr) {
		printf("Failed to find needed function in the lib :(\n");
		exit(-1);
	}

	printf("Function cap_init is mapped at address: %p\n", addr);

	return 0;
}
