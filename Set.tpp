#include "Set.h"


template<typename TElem>
Multime<TElem>::Multime(Comparator<TElem> cmpFunc) {
    capacitate = 10;
    noElems = 0;
    elems = new TElem[capacitate];
    cmp = cmpFunc;
}

template<typename TElem>
Multime<TElem>::~Multime() {
    delete[] elems;
}

template<typename TElem>
void Multime<TElem>::resize() {
    capacitate *= 2;
    TElem* newElems = new TElem[capacitate];
    for (int i = 0; i < noElems; i++) {
        newElems[i] = elems[i];
    }
    delete[] elems;
    elems = newElems;
}

template<typename TElem>
int Multime<TElem>::search(const TElem& e) const {
    int st = 0, dr = noElems - 1, poz = 0;
    while (st <= dr) {
        int m = (st + dr) / 2;
        if (!cmp(elems[m], e) && !cmp(e, elems[m])) // egal
            return m;
        if (cmp(elems[m], e)) {
            poz = m + 1;
            st = m + 1;
        } else {
            dr = m - 1;
        }
    }
    return poz;
}

template<typename TElem>
bool Multime<TElem>::ifExist(const TElem& e) const {
    int st = 0, dr = noElems - 1;
    while (st <= dr) {
        int m = (st + dr) / 2;
        if (!cmp(elems[m], e) && !cmp(e, elems[m])) // egal
            return true;
        if (cmp(elems[m], e))
            st = m + 1;
        else
            dr = m - 1;
    }
    return false;
}

template<typename TElem>
void Multime<TElem>::add(const TElem& e) {
    if (ifExist(e)) return;

    if (noElems == capacitate)
        resize();

    int poz = search(e);
    for (int i = noElems; i > poz; --i)
        elems[i] = elems[i - 1];

    elems[poz] = e;
    noElems++;
}

template<typename TElem>
int Multime<TElem>::remove(const TElem& e) {
    if (!ifExist(e))
        return 0;

    int poz = search(e);
    for (int i = poz; i < noElems - 1; ++i)
        elems[i] = elems[i + 1];
    noElems--;
    return 1;
}

template<typename TElem>
int Multime<TElem>::size() const {
    return noElems;
}

template<typename TElem>
TElem Multime<TElem>::getElem(int poz) const {
    if (poz < 0 || poz >= noElems) {
        return TElem();
    }
    return elems[poz];
}
