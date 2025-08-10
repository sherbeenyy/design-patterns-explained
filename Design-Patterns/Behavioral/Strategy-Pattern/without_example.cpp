#include <iostream>
#include <string>

using namespace std;

// base payment processor
class PaymentProcessor {
public:
    virtual void processPayment(double amount) {
        cout << "Processing generic payment of $" << amount << endl;
    }

    virtual ~PaymentProcessor() = default;
};

// credit card processor
class CreditCardProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
    }
};

// PayPal processor
class PayPalProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

// cryptocurrency processor
class CryptoProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        cout << "Processing cryptocurrency payment of $" << amount << endl;
    }
};

int main() {

    //to change the payment mehtod i need to create a whole new object 
    //any state saved in the precious object will be delted automatically as i destroy the whole object and create a new one
    PaymentProcessor* paymentProcessor = nullptr;

    int choice;
    double amount;

    cout << "Enter the amount: ";
    cin >> amount;

    while (true) {
        cout << "Choose your payment method: " << endl;
        cout << "1. credit Card" << endl;
        cout << "2. payPal" << endl;
        cout << "3. crypto" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            paymentProcessor = new CreditCardProcessor();
            break;
        case 2:
            paymentProcessor = new PayPalProcessor();
            break;
        case 3:
            paymentProcessor = new CryptoProcessor();
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            continue; // go back to start
        }

        cout << "Are you sure of that payment method? (reply with Y or y for yes)" << endl;
        char confirmation;
        cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            paymentProcessor->processPayment(amount);
            break; // exit loop after confirmation
        } else {
            cout << "payment method not confirmed" << endl;
        }
    }

    delete paymentProcessor; // clean up the pointer 
    return 0;
}
