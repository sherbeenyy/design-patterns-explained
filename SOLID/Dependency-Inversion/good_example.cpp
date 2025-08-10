#include <iostream>
#include <string>
using namespace std;


class IInputDevice {
public:
    virtual void input() = 0;
    virtual ~IInputDevice() {}
};

class Keyboard : public IInputDevice {
public:
    void input() override {
        cout << "Typing on keyboard..." << endl;
    }
};

class Mouse : public IInputDevice {
public:
    void input() override {
        cout << "Clicking mouse..." << endl;
    }
};

class Computer {

private:
    IInputDevice* inputDevice;

public:
    Computer(IInputDevice* device) : inputDevice(device) {}

    void start() {
        inputDevice->input();
    }
};

int main() {
    Computer computer(new Keyboard()); // it's not tightly coupling anymore !
    computer.start();

    Computer computer2(new Mouse());
    computer2.start();

    return 0;
}
