#ifndef SET_H
#define SET_H

template<typename TElem>
using Comparator = bool (*)(const TElem&, const TElem&);  //pointer la functie

template<typename TElem>
class Multime {
private:
    TElem* elems;
    int capacitate;
    int noElems;

    Comparator<TElem> cmp;  // folosește aliasul de tip

    void resize();
    int search(const TElem& e) const;

public:
    Multime(Comparator<TElem> cmpFunc);
    ~Multime();

    void add(const TElem& e);
    int remove(const TElem& e);
    bool ifExist(const TElem& e) const;
    int size() const;
    TElem getElem(int poz) const;
};


#include "Set.tpp"
#endif //SET_H
