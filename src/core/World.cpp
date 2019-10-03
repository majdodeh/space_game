#include <cmath>
#include "World.h"

World::World() : buddy(), hunter(), space(), highScore(), health() {
    gameStatus = false;
    ammo = 20;
}

World::World(int gameWidth, int gameHeight, int cowPosX, int cowPosY, int hunterPosX, int hunterPosY) : buddy(cowPosX, cowPosY), hunter(hunterPosX,hunterPosY), space(gameWidth, gameHeight), score(), health() {
    gameStatus = false;
    ammo = 20;

    cout<<"The window is with size "<<space.getDimX()<<" x "<<space.getDimY()<<endl;
    cout<<"The Cow is initialized on x:"<<buddy.getPosition().getPosX()<<" and y:"<<buddy.getPosition().getPosY()<<endl;
}

Terrain& World::getTerrain() {
    return space;
}

Cow& World::getCow() {
    return buddy;
}

Hunter& World::gethunter() {
    return hunter;
}


Score& World::getScore() {
    return score;
}

Score& World::getHighScore() {
    return highScore;
}

Health &World::getHealth() {
    return health;
}

vector<Asteroid> World::getAsteroidsTxt() const {
    return asteroids;
}

vector<Object> World::getBulletsTxt() const {
    return bullets;
}

vector<Object> World::getAmmoBonusTxt() const {
    return ammoBonus;
}

vector<Asteroid> World::getAsteroids() const {
    return asteroids;
}

vector<Object> World::getBullets() const {
    return bullets;
}

vector<Object> World::getBulletsHunter() const {
    return bulletsH;
}


vector<Object> World::getAmmoBonus() const {
    return ammoBonus;
}

vector<Object> World::getHealthBonus() const {
    return healthBonus;
}

int World::getAmmo() const {
    return ammo;
}

void World::setGameStatus(bool status) {
    gameStatus = status;
}

bool World::getGameStatus() const {
    return gameStatus;
}

void World::moveCow(int button) {
    switch(button) {
        case 'w' :
            buddy.up();
            break;
        case 's' :
            buddy.down();
            break;
        case 'd' :
            buddy.right();
            break;
        case 'a' :
            buddy.left();
            break;
        default:break;
    }
}

void World::addCowPosX(int valueX) {
    buddy.addPosX(valueX);
}

void World::addCowPosY(int valueY) {
    buddy.addPosY(valueY);
}

void World::updateAsteroidsTxt() {
    // update existing asteroids vector
    for(size_t i = 0; i < asteroids.size(); i++) {
        if (asteroids.at(i).getPosition().getPosY() > getTerrain().getDimY()){
            asteroids.erase(asteroids.begin() + i);
        }else{
            asteroids.at(i).update();
        }
    }

    // create new random asteroid
    Asteroid randomAsteroid(rand() % getTerrain().getDimX(), 0);
    // push the new random asteroid into the vector
    asteroids.push_back(randomAsteroid);
}

void World::removeAsteroidTxt(size_t id) {
    // remove the asteroid at the
    asteroids.erase(asteroids.begin() + id);
}

bool World::verifyCrashTxt(size_t id) {
    if (buddy.getPosition().getPosX() == asteroids.at(id).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY() == asteroids.at(id).getPosition().getPosY()) {
            return true;
        }
    }
    if (buddy.getPosition().getPosX()+1 == asteroids.at(id).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY()+1 == asteroids.at(id).getPosition().getPosY()) {
            return true;
        }
    }
    if (buddy.getPosition().getPosX()-1 == asteroids.at(id).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY()+1 == asteroids.at(id).getPosition().getPosY()) {
            return true;
        }
    }
    if (buddy.getPosition().getPosX() == asteroids.at(id).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY()+1 == asteroids.at(id).getPosition().getPosY()) {
            return true;
        }
    }
    return false;
}

void World::updateAsteroidsSdl() {
    // update existing asteroids vector
    for(size_t i = 0; i < asteroids.size(); i++) {
        if (asteroids.at(i).getPosition().getPosY() > getTerrain().getDimY()){
            asteroids.erase(asteroids.begin() + i);
        }else{
            asteroids.at(i).update();
        }
    }
}

void World::addAsteroidsSdl() {
    // create new random asteroid
    Asteroid randomAsteroid(rand() % 720, -80, 70);
    // push the new random asteroid into the vector
    asteroids.push_back(randomAsteroid);
}

void World::removeAsteroidSdl(size_t id) {
    // remove the asteroid at the
    asteroids.erase(asteroids.begin() + id);
}

void World::asteroidCrashed(size_t id) {
    // remove the asteroid at the
    asteroids.at(id).setCrashed(true);
}

bool World::verifyAsteroidCowCrashSdl(size_t id) {
    if (verifyDistanceAsteroidCow(id)) {
            return true;
    }
    return false;
}

