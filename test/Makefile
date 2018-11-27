CC=gcc
RM=rm
MKDIR=mkdir 
CUR_DIR=$(shell pwd)
LD_LIBRARY_PATH=${CUR_DIR}/../build
export LD_LIBRARY_PATH

.PHONY: all cleanup runTest

all: testCaesar runTest

testCaesar: testCaesar.c
	${CC} ${FLAGS} -I${CUR_DIR}/../inc -L${CUR_DIR}/../build -lcaesar $< -o $@

cleanup:
	${RM} -f *.o testCaesar 
	${MKDIR} bin

runTest: testCaesar
	@echo "Run tests ..."
	@./testCaesar
