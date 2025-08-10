#include <iostream>
#include <string>
using namespace std;

class IWorker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
    virtual ~IWorker() {}
};

class HumanWorker : public IWorker {
public:
    void work() override {
        cout << "Human working..." << endl;
    }
    void eat() override {
        cout << "Human eating..." << endl;
    }
    void sleep() override {
        cout << "Human sleeping..." << endl;
    }
};

class RobotWorker : public IWorker {
public:
    void work() override {
        cout << "Robot working..." << endl;
    }
    void eat() override {
        cout << "msh bakol y3m!" << endl; // irrelevant method
    }
    void sleep() override {
        cout << "msh banam y3m!" << endl; // irrelevant method
    }
};

int main() {
    HumanWorker h;
    RobotWorker r;

    h.work();
    h.eat();
    h.sleep();

    r.work();
    r.eat();  // nonsense output
    r.sleep(); // nonsense output
}
