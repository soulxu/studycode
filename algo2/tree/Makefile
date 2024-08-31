all: tree array_tree

tree: tree.cc tree.h
	g++ tree.cc -o tree

array_tree: array_tree.cc array_tree.h
	g++ array_tree.cc -o array_tree

.PHONY: clean 

clean:
	rm tree array_tree