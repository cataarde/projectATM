#ifndef ITERATOR_H
#define ITERATOR_H

#include "Set.h"

template<typename TElem>
class Iterator {
private:
    const Multime<TElem>& multime;
    int position;

public:
    Iterator(const Multime<TElem>& m);

    void first();
    void next();
    bool valid() const;
    TElem current() const;
};

#include "Iterator.tpp"
#endif //ITERATOR_H
