#include <iostream>
#include <string>
#include <cmath> 

using namespace std;

// Subsystem Part 1: Inventory System
class InventorySystem {
public:
    bool checkStock(const string& productId, int quantity) {
        cout << "Checking stock for " << productId << "..." << endl;
        // Simulate a real stock check
        if (quantity < 100) {
            cout << "Stock is available." << endl;
            return true;
        }
        cout << "Stock is NOT available." << endl;
        return false;
    }
};

// Subsystem Part 2: Payment Gateway
class PaymentGateway {
public:
    bool processPayment(const string& creditCard, double amount) {
        cout << "Processing payment of $" << amount << "..." << endl;
        if (creditCard == "1") { //for example, "1" is a valid card
            cout << "Payment successful !" << endl;
            return true;
        }
        cout << "Payment failed (invalid card)." << endl;
        return false;
    }
};

// Subsystem Part 3: Shipping Service
class ShippingService {
public:
    void createShipment(const string& productId, const string& address) {
        cout << "Creating shipment for " << productId << " to " << address << endl;
        cout << "Shipment created !." << endl;
    }
};


// --- The Facade ---
class OrderFacade {
private:
    InventorySystem inventory;
    PaymentGateway payment;
    ShippingService shipping;

public:
    OrderFacade() : inventory(), payment(), shipping() {}


    /**
     * This is the simplified, unified interface.
     * The client just calls this one method.
     */
    bool placeOrder(const string& productId, int quantity, 
                    const string& creditCard, double price, 
                    const string& address) 
    {
        cout << "--- Initiating order process ---" << endl;
        bool success = false;

        // 1. Check stock
        if (inventory.checkStock(productId, quantity)) {
            
            // 2. Process payment
            if (payment.processPayment(creditCard, price * quantity)) {

                // 3. Create shipment
                shipping.createShipment(productId, address);
                success = true;
                cout << "--- Order process completed successfully! ---" << endl;
            
            } else {
                cout << "--- Order process failed (Payment Error) ---" << endl;
            }
        
        } else {
            cout << "--- Order process failed (Out of Stock) ---" << endl;
        }

        return success;
    }
};


// --- The Client ---
int main() {
    
    // The client only needs to know about the facade
    OrderFacade orderFacade;

    // --- Use Case 1: Successful Order ---
    cout << "Attempting a valid order..." << endl;
    orderFacade.placeOrder(
        "shampoo", 
        2, 
        "1", // Valid card
        50.00, 
        "21, masr elgdeda, Egypt"
    );

    // --- Use Case 2: Failed Order (Payment) ---
    cout << "\nAttempting an order with a invalid card..." << endl;
    orderFacade.placeOrder(
        "sokar", 
        1, 
        "2", // Invalid card
        150.00, 
        "456 Oak Ave, Othertown, USA"
    );

    
    return 0;
}