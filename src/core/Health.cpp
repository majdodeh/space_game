#include "Health.h"
#include <assert.h>

Health::Health() {
    health = 100;
}

int Health::getHealth() const {
    return health;
}

void Health::setHealth(int newHealth) {
    health = newHealth;
}

void Health::addHealth(int points) {
        health += points;
    if(health > 100)
        health = 100;
}

void Health::removeHealth(int points) {
        health -= points;
    if(health < 0)
        health = 0;
}

bool Health::verifyDead() const {
    return health > 0;
}
