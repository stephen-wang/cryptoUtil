CC=gcc
CFLAGS?=-Wall -g
CRYPTOUTIL_DIR?=$(shell pwd)/..
LD_LIBRARY_PATH=${CRYPTOUTIL_DIR}/build
export LD_LIBRARY_PATH
RM?=rm
MKDIR?=mkdir

.PHONY: all clean runTest
all: testUtils testCaesar testVigenere runTest

testUtils: testUtils.c
	${CC} ${CFLAGS} -I${CRYPTOUTIL_DIR}/inc $< -L${CRYPTOUTIL_DIR}/build -lcryptoUtil -o build/$@

testCaesar: testCaesar.c
	${CC} ${CFLAGS} -I${CRYPTOUTIL_DIR}/inc $< -L${CRYPTOUTIL_DIR}/build -lcryptoUtil -o build/$@

testVigenere: testVigenere.c
	${CC} ${CFLAGS} -I${CRYPTOUTIL_DIR}/inc $< -L${CRYPTOUTIL_DIR}/build -lcryptoUtil -o build/$@

clean:
	${RM} -rf *.o build/
	${MKDIR} build 

runTest: testCaesar
	@echo  "\n*** Run tests ***"
	@build/testUtils
	@build/testCaesar
	@build/testVigenere
	@echo  "*** All tests passed ***\n"
