SUBDIRS=src test
all: $(SUBDIRS)
	
$(SUBDIRS):
	make -C $@

.PHONY: $(SUBDIRS)
