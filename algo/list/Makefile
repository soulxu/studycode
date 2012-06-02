VPATH=../container
CFLAGS=-I../container -g 
LDFLAGS=-g

all: polynomial polynomial_c calc

polynomial: polynomial.o clist.o container.o c_type.o c_debug.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm *.o polynomial polynomial_c calc
