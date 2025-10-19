#include <iostream>
#include <memory>
#include <string>
using namespace std;

class IPaymentGateway {
public:
    virtual void pay(float amount) = 0;
    virtual ~IPaymentGateway() = default;
};

class CreditCardGateway : public IPaymentGateway {
public:
    void pay(float amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
    }
};

class PayPalGateway : public IPaymentGateway {
public:
    void pay(float amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

class CryptoGateway : public IPaymentGateway {
public:
    void pay(float amount) override {
        cout << "Processing Crypto payment of $" << amount << endl;
    }
};

class ApplePayGateway : public IPaymentGateway {
public:
    void pay(float amount) override {
        cout << "Processing Apple Pay payment of $" << amount << endl;
    }
};

class CheckoutService {
private:
    shared_ptr<IPaymentGateway> gateway;

public:
    void setGateway(shared_ptr<IPaymentGateway> newGateway) {
        gateway = newGateway;
    }

    void processPayment(float amount) {
        if (!gateway) {
            cout << "Error: No payment gateway selected!" << endl;
            return;
        }
        gateway->pay(amount);
    }
};
int main() {
    CheckoutService checkout;

    checkout.setGateway(make_shared<CreditCardGateway>());
    checkout.processPayment(100.0f);

    checkout.setGateway(make_shared<PayPalGateway>());
    checkout.processPayment(200.0f);

    checkout.setGateway(make_shared<CryptoGateway>());
    checkout.processPayment(300.0f);

    checkout.setGateway(make_shared<ApplePayGateway>());
    checkout.processPayment(400.0f);

    return 0;
}