bool World::verifyDistanceAsteroidCow(size_t id) {
    if (buddy.getPosition().getPosX()+25 <= asteroids.at(id).getPosition().getPosX()+70 && buddy.getPosition().getPosX()+75 >= asteroids.at(id).getPosition().getPosX()+10) {
        if (buddy.getPosition().getPosY()+25 <= asteroids.at(id).getPosition().getPosY()+70 && buddy.getPosition().getPosY()+75 >= asteroids.at(id).getPosition().getPosY()+10) {
            return true;
        }
    }
    return false;
}

void World::AnimationAsteroid(size_t id) {
    asteroids.at(id).addframe(1);
}


void World::updateHunterSdl() {

    if (hunter.getPosition().getPosX() < (buddy.getPosition().getPosX())) {
        hunter.setSens(1);
    }
    else if (hunter.getPosition().getPosX() > (buddy.getPosition().getPosX())) {
        hunter.setSens(-1);
    }else {hunter.setSens(0);}
    hunter.update();
}

void World::updateBulletsHunterSdl() {
    for(size_t i = 0; i < bulletsH.size(); i++) {
        if (bulletsH.at(i).getPosition().getPosY() >= getTerrain().getDimY()){
            bulletsH.erase(bulletsH.begin() + i);
        }else{
            bulletsH.at(i).updatePosDown();
        }
    }
}

void World::fireBulletHunterSdl() {
    int posX = hunter.getPosition().getPosX() + 35;
    int posY = hunter.getPosition().getPosY() + 35;
    Object newBullet(posX, posY);

    bulletsH.push_back(newBullet);
}

void World::removeBulletHunter(size_t id) {
    bulletsH.erase(bulletsH.begin() + id);
}

bool World::verifyBulletCowHunterSdl(size_t idBullet) {
    if (buddy.getPosition().getPosX()+10 <= bulletsH.at(idBullet).getPosition().getPosX()+25 && buddy.getPosition().getPosX()+90 >= bulletsH.at(idBullet).getPosition().getPosX()+5) {
        if (buddy.getPosition().getPosY()+40 <= bulletsH.at(idBullet).getPosition().getPosY()+25 && buddy.getPosition().getPosY()+90 >= bulletsH.at(idBullet).getPosition().getPosY()+5) {
            return true;
        }
    }
    return false;
}

void World::updateHealthBonus() {
    // update existing healthBonus vector
    for(size_t i = 0; i < healthBonus.size(); i++) {
        if (healthBonus.at(i).getPosition().getPosY() > getTerrain().getDimY()){
            healthBonus.erase(healthBonus.begin() + i);
        }else{
            healthBonus.at(i).updatePosDown();
        }
    }
}

void World::addHealthBonus() {
    Object randomHealthBonus(rand() % getTerrain().getDimX(), -30, rand() % 9 + 1);
    // push the new random healthBonus into the vector
    healthBonus.push_back(randomHealthBonus);
}

void World::removeHealthBonus(size_t id) {
    healthBonus.erase(healthBonus.begin() + id);
}


bool World::verifyHealthBonusCow(size_t idHealthBonus) {
    if (buddy.getPosition().getPosX()+25 <= healthBonus.at(idHealthBonus).getPosition().getPosX()+40 && buddy.getPosition().getPosX()+75 >= healthBonus.at(idHealthBonus).getPosition().getPosX()+10) {
        if (buddy.getPosition().getPosY()+25 <= healthBonus.at(idHealthBonus).getPosition().getPosY()+40 && buddy.getPosition().getPosY()+75 >= healthBonus.at(idHealthBonus).getPosition().getPosY()+10) {
            return true;
        }
    }
    return false;
}

void World::fireBullet() {
    int posX = buddy.getPosition().getPosX();
    int posY = buddy.getPosition().getPosY() - 1;
    Object newBullet(posX, posY);

    bullets.push_back(newBullet);
}

void World::updateBullets() {
    // update existing Bullets vector
    for(size_t i = 0; i < bullets.size(); i++) {
        if (bullets.at(i).getPosition().getPosY() <= 1){
            bullets.erase(bullets.begin() + i);
        }else{
            bullets.at(i).updatePosUp();
        }
    }
}

void World::fireBulletSdl() {
    int posX = buddy.getPosition().getPosX() + 35;
    int posY = buddy.getPosition().getPosY() + 35;
    Object newBullet(posX, posY);

    bullets.push_back(newBullet);
}

void World::updateBulletsSdl() {
    // update existing Bullets vector
    for(size_t i = 0; i < bullets.size(); i++) {
        if (bullets.at(i).getPosition().getPosY() <= -30){
            bullets.erase(bullets.begin() + i);
        }else{
            bullets.at(i).updatePosUp();
        }
    }
}

void World::updateAmmo() {
    ammo -= 1;
}

void World::increaseAmmo(int bonus) {
    ammo += bonus;
}

void World::removeBullet(size_t id) {
    bullets.erase(bullets.begin() + id);
}


