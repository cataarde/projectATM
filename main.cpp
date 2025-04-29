#include <iostream>
#include "ATM.h"

bool cmpDate(const Transaction<int>& t1, const Transaction<int>& t2) {
    return t1.getId() < t2.getId();
}
// template <typename TElem>
// bool cmpAmount(const Transaction<TElem>& t1, const Transaction<TElem>& t2) {
//     return t1.getSum() < t2.getSum();
// }
//
//
// bool cmpBanknotesUsed(const Transaction<int>& t1, const Transaction<int>& t2) {
//     return  t1.getBanknotes().size() < t2.getBanknotes().size();
// }
void displayMenu() {
    std::cout << "\n--- ATM System Menu ---\n";
    std::cout << "1. Add Banknotes\n";
    std::cout << "2. Withdraw Money\n";
    std::cout << "3. Show Available Banknotes\n";
    std::cout << "4. Show Transactions\n";
    std::cout << "5. Sort Transactions\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}
template<typename TElem>
int main() {
    ATM<int> atm(cmpDate);
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                TElem value;
                int freq;
                std::cout << "Enter the value of the banknote: ";
                std::cin >> value;
                std::cout << "Enter the number of banknotes: ";
                std::cin >> freq;

                if (atm.addBanknotes(value, freq)) {
                    std::cout << "Banknotes added successfully.\n";
                } else {
                    std::cout << "Failed to add banknotes. Please try again.\n";
                }
                break;
            }

            case 2: {
                int sum;
                std::cout << "Enter the amount to withdraw: ";
                std::cin >> sum;

                if (!atm.withdrawal(sum)) {
                    std::cout << "Withdrawal failed. Ensure the ATM has the required banknotes.\n";
                }
                break;
            }

            case 3: {
                std::cout << "Available banknotes: \n";
                atm.printBanknotes();
                break;
            }

            case 4: {
                std::cout << "Transaction history: \n";
                atm.printTransactions();
                break;
            }

            case 5: {
                std::cout << "Sort transactions: \n1. By Date\n2. By Amount\n3. By Number of Banknotes Used\n";
                int sortChoice;
                std::cin >> sortChoice;
                switch (sortChoice) {
                    case 1:
                        atm.sortDate();
                        std::cout << "Transactions sorted by date.\n";
                        break;
                    case 2:
                        atm.sortSum();
                        std::cout << "Transactions sorted by amount.\n";
                        break;
                    case 3:
                        atm.sortNrBanknotes();
                        std::cout << "Transactions sorted by number of banknotes used.\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                }
            }

            case 0: {
                std::cout << "Exiting the ATM system. Goodbye!\n";
                break;
            }

            default: {
                std::cout << "Invalid choice. Please select a valid option.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
