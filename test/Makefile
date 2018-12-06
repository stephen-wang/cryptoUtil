CC=gcc
CFLAGS?=-Wall -g
CRYPTOUTIL_DIR?=$(shell pwd)/..
LD_LIBRARY_PATH=${CRYPTOUTIL_DIR}/build
export LD_LIBRARY_PATH
RM?=rm

.PHONY: all clean runTest
all: testUtils testCaesar testVigenere runTest

testUtils: testUtils.c ${CRYPTOUTIL_DIR}/src/utils.c
	${CC} ${CFLAGS} -I${CRYPTOUTIL_DIR}/inc $^ -o $@

testCaesar: testCaesar.c
	${CC} ${CFLAGS} -I${CRYPTOUTIL_DIR}/inc $< -L${CRYPTOUTIL_DIR}/build -lcryptoUtil -o $@

testVigenere: testVigenere.c
	${CC} ${CFLAGS} -I${CRYPTOUTIL_DIR}/inc $< -L${CRYPTOUTIL_DIR}/build -lcryptoUtil -o $@

clean:
	${RM} -f *.o testUtils testCaesar testVigenere

runTest: testCaesar
	@echo  "\n*** Run tests ***"
	@./testUtils
	@./testCaesar
	@./testVigenere
	@echo  "*** All tests passed ***\n"
