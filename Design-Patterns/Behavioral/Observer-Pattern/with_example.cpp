#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <unistd.h> 

using namespace std;


class IObserver{ 
public:
    virtual void update(float newPrice) = 0;
    virtual ~IObserver() = default;
};

class IObservable{ 
public:
    virtual void add(shared_ptr<IObserver> observer) = 0;
    virtual void remove(shared_ptr<IObserver> observer) = 0;
    virtual void notify() = 0;
    virtual ~IObservable() = default;
};

class Stock : public IObservable{
    float price;
    list<shared_ptr<IObserver>> observers;
public:
    void setPrice(float newPrice) {
        price = newPrice;
        notify();
    }

    float getPrice() const {
        return price;
    }

    void add(shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
    }

    void remove(shared_ptr<IObserver> observer) override {
        observers.remove(observer);
    }

    void notify() override {
        for (auto& observer : observers) {
            observer->update(price);
        }
    }
};

class Investor : public IObserver{
private:
    float _currentPrice;
    string _name;

public:
    Investor(string name) : _name(name), _currentPrice(0.0f) {}

    void update(float newPrice) override {
        _currentPrice = newPrice;
        display();
    }

    void display() const {
        cout << "Investor " << _name << " current stock price: " << _currentPrice << endl;
    }
};

int main(){
    Stock stock;
    auto investor1 = make_shared<Investor>("Ahmed");
    auto investor2 = make_shared<Investor>("Mohamed");
    auto investor3 = make_shared<Investor>("Ali");

    stock.add(investor1);
    stock.add(investor2);

    stock.setPrice(100.0f);
    sleep(2);
    stock.setPrice(105.5f);
    sleep(2);
    stock.add(investor3); // adding a new investor mid runtime
    stock.setPrice(110.0f);
    sleep(2);
    stock.remove(investor2); // removing an investor mid runtime
    stock.setPrice(212.0f);
    sleep(2);
    stock.setPrice(60.75f);

    return 0;
}
