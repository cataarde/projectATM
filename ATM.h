#ifndef ATM_H
#define ATM_H

#include "Transaction.h"
#include "Set.h"
template <typename TElem>
using Comparator = bool (*)(const Transaction<TElem>&, const Transaction<TElem>&);

template<typename TElem>
class ATM{
private:
    int lastId;
    int capacity;
    Comparator<TElem> cmp;
    Multime<TElem> transactions;
    Collection<TElem> banknotes;
public:
    ATM(Comparator<TElem> comparator)
        : cmp(comparator), transactions(comparator){}
    TElem getAllMoney();
    void sortBanknotes();
    bool addBanknotes(TElem value, int freq);
    bool withdrawal(int sum);
    void printBanknotes();
    void printTransactions();
    bool addTransaction(int lastId, int sum, Collection<TElem> usedBanknotes);
    void sortDate();
    void sortSum();
    void sortNrBanknotes();
};

#include "ATM.tpp"

#endif //ATM_H
