#ifndef PROJECT_WORLD_H
#define PROJECT_WORLD_H


#include <vector>
#include <iostream>
#include <math.h>
#include "Cow.h"
#include "Terrain.h"
#include "Asteroid.h"
#include "Score.h"
#include "Health.h"
#include "Object.h"
#include "Hunter.h"

using namespace std;

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       World class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

class World {

private:
    Cow buddy;
    Hunter hunter;
    Terrain space;
    Score score;
    Score highScore;
    Health health;
    bool gameStatus;
    int ammo;

    vector<Asteroid> asteroids;
    vector<Object> bullets;
    vector<Object> bulletsH;
    vector<Object> ammoBonus;
    vector<Object> healthBonus;

public:

    /**
    * \brief Constructor
    */
    World();

    /**
    * \brief Constructor
    * @param int gameWidth, int gameHeight, int cowPosX, int cowPosY,int hunterPosX, int hunterPosY
    */
    World(int gameWidth, int gameHeight, int cowPosX, int cowPosY,int hunterPosX, int hunterPosY);

    /**
    * \brief Accessor
    * get Terrain
    * @return Terrain
    */
    Terrain& getTerrain();

    /**
    * \brief Accessor
    * get Cow
    * @return Cow
    */
    Cow& getCow();

    /**
    * \brief Accessor
    * get hunter
    * @return Hunter
    */
    Hunter& gethunter();

    /**
    * \brief Accessor
    * get score
    * @return Score
    */
    Score& getScore();

    /**
    * \brief Accessor
    * get high score
    * @return Score
    */
    Score& getHighScore();

    /**
    * \brief Accessor
    * get health
    * @return Health
    */
    Health& getHealth();

    /**
    * \brief Accessor
    * get ammo points
    * @return int
    */
    int getAmmo() const;

    /**
    * \brief increas ammo points
    * @param int bonus
    */
    void increaseAmmo(int bonus);

    /**
    * \brief Accessor
    * get asteroids txt
    * @return vector<Asteroid>
    */
    vector<Asteroid> getAsteroidsTxt() const;

    /**
    * \brief Accessor
    * get bullets txt
    * @return vector<Object>
    */
    vector<Object> getBulletsTxt() const;

    /**
    * \brief Accessor
    * get ammo bonus txt
    * @return vector<Object>
    */
    vector<Object> getAmmoBonusTxt() const;

    /**
    * \brief Accessor
    * get asteroids
    * @return vector<Asteroid>
    */
    vector<Asteroid> getAsteroids() const;

    /**
    * \brief Accessor
    * get bullets
    * @return vector<Object>
    */
    vector<Object> getBullets() const;

    /**
    * \brief Accessor
    * get hunter bullets
    * @return vector<Object>
    */
    vector<Object> getBulletsHunter() const;

    /**
    * \brief Accessor
    * get ammo bonus
    * @return vector<Object>
    */
    vector<Object> getAmmoBonus() const;

    /**
    * \brief Accessor
    * get health bonus
    * @return vector<Object>
    */
    vector<Object> getHealthBonus() const;

    /**
    * \brief Mutator
    * set game size
    * @param int
    */
    void setGameStatus(bool status);

    /**
    * \brief Accessor
    * get game status
    * @return bool
    */
    bool getGameStatus() const;

    /**
    * \brief move cow
    * @param int button
    */
    void moveCow(int button);

    /**
    * \brief add Cow Pos X
    * @param int valueX
    */
    void addCowPosX(int valueX);

    /**
    * \brief add Cow Pos Y
    * @param int valueY
    */
    void addCowPosY(int valueY);


    /**
    * \brief update asteroids txt
    */
    void updateAsteroidsTxt();

    /**
    * \brief remove asteroid txt
    * @param size_t id
    */
    void removeAsteroidTxt(size_t id);

    /**
    * \brief verify crash txt
    * @param size_t id
    * @return bool
    */
    bool verifyCrashTxt(size_t id);

    /**
    * \brief update asteroids
    */
    void updateAsteroidsSdl();

