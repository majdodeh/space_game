#include "Terrain.h"

Terrain::Terrain() {
    dimX = 900;
    dimY = 900;
}

Terrain::Terrain(int width, int height) {
    dimX = width;
    dimY = height;
}

int Terrain::getDimX() const {
    return dimX;
}

void Terrain::setDimX(int newDimX) {
    dimX = newDimX;
}

int Terrain::getDimY() const {
    return dimY;
}

void Terrain::setDimY(int newDimY) {
    dimY = newDimY;
}
