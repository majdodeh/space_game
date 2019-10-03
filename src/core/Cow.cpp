#include "Cow.h"

Cow::Cow() {
    animation = false;
    crashTimer = 0;
    sens = 3;
    frame = 0;
}

Cow::Cow(int x, int y) : pos(x, y) {
    crashTimer = 0;
    sens = 3;
    frame = 0;
}

void Cow::left(){
    pos.minusOneX();
}

void Cow::right(){
    pos.plusOneX();
}

void Cow::up(){
    pos.minusOneY();
}

void Cow::down(){
    pos.plusOneY();
}

void Cow::addPosX(int valueX) {
    pos.addPosX(valueX);
}

void Cow::addPosY(int valueY) {
    pos.addPosY(valueY);
}

Position Cow::getPosition() const {
    return pos;
}

void Cow::setPositionX(int newX) {
    pos.setPosX(newX);
}

void Cow::setPositionY(int newY) {
    pos.setPosY(newY);

}

bool Cow::getAnimation() const {
    return animation;
}

void Cow::setAnimation(bool value) {
    animation = value;
}

int Cow::getCrashTimer() const {
    return crashTimer;
}

void Cow::setCrashTimer(int new_CrashTimer) {
    crashTimer = new_CrashTimer;
}

int Cow::getSens() {
    return sens;
}

void Cow::setSens(int new_sens) {
    sens = new_sens;
}

int Cow::getframe() {
    return frame;
}

void Cow::setframe(int new_frame) {
    frame = new_frame;
}

void Cow::addframe(int add) {
    frame = frame + add;
}



