#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
using namespace std;

// Receiver - The actual Lamp
class Lamp
{
    int brightness = 50; // default 50%
public:
    void turnOn() { cout << "Lamp is ON\n"; }
    void turnOff() { cout << "Lamp is OFF\n"; }
    void increaseBrightness()
    {
        if (brightness < 100)
            brightness += 10;
        cout << "Lamp brightness increased to " << brightness << "%\n";
    }
    void decreaseBrightness()
    {
        if (brightness > 0)
            brightness -= 10;
        cout << "Lamp brightness decreased to " << brightness << "%\n";
    }
};

// Command interface
class ICommand
{
public:
    virtual ~ICommand() {}
    virtual void execute() = 0;
};

// Concrete Commands
class TurnOnCommand : public ICommand
{
    Lamp *lamp;

public:
    TurnOnCommand(Lamp *l) : lamp(l) {}
    void execute() override { lamp->turnOn(); }
};

class TurnOffCommand : public ICommand
{
    Lamp *lamp;

public:
    TurnOffCommand(Lamp *l) : lamp(l) {}
    void execute() override { lamp->turnOff(); }
};

class IncreaseBrightnessCommand : public ICommand
{
    Lamp *lamp;

public:
    IncreaseBrightnessCommand(Lamp *l) : lamp(l) {}
    void execute() override { lamp->increaseBrightness(); }
};

class DecreaseBrightnessCommand : public ICommand
{
    Lamp *lamp;

public:
    DecreaseBrightnessCommand(Lamp *l) : lamp(l) {}
    void execute() override { lamp->decreaseBrightness(); }
};

// Invoker - The Remote Control
class RemoteControl
{
    unordered_map<string, shared_ptr<ICommand>> buttonMap;

public:
    void setCommand(const string &button, shared_ptr<ICommand> command)
    {
        buttonMap[button] = command;
    }
    void pressButton(const string &button)
    {
        if (buttonMap.find(button) != buttonMap.end())
        {
            buttonMap[button]->execute();
        }
        else
        {
            cout << "No command assigned to button " << button << "\n";
        }
    }
};

int main()
{
    Lamp myLamp;
    RemoteControl remote;

    auto onCmd = make_shared<TurnOnCommand>(&myLamp);
    auto offCmd = make_shared<TurnOffCommand>(&myLamp);
    auto incCmd = make_shared<IncreaseBrightnessCommand>(&myLamp);
    auto decCmd = make_shared<DecreaseBrightnessCommand>(&myLamp);

    // User assigns commands to colored buttons
    remote.setCommand("Red", onCmd);
    remote.setCommand("Green", incCmd);
    remote.setCommand("Blue", decCmd);
    remote.setCommand("Yellow", offCmd);

    // Simulate button presses
    remote.pressButton("Red");
    remote.pressButton("Green");
    remote.pressButton("Green");
    remote.pressButton("Blue");
    remote.pressButton("Yellow");

    return 0;
}
