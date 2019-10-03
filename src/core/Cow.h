#ifndef PROJECT_COW_H
#define PROJECT_COW_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Cow class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

#include "Position.h"

class Cow {

private:
    Position pos;
    int crashTimer;
    bool animation;

    /** pour l'animation*/
    // son sens (gauche:0 , droite:1 , haut:2 , bas:3)
    int sens;
    // sa frame courante
    int frame;

public:

    /**
    * \brief Constructor
    */
    Cow();

    /**
    * \brief Constructor
    */
    Cow(int x, int y);

    /**
    * \brief move cow left
    */
    void left();

    /**
    * \brief move cow right
    */
    void right();

    /**
    * \brief move cow up
    */
    void up();

    /**
    * \brief move cow down
    */
    void down();

    /**
    * \brief addPosX
    * @param int valueX
    */
    void addPosX(int valueX);

    /**
    * \brief addPosY
    * @param int valueY
    */
    void addPosY(int valueY);

    /**
    * \brief Accessor
    * get cow position
    * @return Position
    */
    Position getPosition() const;

    /**
    * \brief Mutator
    * get cow position x
    * @param int newX
    */
    void setPositionX(int newX);

    /**
    * \brief Mutator
    * get cow position y
    * @param int newY
    */
    void setPositionY(int newY);

    /**
    * \brief Accessor
    * get cow crash timer
    * @return int
    */
    int getCrashTimer() const;

    /**
    * \brief Mutator
    * set cow crash timer
    * @param int new_CrashTimer
    */
    void setCrashTimer(int new_CrashTimer);

    /**
    * \brief Accessor
    * get cow animation
    * @return bool
    */
    bool getAnimation() const;

    /**
    * \brief Mutator
    * get cow animation
    * @param bool value
    */
    void setAnimation(bool value);

    /**
    * \brief Accessor
    * get cow direction
    * @return int
    */
    int getSens();

    /**
    * \brief Mutator
    * set cow direction
    * @param int new_sens
    */
    void setSens(int new_sens);

    /**
    * \brief Accessor
    * get frame for cow
    * @return int
    */
    int getframe();

    /**
    * \brief Mutator
    * set frame for cow
    * @param int new_frame
    */
    void setframe(int new_frame);

    /**
    * \brief Add frame
    * add frame for cow
    * @param int add
    */
    void addframe(int add);

};


#endif //PROJECT_COW_H
