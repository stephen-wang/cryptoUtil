CC=gcc
CFLAGS= -Wall -g -fPIC
RM=rm
CUR_DIR=$(shell pwd)

.PHONY: all cleanup
all: libcaesar.so caesar

libcaesar.so: caesar.c
	${CC} ${CFLAGS} -shared -I${CUR_DIR}/../inc $< -o ${CUR_DIR}/../build/$@

caesar: caesar.c
	${CC} -g -I${CUR_DIR}/../inc $< -o $@

cleanup: libcaesar.so 
	rm -rf *.o

