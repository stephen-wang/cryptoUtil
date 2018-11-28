C = gcc
CFLAGS ?= -Wall -g
CRYPTOUTIL_DIR ?= $(shell pwd)/..
RM ?= rm

.PHONY: all clean
all: libcaesar.so

libcaesar.so: caesar.c clean
	rm -rf ${CRYPTOUTIL_DIR}/build/*
	${CC} ${CFLAGS} -fPIC -shared -I${CRYPTOUTIL_DIR}/inc $< -o ${CRYPTOUTIL_DIR}/build/$@

clean:
	${RM} -rf *.o

