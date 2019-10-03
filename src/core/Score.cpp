#include "Score.h"

Score::Score() {
    score = 0;
}

int Score::getScore() const {
    return score;
}

void Score::setScore(int newScore) {
    score = newScore;
}

void Score::addScore(int points) {
    score += points;
}