    /**
    * \brief add asteroid
    */
    void addAsteroidsSdl();

    /**
    * \brief remove asteroid
    * @param size_t id
    */
    void removeAsteroidSdl(size_t id);

    /**
    * \brief set asteroid as crashed
    * @param size_t id
    */
    void asteroidCrashed(size_t id);


    /**
    * \brief verify crash between asteroids and cow
    * @param size_t id
    * @return bool
    */
    bool verifyAsteroidCowCrashSdl(size_t id);

    /**
    * \brief verify distance between cow and asteroids
    * @param size_t id
    * @return bool
    */
    bool verifyDistanceAsteroidCow(size_t id);

    /**
    * \brief asteroid's animation
    * @param size_t id
    */
    void AnimationAsteroid(size_t id);


    /**
    * \brief update hunter
    */
    void updateHunterSdl();

    /**
    * \brief update hunter's bullets
    */
    void updateBulletsHunterSdl();

    /**
    * \brief fire hunter bullet
    */
    void fireBulletHunterSdl();

    /**
    * \brief remove hunter's bullets
    * @param size_t id
    */
    void removeBulletHunter(size_t id);

    /**
    * \brief verify if hunter's bullets crashed with cow
    * @param size_t idBullet
    * @return bool
    */
    bool verifyBulletCowHunterSdl(size_t idBullet);


    /**
    * \brief update health bonus object
    */
    void updateHealthBonus();

    /**
    * \brief add health bonus object
    */
    void addHealthBonus();

    /**
    * \brief remove health bonus object
    * @param size_t id
    */
    void removeHealthBonus(size_t id);

    /**
    * \brief verify if get health bonus object
    * @param size_t id
    * @return bool
    */
    bool verifyHealthBonusCow(size_t id);

    /**
    * \brief fire bullet
    */
    void fireBullet();

    /**
    * \brief update bullets objects
    */
    void updateBullets();

    /**
    * \brief fire bullet sdl
    */
    void fireBulletSdl();

    /**
    * \brief update bullets objects sdl
    */
    void updateBulletsSdl();

    /**
    * \brief update ammo objects
    */
    void updateAmmo();

    /**
    * \brief remove bullet object
    * @param size_t id
    */
    void removeBullet(size_t id);

    /**
    * \brief verify crash between bullets and asteroids
    * @param size_t idBullet, size_t idAsteroid
    * @return bool
    */
    bool verifyBulletAsteroid(size_t idBullet, size_t idAsteroid);

    /**
    * \brief veridy crash between bullet and asteroids
    * @param size_t idBullet, size_t idAsteroid
    * @return bool
    */
    bool verifyBulletAsteroidSdl(size_t idBullet, size_t idAsteroid);


    /**
    * \brief update ammo bonus object txt
    */
    void updateAmmoBonusTxt();

    /**
    * \brief add ammo bonus object txt
    */
    void addAmmoBonusTxt();

    /**
    * \brief update ammo bonus sdl
    */
    void updateAmmoBonusSdl();

    /**
    * \brief add ammo bonus object
    */
    void addAmmoBonusSdl();

    /**
    * \brief remove ammo bonus object
    * @param size_t id
    */
    void removeAmmoBonus(size_t id);

    /**
    * \brief verify ammo bonus
    * @return bool
    */
    bool verifyAmmoBonusCow(size_t idAmmoBonus);

    /**
    * \brief verify ammo bonus sdl
    * @return bool
    */
    bool verifyAmmoBonusCowSdl(size_t idAmmoBonus);


    /**
    * \brief reset game text
    * @param int buddyPosX, int buddyPosY, int newScore, int newHealth
    */
    void resetGameTxt(int buddyPosX, int buddyPosY, int newScore, int newHealth);

    /**
    * \brief reset game sdl
    * @param int buddyPosX, int buddyPosY, int newScore, int newHealth
    */
    void resetGameSdl(int buddyPosX, int buddyPosY, int newScore, int newHealth);


};

#endif //PROJECT_WORLD_H
