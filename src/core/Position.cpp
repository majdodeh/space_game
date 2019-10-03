#include "Position.h"


Position::Position() {
    x = y = 0;
}

Position::Position(int posX, int posY){
    x = posX;
    y = posY;
}

int Position::getPosX() const {
    return x;
}

int Position::getPosY() const {
    return y;
}

void Position::setPosX(int posX) {
    x = posX;

}

void Position::setPosY(int posY) {
    y = posY;

}

void Position::addPosX(int valueX) {
    x += valueX;
}

void Position::addPosY(int valueY) {
    y += valueY;
}

void Position::plusOneX() {
   x++ ;

}


void Position::plusOneY() {
    y++ ;

}

void Position::minusOneX() {
    x-- ;

}


void Position::minusOneY() {
    y-- ;

}
