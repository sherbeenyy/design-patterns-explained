#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

// enemy Interface
class Ienemy {
public:
    virtual void attack() = 0;
    virtual ~Ienemy() = default;
};

class Goblin : public Ienemy {
public:
    void attack() override {
        cout << "Goblin attacks with a dagger!" << endl;
    }
};

class Dragon : public Ienemy {
public:
    void attack() override {
        cout << "Dragon breathes fire!" << endl;
    }
};

class Wizard : public Ienemy {
public:
    void attack() override {
        cout << "Wizard cursed you!" << endl;
    }
};

// factory interface 
class IEnemyFactory {
public:
    virtual shared_ptr<Ienemy> createEnemy() = 0;
    virtual ~IEnemyFactory() = default;
};

// random enemy factory 
class randomEnemySpawn : public IEnemyFactory {
public:
    shared_ptr<Ienemy> createEnemy() override {
        int enemyType = rand() % 3;  // random number between 0 and 2

        switch (enemyType) {
        case 0: return make_shared<Goblin>();
        case 1: return make_shared<Dragon>();
        case 2: return make_shared<Wizard>();
        default: return nullptr;
        }
    }
};

// level based enemy factory
class byLevelEnemySpawn : public IEnemyFactory {
    int level;
public:
    byLevelEnemySpawn(int lvl) : level(lvl) {}

    shared_ptr<Ienemy> createEnemy() override {
        if (level < 0) return nullptr;

        if (level > 0 && level < 5) {
            return make_shared<Goblin>();
        } 
        else if (level >= 5 && level < 10) {
            return make_shared<Dragon>();
        } 
        else {
            return make_shared<Wizard>();
        }
    }
};


int main() {
    srand(static_cast<unsigned>(time(nullptr))); // seed random

    // random enemy spawner
    shared_ptr<IEnemyFactory> randomSpawner = make_shared<randomEnemySpawn>();
    shared_ptr<Ienemy> randomEnemy = randomSpawner->createEnemy();
    randomEnemy->attack();

    cout << "------------------------" << endl;

    // level based enemy spawner
    int playerLevel = 7;
    shared_ptr<IEnemyFactory> levelSpawner = make_shared<byLevelEnemySpawn>(playerLevel);
    shared_ptr<Ienemy> levelEnemy = levelSpawner->createEnemy();
    levelEnemy->attack();

    return 0;
}
