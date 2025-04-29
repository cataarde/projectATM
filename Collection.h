#ifndef COLLECTION_H
#define COLLECTION_H

template<typename TElem>
struct pereche {
    TElem elem;
    int frecv;
};

template<typename TElem>
class Collection {
private:
    pereche<TElem>* elems;
    int len;
    int capacity;

    void resize(int);

public:
    Collection();
    ~Collection();

    void add(TElem elem);
    bool remove(TElem elem);
    bool search(TElem elem);
    int size();
    int nrOccurrences(TElem elem);
    TElem getAt(int position);

    void print_all();
};
#include "Collection.tpp"

#endif //COLLECTION_H
