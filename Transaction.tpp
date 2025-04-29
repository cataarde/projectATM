#include <iostream>
#include "Transaction.h"

template <typename TElem>
Transaction<TElem>::Transaction()
{
    this->id = 0;
    this->sum = 0;
    this->banknotes = Collection<TElem>();
}

template <typename TElem>
Transaction<TElem>::Transaction(int newId, int usedSum, Collection<TElem> usedBanknotes)
{
    this->id = newId;
    this->sum = usedSum;
    this->banknotes = usedBanknotes;
}

template <typename TElem>
int Transaction<TElem>::getId() const
{
    return id;
}

template <typename TElem>
int Transaction<TElem>::getSum() const
{
    return sum;
}

template <typename TElem>
const Collection<TElem>& Transaction<TElem>:: getBanknotes() const
{
    return banknotes;
}

template <typename TElem>
void Transaction<TElem>::print()const
{
    std::cout<<"Id: "<<getId()<<" "<<"Sum: "<<getSum()<<"\n";
    std::cout<<"Banknotes used/n";
    banknotes.print_all();
}

template <typename TElem>
std::time_t Transaction<TElem>::getTimestamp() const
{
    return timestamp;
}

