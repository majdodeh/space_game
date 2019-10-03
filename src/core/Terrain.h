#ifndef PROJECT_TERRAIN_H
#define PROJECT_TERRAIN_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Terrain class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

class Terrain {

private:
    int dimX;
    int dimY;

public:

    /**
    * \brief Constructor
    */
    Terrain();

    /**
    * \brief Constructor
    * @param int width, int height
    */
    Terrain(int width, int height);

    /**
    * \brief Accessor
    * get Terrain dim x
    * @return int
    */
    int getDimX() const;

    /**
    * \brief Mutator
    * set Terrain dim x
    * @param int newDimX
    */
    void setDimX(int newDimX);

    /**
    * \brief Accessor
    * get Terrain dim y
    * @return int
    */
    int getDimY() const;

    /**
    * \brief Mutator
    * set Terrain dim Y
    * @param int newDimY
    */
    void setDimY(int newDimY);

};


#endif //PROJECT_TERRAIN_H
