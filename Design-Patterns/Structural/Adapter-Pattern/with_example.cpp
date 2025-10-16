#include <iostream>
#include <string>
#include <iomanip> 

// Define the Incompatible Third-Party Services (Adaptees)
// These are the classes with interfaces that our system doesn't control.
using namespace std;
class StripeAPI {
public:
    /**
     * @brief Processes a payment in cents.
     */
    void charge(const string& cardDetails, int amountCents) {
        cout << "Stripe: Charging card '" << cardDetails << "' for "
             << fixed << setprecision(2) << static_cast<double>(amountCents) / 100.0
             << " USD." << endl;
    }

    /**
     * @brief Issues a refund in cents.
     */
    void issueRefund(const string& transactionId, int amountCents) {
        cout << "Stripe: Refunding "
             << fixed << setprecision(2) << static_cast<double>(amountCents) / 100.0
             << " USD for transaction '" << transactionId << "'." << endl;
    }
};

class PayPalAPI {
public:
    /**
     * @brief Sends a payment in dollars.
     */
    void sendPayment(const string& email, double amountDollars) {
        cout << "PayPal: Sending payment of "
             << fixed << setprecision(2) << amountDollars
             << " USD to '" << email << "'." << endl;
    }

    /**
     * @brief Reverses a payment in dollars.
     */
    void reversePayment(const string& paymentId, double amountDollars) {
        cout << "PayPal: Reversing payment of "
             << fixed << setprecision(2) << amountDollars
             << " USD for payment ID '" << paymentId << "'." << endl;
    }
};

// Define the Target Interface
// This is the single, consistent interface our application will use.
// In C++, this is an abstract base class with pure virtual functions.

class IPaymentGateway {
public:
    virtual ~IPaymentGateway() = default; // Virtual destructor for base class
    virtual void pay(double amount) = 0;
    virtual void refund(double amount) = 0;
};

// Create the Adapters 
// These classes implement our Target interface and translate its calls
// into the specific calls required by the Adaptee classes.

class StripeAdapter : public IPaymentGateway {
private:
    StripeAPI* stripeApi;
    string cardDetails;
    string transactionId;

public:
    StripeAdapter(StripeAPI* api, string card, string txnId)
        : stripeApi(api), cardDetails(card), transactionId(txnId) {}

    /**
     * @brief Translates the standard 'pay' call into Stripe's 'charge' call,
     * converting the amount from dollars to cents.
     */
    void pay(double amount) override {
        int amountInCents = static_cast<int>(amount * 100);
        cout << "StripeAdapter: Converting amount to cents and calling Stripe API." << endl;
        stripeApi->charge(cardDetails, amountInCents);
    }

    /**
     * @brief Translates the standard 'refund' call into Stripe's 'issueRefund' call,
     * converting the amount from dollars to cents.
     */
    void refund(double amount) override {
        int amountInCents = static_cast<int>(amount * 100);
        cout << "StripeAdapter: Converting amount to cents and calling Stripe API for refund." << endl;
        stripeApi->issueRefund(transactionId, amountInCents);
    }
};

class PayPalAdapter : public IPaymentGateway {
private:
    PayPalAPI* payPalApi;
    string email;
    string paymentId;

public:
    PayPalAdapter(PayPalAPI* api, string userEmail, string payId)
        : payPalApi(api), email(userEmail), paymentId(payId) {}

    /**
     * @brief Translates the standard 'pay' call into PayPal's 'sendPayment' call.
     * No amount conversion is needed here.
     */
    void pay(double amount) override {
        cout << "PayPalAdapter: Calling PayPal API directly." << endl;
        payPalApi->sendPayment(email, amount);
    }

    /**
     * @brief Translates the standard 'refund' call into PayPal's 'reversePayment' call.
     */
    void refund(double amount) override {
        cout << "PayPalAdapter: Calling PayPal API for refund." << endl;
        payPalApi->reversePayment(paymentId, amount);
    }
};


// Client Code
// The client code interacts with any object that follows the IPaymentGateway interface.
// It doesn't need to know the specifics of Stripe or PayPal.

void processOrder(IPaymentGateway* gateway, double totalAmount) {
    cout << "\n--- Processing an order of $" << fixed << setprecision(2) << totalAmount << " ---" << endl;
    gateway->pay(totalAmount);
    cout << "--- Order processed successfully! ---" << endl;
}

int main() {
    // Create instances of the external services
    StripeAPI stripeService;
    PayPalAPI paypalService;

    // Create adapter instances, wrapping the specific APIs.
    // For a real app, this data would come from the user's order.
    StripeAdapter stripeGateway(&stripeService, "1234-5678-9012-3456", "txn_stripe123");
    PayPalAdapter paypalGateway(&paypalService, "customer@example.com", "pay_paypal456");

    // Use the client code with different adapters without changing it.
    // We pass the addresses of the adapter objects.
    processOrder(&stripeGateway, 150.75);
    processOrder(&paypalGateway, 89.99);

    // We can also issue a refund using the same adapters
    cout << "\n--- Issuing a refund ---" << endl;
    stripeGateway.refund(25.00);

    return 0;
}
