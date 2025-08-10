#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bird {
public:
    virtual void eat() {
        cout << "I am eating!" << endl;
    }
};

class FlyingBird : public Bird {
public:
    virtual void fly() {
        cout << "I am flying!" << endl;
    }
};

class Sparrow : public FlyingBird {
public:
    void fly() override {
        cout << "Sparrow is flying!" << endl;
    }
};

class Penguin : public Bird {
public:
    void swim() {
        cout << "Penguin is swimming!" << endl;
    }
};

void makeFlyingBirdFly(FlyingBird* bird) {
    bird->fly();
}

int main() {
    vector<FlyingBird*> flyingBirds;
    flyingBirds.push_back(new Sparrow());
    // flyingBirds.push_back(new Penguin()); // Not allowed: Penguin is not a FlyingBird

    for (auto bird : flyingBirds) {
        makeFlyingBirdFly(bird);
    }

    // Example with Penguin
    Penguin p;
    p.eat();
    p.swim();

    // Cleaning up pointers
    for (auto bird : flyingBirds) {
        delete bird;
    }
}
