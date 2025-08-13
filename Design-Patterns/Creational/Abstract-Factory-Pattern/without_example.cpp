#include <iostream>
#include <unistd.h> // for sleep
using namespace std;

// hardcoded enemy creation

// boss types
class SkeletonGiant
{
public:
    void attack()
    {
        cout << "Skeleton Giant smashes with a huge bone!" << endl;
    }
};

class GoblinGiant
{
public:
    void attack()
    {
        cout << "Goblin Giant hits with his fist!" << endl;
    }
};

// support types
class SkeletonBomber
{
public:
    void support()
    {
        cout << "Skeleton Bomber throws explosive skulls!" << endl;
    }
};

class SpearGoblin
{
public:
    void support()
    {
        cout << "Spear Goblin throws sharp spears!" << endl;
    }
};

int main()
{
    int level = 2; // change to test different gangs

    cout << "=== Boss Appears! ===" << endl;
    sleep(2);

    // instead of using factories, we hardcode every decision here
    if (level == 1)
    {
        SkeletonGiant boss;
        boss.attack();

        sleep(2);
        cout << "=== Support Joins! ===" << endl;
        SkeletonBomber support;
        support.support();
    }
    else
    {
        GoblinGiant boss;
        boss.attack();

        sleep(2);
        cout << "=== Support Joins! ===" << endl;
        SpearGoblin support;
        support.support();
    }

    return 0;
}
