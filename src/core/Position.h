#ifndef PROJECT_POSITION_H
#define PROJECT_POSITION_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Position class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

class Position {

    private:

        int x;
        int y;

    public:

    /**
    * \brief Constructor
    */
    Position();

    /**
    * \brief Constructor
    * @param int posX, int posY
    */
    Position(int posX, int posY);

    /**
    * \brief Accessor
    * get Position x
    * @return int
    */
    int getPosX() const;

    /**
    * \brief Accessor
    * get Position y
    * @return int
    */
    int getPosY() const;

    /**
    * \brief Mutator
    * set Position x
    * @param int posX
    */
    void setPosX(int posX);

    /**
    * \brief Mutator
    * set Position y
    * @param int posY
    */
    void setPosY(int posY);

    /**
    * \brief add value to position x
    * @param int valueX
    */
    void addPosX(int valueX);

    /**
    * \brief add value to position y
    * @param int valueY
    */
    void addPosY(int valueY);

    /**
    * \brief add one to position x
    */
    void plusOneX();

    /**
    * \brief add one to position y
    */
    void plusOneY();

    /**
    * \brief remove one to position x
    */
    void minusOneX();

    /**
    * \brief remove one to position y
    */
    void minusOneY();

};


#endif //PROJECT_POSITION_H