bool World::verifyBulletAsteroid(size_t idBullet, size_t idAsteroid) {
    if (bullets.at(idBullet).getPosition().getPosX() == asteroids.at(idAsteroid).getPosition().getPosX()) {
        if (bullets.at(idBullet).getPosition().getPosY() == asteroids.at(idAsteroid).getPosition().getPosY()) {
            return true;
        }
        if (bullets.at(idBullet).getPosition().getPosY()+1 == asteroids.at(idAsteroid).getPosition().getPosY()) {
            return true;
        }
    }
    return false;
}


bool World::verifyBulletAsteroidSdl(size_t idBullet, size_t idAsteroid) {
    if (bullets.at(idBullet).getPosition().getPosX()+5 <= asteroids.at(idAsteroid).getPosition().getPosX()+66 && bullets.at(idBullet).getPosition().getPosX()+25 >= asteroids.at(idAsteroid).getPosition().getPosX()+15) {
        if (bullets.at(idBullet).getPosition().getPosY() <= asteroids.at(idAsteroid).getPosition().getPosY()+62 && bullets.at(idBullet).getPosition().getPosY()+30 >= asteroids.at(idAsteroid).getPosition().getPosY()+19) {
            return true;
        }
    }
    return false;
}



void World::updateAmmoBonusTxt() {
    // update existing asteroids vector
    for(size_t i = 0; i < ammoBonus.size(); i++) {
        if (ammoBonus.at(i).getPosition().getPosY() > getTerrain().getDimY()){
            ammoBonus.erase(ammoBonus.begin() + i);
        }else{
            ammoBonus.at(i).updatePosDown();
        }
    }
}

void World::addAmmoBonusTxt() {

    Object randomAmmoBonus(rand() % getTerrain().getDimX(), 0, rand() % 9 + 1);
    // push the new random ammoBonus into the vector
    ammoBonus.push_back(randomAmmoBonus);
}

void World::updateAmmoBonusSdl() {
    // update existing asteroids vector
    for(size_t i = 0; i < ammoBonus.size(); i++) {
        if (ammoBonus.at(i).getPosition().getPosY() > getTerrain().getDimY()){
            ammoBonus.erase(ammoBonus.begin() + i);
        }else{
            ammoBonus.at(i).updatePosDown();
        }
    }
}

void World::addAmmoBonusSdl() {
    Object randomAmmoBonus(rand() % getTerrain().getDimX(), -30, rand() % 9 + 1);
    // push the new random ammoBonus into the vector
    ammoBonus.push_back(randomAmmoBonus);
}

void World::removeAmmoBonus(size_t id) {
    ammoBonus.erase(ammoBonus.begin() + id);
}


bool World::verifyAmmoBonusCow(size_t idAmmoBonus) {
    if (buddy.getPosition().getPosX() == ammoBonus.at(idAmmoBonus).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY() == ammoBonus.at(idAmmoBonus).getPosition().getPosY()) {
            return true;
        }
    }
    if (buddy.getPosition().getPosX()+1 == ammoBonus.at(idAmmoBonus).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY()+1 == ammoBonus.at(idAmmoBonus).getPosition().getPosY()) {
            return true;
        }
    }
    if (buddy.getPosition().getPosX()-1 == ammoBonus.at(idAmmoBonus).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY()+1 == ammoBonus.at(idAmmoBonus).getPosition().getPosY()) {
            return true;
        }
    }
    if (buddy.getPosition().getPosX() == ammoBonus.at(idAmmoBonus).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY()+1 == ammoBonus.at(idAmmoBonus).getPosition().getPosY()) {
            return true;
        }
    }
    return false;
}

bool World::verifyAmmoBonusCowSdl(size_t idAmmoBonus) {
    if (buddy.getPosition().getPosX()+25 <= ammoBonus.at(idAmmoBonus).getPosition().getPosX()+30 && buddy.getPosition().getPosX()+75 >= ammoBonus.at(idAmmoBonus).getPosition().getPosX()) {
        if (buddy.getPosition().getPosY()+25 <= ammoBonus.at(idAmmoBonus).getPosition().getPosY()+30 && buddy.getPosition().getPosY()+75 >= ammoBonus.at(idAmmoBonus).getPosition().getPosY()) {
            return true;
        }
    }
    return false;
}

void World::resetGameTxt(int buddyPosX, int buddyPosY, int newScore, int newHealth) {
    buddy.setPositionX(buddyPosX);
    buddy.setPositionY(buddyPosY);
    gameStatus = false;
    ammo =20;
    score.setScore(newScore);
    health.setHealth(newHealth);
    asteroids.clear();
    bullets.clear();
    ammoBonus.clear();
}

void World::resetGameSdl(int buddyPosX, int buddyPosY, int newScore, int newHealth) {
    buddy.setPositionX(buddyPosX);
    buddy.setPositionY(buddyPosY);
    gameStatus = false;
    ammo = 20;
    score.setScore(newScore);
    health.setHealth(newHealth);
    asteroids.clear();
    bullets.clear();
    bulletsH.clear();
    ammoBonus.clear();
    healthBonus.clear();
}

