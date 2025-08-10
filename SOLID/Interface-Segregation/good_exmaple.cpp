#include <iostream>
#include <string>
using namespace std;

class IWorkable {
public:
    virtual void work() = 0;
    virtual ~IWorkable() {}
};

class IEatable {
public:
    virtual void eat() = 0;
    virtual ~IEatable() {}
};

class ISleepable {
public:
    virtual void sleep() = 0;
    virtual ~ISleepable() {}
};

class HumanWorker : public IWorkable, public IEatable, public ISleepable {
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

class RobotWorker : public IWorkable {
public:
    void work() override {
        cout << "Robot working..." << endl;
    }
};

int main() {
    HumanWorker h;
    RobotWorker r;

    h.work();
    h.eat();
    h.sleep();

    r.work();
}
