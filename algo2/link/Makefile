all: link link_simple link_cpp list list2 reverse_list

link: link.c
	gcc link.c -o link

link_simple: link_simple.c
	gcc link_simple.c -o link_simple

link_cpp: link.h link.cc
	g++ link.cc -o link_cpp

list: list.cc list.h
	g++ list.cc -o list

list2: list2.cc list2.h
	g++ list2.cc -o list2

reverse_list: reverse_list.cpp 
	g++ reverse_list.cpp -o reverse_list

.PHONY: clean

clean:
	rm link link_simple list