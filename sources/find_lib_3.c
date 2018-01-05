#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/ptrace.h>

int main(int argc, char **argv)
{
	// "./____libreadline.so" ^ 'B'
	char path[] = {
		0x6C, 0x6D, 0x1D, 0x1D, 0x1D, 0x1D, 0x2E, 0x2B,
		0x20, 0x30, 0x27, 0x23, 0x26, 0x2E, 0x2B, 0x2C,
		0x27, 0x6C, 0x31, 0x2D, 0x42
	};
	// "history_get" ^ 'B'
	char func[] = {
		0x2A, 0x2B, 0x31, 0x36, 0x2D, 0x30, 0x3B, 0x1D,
		0x25, 0x27, 0x36, 0x42
	};

	int i;

	for(i = 0; i < sizeof(path); ++i)
		path[i] ^= 'B';

	for(i = 0; i < sizeof(func); ++i)
		func[i] ^= 'B';

	if(ptrace(PTRACE_TRACEME) == -1) {
		printf("Sorry, no debugger allowed this time...\n");
		exit(-1);
	}

	if(getenv("LD_DEBUG")) {
		printf("Sorry, no LD_DEBUG allowed this time...\n");
		exit(-1);
	}

	void *dl_h = dlopen(path, RTLD_LAZY);

	if(!dl_h) {
		printf("Failed to find needed lib :(\n");
		exit(-1);
	}

	void *addr = dlsym(dl_h, func);
	if(!addr) {
		printf("Failed to find needed function in the lib :(\n");
		exit(-1);
	}

	printf("Function %s is mapped at address: %p\n", func, addr);

	return 0;
}
