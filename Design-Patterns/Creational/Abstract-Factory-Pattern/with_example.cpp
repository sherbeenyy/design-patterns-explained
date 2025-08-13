#include <iostream>
#include <memory>
#include <unistd.h>
using namespace std;

// ----- abstract products -----
class IBoss
{
public:
    virtual void attack() = 0;
    virtual ~IBoss() = default;
};

class ISupport
{
public:
    virtual void support() = 0;
    virtual ~ISupport() = default;
};

// ----- abstract factory -----
class IEnemyFactory
{
public:
    virtual shared_ptr<IBoss> spawnBoss() = 0;
    virtual shared_ptr<ISupport> spawnSupport() = 0;
    virtual ~IEnemyFactory() = default;
};

// ----- concrete products -----
class SkeletonGiant : public IBoss
{
public:
    void attack() override
    {
        cout << "Skeleton Giant smashes with a huge bone!" << endl;
    }
};

class GoblinGiant : public IBoss
{
public:
    void attack() override
    {
        cout << "Goblin Giant hits with his fist!" << endl;
    }
};

class SkeletonBomber : public ISupport
{
public:
    void support() override
    {
        cout << "Skeleton Bomber throws explosive skulls!" << endl;
    }
};

class SpearGoblin : public ISupport
{
public:
    void support() override
    {
        cout << "Spear Goblin throws sharp spears!" << endl;
    }
};

// ----- concrete factories -----
class SkeletonGangFactory : public IEnemyFactory
{
public:
    shared_ptr<IBoss> spawnBoss() override
    {
        return make_shared<SkeletonGiant>();
    }
    shared_ptr<ISupport> spawnSupport() override
    {
        return make_shared<SkeletonBomber>();
    }
};

class GoblinSquadFactory : public IEnemyFactory
{
public:
    shared_ptr<IBoss> spawnBoss() override
    {
        return make_shared<GoblinGiant>();
    }
    shared_ptr<ISupport> spawnSupport() override
    {
        return make_shared<SpearGoblin>();
    }
};

int main()
{
    int level = 2; // change to test different gangs

    shared_ptr<IEnemyFactory> factory;

    if (level == 1)
    {
        factory = make_shared<SkeletonGangFactory>();
    }
    else
    {
        factory = make_shared<GoblinSquadFactory>();
    }

    auto boss = factory->spawnBoss();
    auto support = factory->spawnSupport();

    cout << "=== Boss Appears! ===" << endl;
    sleep(2);
    boss->attack();
    sleep(2);
    cout << "=== Support Joins! ===" << endl;
    sleep(2);
    support->support();

    return 0;
}
