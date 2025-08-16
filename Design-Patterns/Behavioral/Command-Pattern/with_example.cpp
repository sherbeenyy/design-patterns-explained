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
};

// Command interface
class ICommand
{
public:
    virtual ~ICommand() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete Commands
class TurnOnCommand : public ICommand
{
    Lamp *lamp;

public:
    TurnOnCommand(Lamp *l) : lamp(l) {}
    void execute() override { lamp->turnOn(); }
    void undo() override { lamp->turnOff(); }
};

class TurnOffCommand : public ICommand
{
    Lamp *lamp;

public:
    TurnOffCommand(Lamp *l) : lamp(l) {}
    void execute() override { lamp->turnOff(); }
    void undo() override { lamp->turnOn(); }
};

// invoker - The Remote Control
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

    // User assigns commands to colored buttons
    remote.setCommand("green", onCmd);
    remote.setCommand("red", offCmd);

    // Simulate button presses
    remote.pressButton("green");
    remote.pressButton("red");

    return 0;
}
