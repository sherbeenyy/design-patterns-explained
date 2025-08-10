#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// class only stores invoice data
class Invoice {
public:
    Invoice(const string& customer, double amount)
        : customerName(customer), amount(amount) {}

    string getCustomerName() const { return customerName; }
    double getAmount() const { return amount; }

private:
    string customerName;
    double amount;
};

// handles saving invoice to a file
class InvoiceFileSaver {
public:
    void saveToFile(const Invoice& invoice) {
        ofstream file("invoice.txt");
        file << "Customer: " << invoice.getCustomerName() << "\n";
        file << "Amount: $" << invoice.getAmount() << "\n";
        file.close();
    }
};

// handles printing invoice to console
class InvoicePrinter {
public:
    void print(const Invoice& invoice) {
        cout << "Customer: " << invoice.getCustomerName() << "\n";
        cout << "Amount: $" << invoice.getAmount() << "\n";
    }
};

int main() {
    Invoice invoice("Ahmed", 250.0);
    InvoicePrinter printer;
    InvoiceFileSaver saver;

    printer.print(invoice);
    saver.saveToFile(invoice);
}
