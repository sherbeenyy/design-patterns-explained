#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Invoice {
public:
    Invoice(const string& customer, double amount)
        : customerName(customer), amount(amount) {}

    void saveToFile() {
        ofstream file("invoice.txt");
        file << "Customer: " << customerName << "\n";
        file << "Amount: $" << amount << "\n";
        file.close();
    }

    void printInvoice() {
        cout << "Customer: " << customerName << "\n";
        cout << "Amount: $" << amount << "\n";
    }

private:
    string customerName;
    double amount;
};

int main() {
    Invoice invoice("Ahmed", 250.0);
    invoice.printInvoice();
    invoice.saveToFile();
}
