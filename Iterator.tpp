#include "Iterator.h"

template<class TElem>
Iterator<TElem>::Iterator(const Multime<TElem>& m) : multime(m), position(0) {}

template <class TElem>
void Iterator<TElem>::first() {
    position = 0;
}

template <class TElem>
void Iterator<TElem>::next() {
    if (valid()) {
        position++;
    }
}

template <class TElem>
bool Iterator<TElem>::valid() const {
    return (0 <= position && position < multime.size());
}

template <class TElem>
TElem Iterator<TElem>::current() const {
    return multime.getElem(position);
}


