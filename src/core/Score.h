#ifndef PROJECT_SCORE_H
#define PROJECT_SCORE_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Score class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

class Score {
private:

    int score;

public:

    /**
    * \brief Constructor
    */
    Score();

    /**
    * \brief Accessor
    * get Score
    */
    int getScore() const;

    /**
    * \brief Mutator
    * set Score
    * @param int newScore
    */
    void setScore(int newScore);

    /**
    * \brief Accessor
    * add Score
    * @param int points
    */
    void addScore(int points);
};


#endif //PROJECT_SCORE_H
