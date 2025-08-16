#include <iostream>
#include <string>
using namespace std;

// receiver - The actual Lamp
class Lamp
{
    int brightness = 50; // default 50%
public:
    void turnOn() { cout << "Lamp is ON\n"; }
    void turnOff() { cout << "Lamp is OFF\n"; }
};

//  tightly coupled to Lamp
class RemoteControl
{
    Lamp *lamp;

public:
    RemoteControl(Lamp *l) : lamp(l) {}

    // instead of commands, it has hardcoded logic
    void pressButton(const string &button)
    {
        if (button == "green")
        {
            lamp->turnOn();
        }
        else if (button == "red")
        {
            lamp->turnOff();
        }
        else
        {
            cout << "Unknown button: " << button << "\n";
        }
    }
};

int main()
{
    Lamp myLamp;
    RemoteControl remote(&myLamp);

    // btn are hardcoded. user cannot change behavior
    remote.pressButton("green");
    remote.pressButton("red");
    remote.pressButton("blue");
    remote.pressButton("yellow");

    return 0;
}
