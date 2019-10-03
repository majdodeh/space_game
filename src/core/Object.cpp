#include "Object.h"

Object::Object() : pos() {
    size = 0;
    speed = 0;
}

Object::Object(int x, int y) : pos(x, y) {
    size = 0;
    speed = 0;
}


Object::Object(int x, int y, int v) : pos(x, y) {
    size = 0;
    speed = 0;
    value = v;
}

Object::Object(int x, int y, int oSize = 0, int oSpeed = 0) : pos(x, y) {
    size = oSize;
    speed = oSpeed;
}

void Object::updatePosDown() {
    pos.plusOneY();
}

void Object::updatePosUp() {
    pos.minusOneY();
}

Position Object::getPosition() const {
    return pos;
}

int Object::getSize() const {
    return size;
}

void Object::setSize(int sizeObject) {
    size = sizeObject;
}

int Object::getSpeed() const {
    return speed;
}

void Object::setSpeed(int speedObject) {
    speed = speedObject;
}

int Object::getValue() const {
    return value;
}

void Object::setValue(int valueObject) {
    speed = valueObject;
}
