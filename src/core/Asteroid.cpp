#include "Asteroid.h"


Asteroid::Asteroid() : pos() {
    size = 80;
    speed =2;
    crashed = false;

    //Initialisation des variables d'animation
}

Asteroid::Asteroid(int x, int y) : pos(x, y) {
    size = 80;
    speed = 2;
    crashed = false;


}

Asteroid::Asteroid(int x, int y, int new_size) : pos(x, y) {
    size = new_size;
    speed = 0;
    crashed = false;
    frame = 0;

}

Asteroid::~Asteroid() {
}

void Asteroid::update() {
    pos.plusOneY();
}

Position Asteroid::getPosition() const {
    return pos;
}

int Asteroid::getSize() const {
    return size;
}

void Asteroid::setSize(int sizeAsteroid) {
    size = sizeAsteroid;
}

int Asteroid::getSpeed() const {
    return speed;
}

void Asteroid::setSpeed(int speedAsteroid) {
    speed = speedAsteroid;
}

bool Asteroid::getCrashed() const {
    return crashed;
}

void Asteroid::setCrashed(bool value) {
    crashed = value;
}

int Asteroid::getShape() const {
    return shape;
}

void Asteroid::setShape(int number) {
    shape = number;
}

int Asteroid::getframe() {
    return frame;
}

void Asteroid::setframe(int new_frame) {
    frame = new_frame;
}

void Asteroid::addframe(int add) {
    frame = frame + add;
}

