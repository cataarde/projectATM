#include "ATM.h"
#include <iostream>
#include "Iterator.h"
#include "Collection.h"

template<typename TElem>
ATM<TElem>::ATM() {
    lastId = 0;
    capacity = 5;
    transactions = new Transaction[capacity];
    for (int i = 0; i < 10; i++) {
        banknotes.add(50);
        banknotes.add(10);
        banknotes.add(5);
        banknotes.add(100);
        banknotes.add(1);
    }
}



void merge(pereche* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    pereche* L = new pereche[n1];
    pereche* R = new pereche[n2];

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

void mergeSort(pereche* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void ATM::sortBanknotes() {
    if (banknotes.size() > 1) {
        int size = banknotes.size();
        pereche* elems = new pereche[size];
        for (int i = 0; i < size; i++) {
            elems[i] = {banknotes.getAt(i), banknotes.nrOccurrences(banknotes.getAt(i))};
        }

        mergeSort(elems, 0, size - 1);

        banknotes = Collection();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < elems[i].frecv; j++) {
                banknotes.add(elems[i].elem);
            }
        }

        delete[] elems;
    }
}


void ATM::resize() {
    capacity *= 2;
    Transaction* newTransactions = new Transaction[capacity];
    for (int i = 0; i < lastId; i++) {
        newTransactions[i] = transactions[i];
    }
    delete[] transactions;
    transactions = newTransactions;
}


bool ATM::addBanknotes(TElem value, int freq) {
    if (freq <= 0) {
        return false;
    }
    for (int i = 0; i < freq; i++) {
        banknotes.add(value);
    }


    return true;
}


bool ATM::withdrawal(int sum) {
    if (sum <= 0) {
        std::cout << "Invalid sum!" << std::endl;
        return false;
    }

    sortBanknotes();

    Collection usedBanknotes;
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


void ATM::printBanknotes() {
    std::cout << "Banknotes in the ATM: " << std::endl;
    banknotes.print_all();
}

void ATM::printTransactions() {
    std::cout << "Transactions: " << std::endl;
    for (int i = 0; i < lastId; i++) {
        transactions[i].print();
    }
}

bool ATM::addTransaction(int newId, int sum, Collection usedBanknotes) {
    if (lastId >= capacity) {   // Resize if capacity is exceeded
        resize();
    }
    transactions[lastId] = Transaction(newId, sum, usedBanknotes);
    lastId++;
    return true;
}

