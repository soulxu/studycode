CFLAGS += -I. -g

all: c

c: main.o container.o c_type.o clist.o c_debug.o carray.o 
	$(CC) $^ -o $@

.PHONY: clean

clean:
	rm *.o c
