PYTHON_VER=2.6

all:example.so

example.so: example.o
	$(CC) -lpthread -shared -o $@ $?

example.o: example.c
	$(CC) -c -I/usr/include/python$(PYTHON_VER) -I/usr/lib/python$(PYTHON_VER)/config $?

.PHONY:clean

clean:
	rm example.so example.o
