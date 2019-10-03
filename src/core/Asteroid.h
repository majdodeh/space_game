#ifndef PROJECT_ASTEROID_H
#define PROJECT_ASTEROID_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Asteroid class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

/**
* \brief Accessor
* get asteroid size
* @param int nr
* @return int
*/

#include "Position.h"

class Asteroid {

private:

    Position pos;
    int size;
    int speed;
    int shape;
    bool crashed;

    /** for animation */
    int frame;

public:

    /**
    * \brief Constructor
    * Initialise asteroid
    * @param int nr
    * @return int nb
    */
    Asteroid();

    /**
    * \brief Constructor
    * Initialise asteroid
    * @param int x, int y
    */
    Asteroid(int x, int y);

    /**
    * \brief Constructor
    * Initialise asteroid
    * @return int x, int y, int new_size
    */
    Asteroid(int x, int y, int new_size);

    /**
    * \brief Destructor
    * For asteroid
    */
    ~Asteroid();

    /**
    * \brief Update
    * Update asteroid
    */
    void update();

    /**
    * \brief Get Position
    * of the asteroid
    * @return Positon
    */
    Position getPosition() const;

    /**
    * \brief Accessor
    * get asteroid size
    * @return int
    */
    int getSize() const;

    /**
    * \brief Mutator
    * set asteroid size
    * @param int nr
    */
    void setSize(int sizeAsteroid);

    /**
    * \brief Accessor
    * get asteroid speed
    * @return int
    */
    int getSpeed() const;

    /**
    * \brief Mutator
    * set asteroid speed
    * @param int speedAsteroid
    */
    void setSpeed(int speedAsteroid);

    /**
    * \brief Mutator
    * set asteroid shape
    * @param int number
    */
    void setShape(int number);

    /**
    * \brief Accessor
    * get asteroid crash statue
    * @return bool
    */
    bool getCrashed() const;

    /**
    * \brief Mutator
    * set asteroid crash statue
    * @param bool value
    */
    void setCrashed(bool value);

    /**
    * \brief Accessor
    * get asteroid shape
    * @return int
    */
    int getShape() const;

    /**
    * \brief Accessor
    * get asteroid frame
    * @return int
    */
    int getframe();

    /**
    * \brief Mutator
    * set asteroid frame
    * @param int new_frame
    */
    void setframe(int new_frame);

    /**
    * \brief add frame
    * to asteroid
    * @param int add
    */
    void addframe(int add);

};


#endif //PROJECT_ASTEROID_H
