#include <iostream>
#include <string>
#include <unistd.h> 

using namespace std;

class Investor
{

private:
    float _currentPrice;
public:
    void update(float newPrice){
    _currentPrice = newPrice;
        cout << "Investor notified: New price is $" << _currentPrice << endl;
    }
};

class StockMarket {
private:
    float price;

    // Hardcoded investors
    Investor investorA;
    Investor investorB;
    Investor investorC;


public:
    void setPrice(float newPrice) {
        price = newPrice;
        notifyInvestors();
    }
    void notifyInvestors() {
        //modifing them manually
        //what if i have a new investor?
        // i will need to add them to the notification list
        investorA.update(price);
        investorB.update(price);
        investorC.update(price);
    }

};

int main() {
    StockMarket market;
    market.setPrice(100.0f);
    sleep(1);
    market.setPrice(150.0f);
    sleep(1);
    market.setPrice(75.0f);
    sleep(1);
    market.setPrice(12.0f);
    sleep(1);
}
