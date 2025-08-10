#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Strategy interface
class IpaymentStrategy {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~IpaymentStrategy() = default;
};

// Concrete Strategies
class CreditCardProcessor : public IpaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing credit card algorithm of $" << amount << endl;
    }
};

class PayPalProcessor : public IpaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal algorithm of $" << amount << endl;
    }
};

class CryptoProcessor : public IpaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing cryptocurrency algorithm of $" << amount << endl;
    }
};

// Context
class PaymentProcessor {
private:
    shared_ptr<IpaymentStrategy> _paymentMethod;
public:
    PaymentProcessor(shared_ptr<IpaymentStrategy> method)
        : _paymentMethod(method) {}

    void setPaymentMethod(shared_ptr<IpaymentStrategy> method) {
        _paymentMethod = method;
    }

    void process(double amount) {
        if (_paymentMethod) {
            _paymentMethod->processPayment(amount);
        } else {
            cout << "No payment method selected!" << endl;
        }
    }
};

int main() {

    //look the idea here that i can change the alogrithm of the proccess the payment with mid process
    // i can change the payment method at any time actually
    // thats the strategy pattern in action ;)
    PaymentProcessor paymentProcessor(nullptr);
    int choice;
    double amount;

    cout << "Enter the amount: ";
    cin >> amount;

    while (true) {
        cout << "Choose your payment method: " << endl;
        cout << "1. Credit Card" << endl;
        cout << "2. PayPal" << endl;
        cout << "3. Crypto" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            paymentProcessor.setPaymentMethod(make_shared<CreditCardProcessor>());
            break;
        case 2:
            paymentProcessor.setPaymentMethod(make_shared<PayPalProcessor>());
            break;
        case 3:
            paymentProcessor.setPaymentMethod(make_shared<CryptoProcessor>());
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            continue; // go back to start
        }

        cout << "Are you sure of that payment method? (reply with Y or y for yes)" << endl;
        char confirmation;
        cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            paymentProcessor.process(amount);
            break; // exit loop after confirmation
        } else {
            cout << "payment method not confirmed" << endl;
        }
    }

    return 0;
}
