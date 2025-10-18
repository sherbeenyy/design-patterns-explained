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


// --- The Client ---
int main() {
    
    // The client must now create and manage all subsystems directly
    InventorySystem inventory;
    PaymentGateway payment;
    ShippingService shipping;

    // --- Use Case 1: Successful Order ---
    cout << "Attempting a valid order..." << endl;
    
    // --- All this logic was previously hidden inside the Facade ---
    {
        // Define order details
        string productId = "shampoo";
        int quantity = 2;
        string creditCard = "1"; // Valid card
        double price = 50.00;
        string address = "21, masr elgdeda, Egypt";

        cout << "--- Initiating order process ---" << endl;
        bool success = false;

        // 1. Client must call InventorySystem
        if (inventory.checkStock(productId, quantity)) {
            
            // 2. Client must call PaymentGateway
            if (payment.processPayment(creditCard, price * quantity)) {

                // 3. Client must call ShippingService
                shipping.createShipment(productId, address);
                success = true;
                cout << "--- Order process completed successfully! ---" << endl;
            
            } else {
                cout << "--- Order process failed (Payment Error) ---" << endl;
            }
        
        } else {
            cout << "--- Order process failed (Out of Stock) ---" << endl;
        }
    }
    // --- End of logic for Use Case 1 ---


    // --- Use Case 2: Failed Order (Payment) ---
    cout << "\nAttempting an order with a invalid card..." << endl;

    // --- The client must REPEAT all the complex logic ---
    {
        // Define order details
        string productId = "sokar";
        int quantity = 1;
        string creditCard = "2"; // Invalid card
        double price = 150.00;
        string address = "456 Oak Ave, Othertown, USA";

        cout << "--- Initiating order process ---" << endl;
        bool success = false;

        // 1. Client must call InventorySystem again
        if (inventory.checkStock(productId, quantity)) {
            
            // 2. Client must call PaymentGateway again
            if (payment.processPayment(creditCard, price * quantity)) {

                // 3. Client must call ShippingService again
                shipping.createShipment(productId, address);
                success = true;
                cout << "--- Order process completed successfully! ---" << endl;
            
            } else {
                cout << "--- Order process failed (Payment Error) ---" << endl;
            }
        
        } else {
            cout << "--- Order process failed (Out of Stock) ---" << endl;
        }
    }
   

    
    return 0;
}