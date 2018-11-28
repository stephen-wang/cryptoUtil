CC=gcc
CFLAGS?=-Wall -g
CRYPTOUTIL_DIR?=$(shell pwd)/..
LD_LIBRARY_PATH=${CRYPTOUTIL_DIR}/build
export LD_LIBRARY_PATH
RM?=rm

.PHONY: all clean runTest
all: testCaesar runTest

testCaesar: testCaesar.c clean
	${CC} ${CFLAGS} -I${CRYPTOUTIL_DIR}/inc $< -L${CRYPTOUTIL_DIR}/build -lcaesar -o $@

clean:
	${RM} -f *.o testCaesar 

runTest: testCaesar
	@echo  "\n*** Run tests ***"
	@./testCaesar
	@echo  "*** All tests passed ***\n"
