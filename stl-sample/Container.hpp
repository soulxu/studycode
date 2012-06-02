#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_

#include <iosfwd>

template<class Seq>
class Container {
public:
    typename Seq::iterator begin() { return seq.begin(); }
    typename Seq::iterator end() { return seq.end(); }

private:
    Seq seq;
};

#endif
