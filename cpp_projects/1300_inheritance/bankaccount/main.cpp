#include <iostream>
using namespace std;
#include <cstring>
#include "bankaccountlib/bankacct.h"
#include "customlib/overdraft.h"

// This program demonstrates the use of inheritance in C++.
// It creates a BankAccount object, performs some operations on it,
int main()
{
    BankAccount porky("Porcelot Pigg", 381299, 4000.); // create a BankAccount object with a name, account number, and initial balance
    porky.view_account();
    cout << "\nDeposited 5000 CZK: \n";
    porky.deposit(5000.); // deposit 5000 CZK into the account
    cout << "New balance: " << porky.get_balance() << " CZK\n";
    cout << "Withdrawn 8000 CZK: \n";
    porky.withdraw(8000.); // withdraw 8000 CZK from the account
    cout << "New balance: " << porky.get_balance() << " CZK\n";
    cout << "Withdrawn 1200 CZK: \n";
    porky.withdraw(1200.);   // withdraw 1200 CZK from the account
    cout << "New balance: " << porky.get_balance() << " CZK\n";
    cout << "\nConversion to new account type.\n\n";
    Overdraft porky2(porky);    // create an Overdraft object from the BankAccount object
    porky2.view_account();      // view the account details of the Overdraft object
    cout << "\nDeposited 5000 CZK: \n";
    porky2.deposit(5000);   // deposit 5000 CZK into the Overdraft account
    cout << "New balance: " << porky2.get_balance() << " CZK\n";
    cout << "Withdrawn 8000 CZK: \n";
    porky2.withdraw(8000);   // withdraw 8000 CZK from the Overdraft account
    cout << "New balance: " << porky2.get_balance() << " CZK\n";
    cout << "Withdrawn 1200 CZK: \n\n";
    porky2.withdraw(1200);   // withdraw 1200 CZK from the Overdraft account
    porky2.view_account();
    cout << "\nWithdrawn 5250 CZK: \n\n";
    porky2.withdraw(5250);   // withdraw 5250 CZK from the Overdraft account
    porky2.view_account();
    cout << "\nWithdrawn 5 CZK: \n\n";
    porky2.withdraw(5);  // withdraw 5 CZK from the Overdraft account
    porky2.view_account();      
    cout << "\nConversion to a pointer to the base class: BankAccount *pb = &porky2;\n\n";
    BankAccount * pb = &porky2; // create a pointer to the Overdraft object as a BankAccount pointer
    // This is possible because Overdraft is derived from BankAccount
    // and the pointer to the base class can point to an object of the derived class
    // This is known as polymorphism in C++
    pb->view_account();
    cout << "\nConversion to a reference to the base class. BankAccount &rb = porky2;\n\n";
    BankAccount &rb = porky2;
    rb.view_account();
    cout << "\nMixed assignment: BankAccount = Overdraft\n";
    BankAccount ba_bip;
    Overdraft od_bip("Bipp Fardbag", "BFRD_01", 212143, 200);
    cout << "\nObject of class Overdraft:\n\n";
    od_bip.view_account();
    // 1. ba_bip.operator=(od_bip)
    // 2. Assignment operator corresponding to BankAccount & BankAccount::operator=(const Overdraft &); does not exist!
    // and the implicit operator in class BankAccount is not sufficient
    // 3. But there is an implicit conversion from derived class to base class
    // 4. As a result, only the base class parameters are assigned to ba_bip 
    ba_bip = od_bip;
    cout << "\nAfter assignment to BankAccount:\n\n";
    ba_bip.view_account();
    cout << "\nMixed assignment: Overdraft = BankAccount\n";
    BankAccount ba_darf("Darfa Flemwit", 121234, 100);
    cout << "\nObject of class BankAccount:\n\n";
    ba_darf.view_account();
    Overdraft od_darf;
    // 1. od_darf.operator=(ba_darf)
    // 2. Assignment operator corresponding to Overdraft & Overdraft::operator=(const BankAccount &); does not exist!
    // 3. but there is an implicit operator in class Overdraft 
    // 4. Overdraft::Overdraft(const BankAccount &ba, double ml = 500, double r = 0.1) 
    // casts the BankAccount object to an Overdraft object
    // 5. As a result, od_darf is assigned a temporary Overdraft object with default values 
    od_darf = ba_darf;
    cout << "\nAfter assignment to Overdraft:\n\n";
    od_darf.view_account();

    return 0;
}