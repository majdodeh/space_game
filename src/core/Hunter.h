#ifndef PROJECT_HUNTER_H
#define PROJECT_HUNTER_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Hunter class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */


#include "Position.h"

class Hunter {

private:

    Position pos;

    //détermine le sens dans lequel le chasseur avance
    int sens;

public:

    /**
    * \brief Constructor
    */
    Hunter();

    /**
    * \brief Constructor
    * @param int x and y
    */
    Hunter(int x, int y);

    /**
    * \brief Destructor
    */
    ~Hunter();

    /**
    * \brief Update Hunter
    */
    void update();

    /**
    * \brief Accessor
    * get Hunter position
    * @return Position
    */
    Position getPosition() const;

    /**
    * \brief Mutator
    * set Hunter direction
    * @return int
    */
    int getSens();

    /**
    * \brief Mutator
    * set Hunter direction
    * @param int new_sens
    */
    void setSens(int new_sens);

};

#endif //PROJECT_HUNTER_H