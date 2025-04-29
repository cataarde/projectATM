#include "ATM.h"
#include <iostream>
#include "Iterator.h"
#include "Collection.h"

// template<typename TElem>
// ATM<TElem>::ATM() {
//     lastId = 0;
//     transactions = nullptr;
// }

template <typename TElem>
TElem ATM<TElem>::getAllMoney() {
    TElem total = 0;
    for (int i = 0; i < banknotes.size(); i++) {
        total += banknotes.getAt(i) * banknotes.nrOccurrences(banknotes.getAt(i));
    }
    return total;
}

template<typename TElem>
void merge(pereche<TElem>* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    pereche<TElem>* L = new pereche[n1];
    pereche<TElem>* R = new pereche[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].elem >= R[j].elem) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

template<typename TElem>
void mergeSort(pereche<TElem>* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template<typename TElem>
void ATM<TElem>::sortBanknotes() {
    if (banknotes.size() > 1) {
        int size = banknotes.size();
        pereche<TElem>* elems = new pereche[size];
        for (int i = 0; i < size; i++) {
            elems[i] = {banknotes.getAt(i), banknotes.nrOccurrences(banknotes.getAt(i))};
        }

        mergeSort(elems, 0, size - 1);

        banknotes = Collection<TElem>();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < elems[i].frecv; j++) {
                banknotes.add(elems[i].elem);
            }
        }

        delete[] elems;
    }
}

// template <typename TElem>
// void ATM<TElem>::resize() {
//     capacity *= 2;
//     Transaction<TElem>* newTransactions = new Transaction[capacity];
//     for (int i = 0; i < lastId; i++) {
//         newTransactions[i] = transactions[i];
//     }
//     delete[] transactions;
//     transactions = newTransactions;
// }

template <typename TElem>
bool ATM<TElem>::addBanknotes(TElem value, int freq) {
    if (freq <= 0) {
        return false;
    }
    for (int i = 0; i < freq; i++) {
        banknotes.add(value);
    }


    return true;
}

template <typename TElem>
bool ATM<TElem>::withdrawal(int sum) {
    if (sum <= 0) {
        std::cout << "Invalid sum!" << std::endl;
        return false;
    }
    if (sum > getAllMoney()) {
        std::cout << "Insufficient funds!" << std::endl;
        return false;
    }

    sortBanknotes();

    Collection<TElem> usedBanknotes;
    int remaining = sum;


    for (int i = 0; i < banknotes.size() && remaining > 0; i++) {
        TElem banknote = banknotes.getAt(i);


        while (remaining >= banknote && banknotes.nrOccurrences(banknote) > 0) {
            usedBanknotes.add(banknote);
            banknotes.remove(banknote);
            remaining -= banknote;
        }
    }


    if (remaining == 0) {

        addTransaction(lastId + 1, sum, usedBanknotes);
        std::cout << "Withdrawal successful: " << sum << std::endl;
        std::cout << "Banknotes used: ";
        usedBanknotes.print_all();
        return true;
    } else {

        for (int i = 0; i < usedBanknotes.size(); i++) {
            banknotes.add(usedBanknotes.getAt(i));
        }
        std::cout << "Withdrawal failed: Exact sum cannot be withdrawn." << std::endl;
        return false;
    }
}

template <typename TElem>
void ATM<TElem>::printBanknotes() {
    std::cout << "Banknotes in the ATM: " << std::endl;
    banknotes.print_all();
}

template <typename TElem>
void ATM<TElem>::printTransactions() {
    std::cout << "Transactions: " << std::endl;
    for (int i = 0; i < lastId; i++) {
        transactions[i].print();
    }
}

template <typename TElem>
bool ATM<TElem>::addTransaction(int newId, int sum, Collection<TElem> usedBanknotes) {
    if (lastId >= capacity) {   // Resize if capacity is exceeded
        transactions.resize();
    }
    transactions[lastId] = Transaction(newId, sum, usedBanknotes);
    lastId++;
    return true;
}


