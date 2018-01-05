LDFLAGS=-ldl
OUT_DIR=binaries

all: directory find_lib_1 find_lib_2 find_lib_3

directory: ${OUT_DIR}

${OUT_DIR}:
	mkdir -p ${OUT_DIR}

find_lib_1: sources/find_lib_1.c
	gcc -o binaries/find_lib_1 sources/find_lib_1.c -g $(LDFLAGS)

find_lib_2: sources/find_lib_2.c
	gcc -o binaries/find_lib_2 sources/find_lib_2.c $(LDFLAGS)

find_lib_3: sources/find_lib_3.c
	gcc -o binaries/find_lib_3 sources/find_lib_3.c $(LDFLAGS)
	strip binaries/find_lib_3
