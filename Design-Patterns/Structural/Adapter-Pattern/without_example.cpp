#include <iostream>
#include <string>
#include <iomanip>

// These are the same third-party services from the good example.
// Their interfaces are incompatible with each other.
class StripeAPI {
public:
    void charge(const std::string& cardDetails, int amountCents) {
        std::cout << "Stripe: Charging card '" << cardDetails << "' for "
             << std::fixed << std::setprecision(2) << static_cast<double>(amountCents) / 100.0
             << " USD." << std::endl;
    }
};

class PayPalAPI {
public:
    void sendPayment(const std::string& email, double amountDollars) {
        std::cout << "PayPal: Sending payment of "
             << std::fixed << std::setprecision(2) << amountDollars
             << " USD to '" << email << "'." << std::endl;
    }
};

// --- Problem Area: The Client Code ---
// This function is now tightly coupled to every single payment service.
// It must contain logic to handle each one individually.

void processOrder(const std::string& gatewayType, double totalAmount) {
    std::cout << "\n--- Processing an order of $" << std::fixed << std::setprecision(2) << totalAmount << " ---" << std::endl;

    if (gatewayType == "stripe") {
        // Specific logic for Stripe
        StripeAPI stripeService;
        std::string cardDetails = "1234-5678-9012-3456"; // Hardcoded for example
        int amountInCents = static_cast<int>(totalAmount * 100); // In-place data conversion
        
        std::cout << "Client: Handling Stripe payment directly. Converting to cents." << std::endl;
        stripeService.charge(cardDetails, amountInCents);

    } else if (gatewayType == "paypal") {
        // Specific logic for PayPal
        PayPalAPI paypalService;
        std::string email = "customer@example.com"; // Hardcoded for example

        std::cout << "Client: Handling PayPal payment directly." << std::endl;
        paypalService.sendPayment(email, totalAmount);

    } else {
        std::cout << "Error: Unknown payment gateway type '" << gatewayType << "'." << std::endl;
    }
     std::cout << "--- Order processed! ---" << std::endl;
}

int main() {
    // The client (main function) now has to decide which specific string to pass.
    // This makes the client's logic more complex.
    
    processOrder("stripe", 150.75);
    processOrder("paypal", 89.99);

    // What if we want to add a new payment provider called "Square"?
    // We would have to go back and add another 'else if' block to the processOrder function.
    // This is not scalable and violates the Open/Closed Principle.
    std::cout << "\n--- Trying to process with a new, unsupported gateway ---" << std::endl;
    processOrder("square", 49.95);

    return 0;
}
