#ifndef PROJECT_TXTGAME_H
#define PROJECT_TXTGAME_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       txtgame class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

#include "../core/World.h"

/**
* \brief initialize text game
* @return int
*/
int init();

/**
* \brief text game loop
* @param World & game
*/
void run(World & game);

/**
* \brief Close text game
*/
void close();

#endif //PROJECT_TXTGAME_H
