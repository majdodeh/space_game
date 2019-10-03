#include "Hunter.h"


Hunter::Hunter() : pos() {
    sens = 0;
}

Hunter::Hunter(int x, int y) : pos(x, y) {
    sens = 0;
}

Hunter::~Hunter() {
}

void Hunter::update() {
    pos.addPosX(sens);
}

Position Hunter::getPosition() const {
    return pos;
}

int Hunter::getSens() {
    return sens;
}

void Hunter::setSens(int new_sens) {
    sens = new_sens;
}