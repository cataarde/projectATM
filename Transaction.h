#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <ctime>
#include "Collection.h"

template <typename TElem>
class Transaction {
private:
    int id;
    int sum;
    Collection<TElem> banknotes;
    std::time_t timestamp;
public:
    Transaction();
    Transaction(int newId, int usedSum, Collection<TElem> usedBanknotes);
    int getId() const;
    int getSum() const;
    const Collection<TElem>& getBanknotes() const;
    void print() const;
    std::time_t getTimestamp() const;
};


#include "Transaction.tpp"

#endif //TRANSACTION_H
