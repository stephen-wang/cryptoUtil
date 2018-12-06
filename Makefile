CC=gcc
CFLAGS= -Wall -g
MAKE=make
MKDIR=mkdir
RM=rm
CRYPTOUTIL_DIR=$(shell pwd)
export

SUBDIRS=src test

.PHONY: $(SUBDIRS) all clean

all: $(SUBDIRS)
	
$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in ${SUBDIRS}; do \
	    $(MAKE) -C $$dir clean;\
	done

