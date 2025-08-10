#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bird {
public:
    virtual void fly() {
        cout << "I am flying!" << endl;
    }
};

class Sparrow : public Bird {
public:
    void fly() override {
        cout << "Sparrow is flying!" << endl;
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        cout << "I can't fly!" << endl; // Violates LSP: Penguin is a Bird but breaks expected behavior
    }
};

void makeBirdFly(Bird* bird) {
    bird->fly();
}

int main() {
    vector<Bird*> birds;
    birds.push_back(new Sparrow());
    birds.push_back(new Penguin()); // This will produce unexpected output

    for (auto bird : birds) {
        makeBirdFly(bird);
    }

    // cleaning up pointers 
    for (auto bird : birds) {
        delete bird;
    }
}
