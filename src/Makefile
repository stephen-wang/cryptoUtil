C = gcc
CFLAGS ?= -Wall -g
CRYPTOUTIL_DIR ?= $(shell pwd)/..
RM ?= rm

.PHONY: all clean
all: libcryptoUtil.so

libcryptoUtil.so: caesar.c vigenere.c railfence.c utils.c
	@if [ ! -d ${CRYPTOUTIL_DIR}/build ]; then mkdir ${CRYPTOUTIL_DIR}/build/; fi
	@rm -rf ${CRYPTOUTIL_DIR}/build/*
	${CC} ${CFLAGS} -fPIC -shared -I${CRYPTOUTIL_DIR}/inc $^ -o ${CRYPTOUTIL_DIR}/build/$@

clean:
	${RM} -rf *.o

