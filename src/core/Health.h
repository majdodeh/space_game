#ifndef PROJECT_HEALTH_H
#define PROJECT_HEALTH_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Health class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

class Health {

private:

    int health;

public:

    /**
    * \brief Constructor for Health
    */
    Health();

    /**
    * \brief Accessor
    * get Health
    * @return int
    */
    int getHealth() const;

    /**
    * \brief Mutator
    * set Health
    * @param int newHealth
    */
    void setHealth(int newHealth);

    /**
    * \brief add health points
    * add health points
    * @param int points
    */
    void addHealth(int points);

    /**
    * \brief remove health points
    * remove from Health
    * @param int points
    */
    void removeHealth(int points);

    /**
    * \brief Accessor
    * verify Health
    * @return bool
    */
    bool verifyDead() const ;

};


#endif //PROJECT_HEALTH_H
