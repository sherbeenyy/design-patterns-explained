#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

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

int main() {
    srand(static_cast<unsigned>(time(nullptr))); 

    // we decide enemy creation logic here
    int enemyType = rand() % 3;

    shared_ptr<Ienemy> enemy;

    if (enemyType == 0) {
        enemy = make_shared<Goblin>();
    }
    else if (enemyType == 1) {
        enemy = make_shared<Dragon>();
    }
    else if (enemyType == 2) {
        enemy = make_shared<Wizard>();
    }

    enemy->attack();

    // if we wanted different spawn rules (e.g., by level),
    // we’d have to rewrite this entire section instead of just changing a factory
    int playerLevel = 7;
    shared_ptr<Ienemy> enemyByLevel;

    if (playerLevel > 0 && playerLevel < 5) {
        enemyByLevel = make_shared<Goblin>();
    }
    else if (playerLevel >= 5 && playerLevel < 10) {
        enemyByLevel = make_shared<Dragon>();
    }
    else {
        enemyByLevel = make_shared<Wizard>();
    }

    enemyByLevel->attack();

    return 0;
}
