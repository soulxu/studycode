CFLAGS+=-g

all: tree benchmark

tree: main.o
	$(CXX) -o tree main.o

benchmark: ktime.h benchmark.o
	$(CXX) -o benchmark benchmark.o

benchmark.o:
	$(CXX) -c -o benchmark.o benchmark.cpp

main.o: main.cpp node.h array.h stack.h
	$(CXX) -c -o main.o $(CFLAGS) main.cpp

.PHONY: clean

clean:
	rm tree *.o benchmark
