#ifndef _VECTOR_H_
#define _VECTOR_H_

template <class T>
class Vector {
public:
    Vector();
    ~Vector();

    void push_back(T t) {
    
    }

private:
    char *mem;
    size_t size;
    size_t used;
};

#endif
