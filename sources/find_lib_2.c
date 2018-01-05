#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

int main(int argc, char **argv)
{
	char path[] = {0x6F, 0x6E, 0x1E, 0x1E, 0x2D, 0x28, 0x23, 0x39, 0x2C, 0x2D, 0x73, 0x6F, 0x32, 0x2E, 0x41};
	int i;
	const char *func_name = "xmlParseFile";

	for(i = 0; i < sizeof(path); ++i)
		path[i] ^= 'A';

	void *dl_h = dlopen(path, RTLD_LAZY);

	if(!dl_h) {
		printf("Failed to find needed lib :(\n");
		exit(-1);
	}

	void *addr = dlsym(dl_h, func_name);
	if(!addr) {
		printf("Failed to find needed function in the lib :(\n");
		exit(-1);
	}

	printf("Function %s is mapped at address: %p\n", func_name, addr);

	return 0;
}
