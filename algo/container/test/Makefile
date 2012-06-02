
CFLAGS+=-I../ -g
VPATH+=../

all: test_carray test_container

test_carray: test_carray.c carray.o container.o c_debug.o c_type.o
	$(CC) $(CFLAGS) $^ -o $@

test_container: test_container.c carray.o clist.o container.o c_debug.o c_type.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm test_carray
