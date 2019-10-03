#ifndef PROJECT_OBJECT_H
#define PROJECT_OBJECT_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Object class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

#include "Position.h"

class Object {

private:

    Position pos;
    int size;
    int speed;
    int value;

public:

    /**
    * \brief Constructoe
    */
    Object();

    /**
    * \brief Constructoe
    * @param int x, y
    */
    Object(int x, int y);

    /**
    * \brief Constructoe
    * @param int x, y, v
    */
    Object(int x, int y, int v);

    /**
    * \brief Constructoe
    * @param int x, y ,oSize, oSpeed
    */
    Object(int x, int y, int oSize, int oSpeed);

    /**
    * \brief update position down
    */
    void updatePosDown();

    /**
    * \brief update position up
    */
    void updatePosUp();

    /**
    * \brief Accessor
    * get Object position
    * @return Position
    */
    Position getPosition() const;

    /**
   * \brief Accessor
   * get Object size
   * @return int
   */
    int getSize() const;

    /**
   * \brief Mutator
   * get Object size
   * @param int sizeObject
   */
    void setSize(int sizeObject);

    /**
   * \brief Accessor
   * get Object speed
   * @return int
   */
    int getSpeed() const;

    /**
   * \brief Mutator
   * get Object speed
   * @param int speedObject
   */
    void setSpeed(int speedObject);

    /**
   * \brief Accessor
   * get Object value
   * @return int
   */
    int getValue() const;

    /**
   * \brief Mutator
   * get Object value
   * @param int valueObject
   */
    void setValue(int valueObject);
};


#endif //PROJECT_OBJECT_H
