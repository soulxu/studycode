test2: LinkList.hpp

test: test.o Date.o Container.hpp
	$(CXX) -o $@ $^

Date.o: Date.cpp Date.h
	$(CXX) $^ -c 

.PHONY:clean

clean:
	rm *.o test
