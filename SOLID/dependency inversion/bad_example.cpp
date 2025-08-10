#include <iostream>
#include <string>
using namespace std;

class Keyboard {
public:
    void input() {
        cout << "Typing on keyboard..." << endl;
    }
};

class Computer {
public:
    void start() {
        Keyboard keyboard;
        keyboard.input(); // direct dependency
    }
};

int main() {
    Computer computer;
    computer.start();
}
