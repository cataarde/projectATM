#ifndef COLLECTION_TPP
#define COLLECTION_TPP

#include "Collection.h"
#include <iostream>

template <typename TElem>
Collection<TElem>::Collection() {
    capacity = 5;
    elems = new pereche[capacity];
    len = 0;
}

template <typename TElem>
TElem Collection<TElem>::getAt(int position) {
    return elems[position].elem;
}

template <typename TElem>
Collection<TElem>::~Collection() {
    delete[] elems;
}

template <typename TElem>
void Collection<TElem>::add(TElem elem) {
    bool found = false;
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) {
            elems[i].frecv++;
            found = true;
            break;
        }
    }
    if (!found) {
        if (len == capacity) {
            resize(2 * capacity);
        }

        elems[len] = pereche{elem, 1};
        len++;
    }
}

template <typename TElem>
void Collection<TElem>::resize(int new_size) {
    if (new_size < len) return;

    capacity = new_size;
    pereche<TElem>* temp = new pereche[new_size];
    for (int i = 0; i < len; i++) {
        temp[i] = elems[i];
    }
    delete[] elems;
    elems = temp;
}

template <typename TElem>
bool Collection<TElem>::remove(TElem elem) {
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) {
            elems[i].frecv--;

            if (elems[i].frecv == 0) {
                for (int j = i + 1; j < len; j++) {
                    elems[j - 1] = elems[j];
                }
                len--;
            }
            return true;
        }
    }
    return false;
}

template <typename TElem>
bool Collection<TElem>::search(TElem elem) {
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) {
            return true;
        }
    }
    return false;
}

template <typename TElem>
int Collection<TElem>::size() {
    return len;
}

template <typename TElem>
int Collection<TElem>::nrOccurrences(TElem elem) {
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) {
            return elems[i].frecv;
        }
    }
    return 0;
}

template <typename TElem>
void Collection<TElem>::print_all()
{
    for (int i = 0; i < len; i++)
        std::cout<<elems[i].elem<<" "<<elems[i].frecv<<"\n"  ;
}

#endif //COLLECTION_TPP
