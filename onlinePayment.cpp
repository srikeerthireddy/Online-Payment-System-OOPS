#include <iostream>
#include <string>
using namespace std;

// Abstract base class
class PaymentMethod {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentMethod() {}
};

// Credit Card Payment
class CreditCardPayment : public PaymentMethod {
private:
    string cardNumber;
    string cardHolder;

public:
    CreditCardPayment(string number, string holder) : cardNumber(number), cardHolder(holder) {}

    void pay(double amount) override {
        cout << "\n[Credit Card] Rs." << amount << " paid by " << cardHolder << " using card " << cardNumber << "." << endl;
    }
};

// PayPal Payment
class PayPalPayment : public PaymentMethod {
private:
    string email;

public:
    PayPalPayment(string emailId) : email(emailId) {}

    void pay(double amount) override {
        cout << "\n[PayPal] Rs." << amount << " paid from account: " << email << "." << endl;
    }
};

// Bank Transfer Payment
class BankTransferPayment : public PaymentMethod {
private:
    string accountNumber;
    string bankName;

public:
    BankTransferPayment(string accNo, string bank) : accountNumber(accNo), bankName(bank) {}

    void pay(double amount) override {
        cout << "\n[Bank Transfer] Rs." << amount << " transferred from account " << accountNumber << " at " << bankName << "." << endl;
    }
};

// Payment processor
class PaymentProcessor {
public:
    void makePayment(PaymentMethod* method, double amount) {
        method->pay(amount);
    }
};

int main() {
    PaymentProcessor processor;
    int choice;
    double amount;

    while (true) {
        cout << "\n====== Online Payment System ======" << endl;
        cout << "1. Pay using Credit Card" << endl;
        cout << "2. Pay using PayPal" << endl;
        cout << "3. Pay using Bank Transfer" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 4) {
            cout << "Thank you for using the Online Payment System!" << endl;
            break;
        }

        cout << "Enter amount to pay: Rs.";
        cin >> amount;

        PaymentMethod* method = nullptr;

        if (choice == 1) {
            string number, holder;
            cout << "Enter Card Number: ";
            cin >> number;
            cout << "Enter Card Holder Name: ";
            cin.ignore(); // to clear newline
            getline(cin, holder);
            method = new CreditCardPayment(number, holder);
        } 
        else if (choice == 2) {
            string email;
            cout << "Enter PayPal Email: ";
            cin >> email;
            method = new PayPalPayment(email);
        } 
        else if (choice == 3) {
            string accNo, bank;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Bank Name: ";
            cin.ignore(); // to clear newline
            getline(cin, bank);
            method = new BankTransferPayment(accNo, bank);
        } 
        else {
            cout << "Invalid choice! Please try again." << endl;
            continue;
        }

        // Process the payment
        processor.makePayment(method, amount);

        // Free memory
        delete method;
    }

    return 0;
}
