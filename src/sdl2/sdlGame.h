#ifndef PROJECT_SDLGAME_H
#define PROJECT_SDLGAME_H

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       Image class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

#include "../core/World.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Image{

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:

    SDL_Rect r;

    /**
    * \brief Constructor
    */
    Image() ;

    /**
    * \brief Destructor
    */
    ~Image();

    /**
    * \brief load image function
    * @param const char * fileName, SDL_Renderer * renderer
    */
    void loadImage(const char * fileName, SDL_Renderer * renderer);

    /**
    * \brief draw image on screen
    * @param SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1, SDL_Rect * portion = NULL
    */
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1, SDL_Rect * portion = NULL);

    /**
    * \brief accessor
    * @return SDL_Texture
    */
    SDL_Texture * getTexture();

    /**
    * \brief accessor
    * @return SDL_Surface
    */
    SDL_Surface * getSurface();
};

/*!
 * \author      Ali BAKIR, Majd ODEH, Rodislav IVANOV
 * \version     1.0
 * \date        17/04/2018
 * \brief       sdlGame class
 * \details     Constructeurs, destructeur et fonctions spécifiques.
 */

class sdlGame{

private:
    World world;

    SDL_Window * window;
    SDL_Renderer * renderer;

    /** The velocity of the cow */
    int cowVelX, cowVelY;

    /** font */
    TTF_Font * font;
    TTF_Font * fontMedium;
    TTF_Font * fontBig;
    SDL_Color whiteFont;

    /** Images **/
    Image background;

    Image cow;
    Image cowNormal;
    Image cowLeft;
    Image cowRight;

    Image hunter;
    Image bulletHunter;
    Image scoreIcon;
    Image ammoIcon;
    Image heartIcon;
    Image asteroid;
    Image healthBonus;
    Image bullet;
    Image topBarShadow;
    Image introImage;
    Image levelsImage;
    Image highScoreImage;
    Image scene1Image;
    Image scene1CowImage;
    Image scene1EarthImage;
    Image scene2Image;
    Image scene2PlanetImage;
    Image scene3Image;
    Image scene3PlanetImage;
    Image finalImage;
    Image finalPlanetImage;
    Image victoryBadge;

    /** Audio **/
    Mix_Chunk * sound;
    Mix_Chunk * movement;
    Mix_Chunk * ammoBonus;
    Mix_Chunk * scoreSound;
    Mix_Chunk * bgSound;
    Mix_Chunk * fireBullet;
    Mix_Chunk * cowCrash;

    Mix_Chunk * sceneOne;
    Mix_Chunk * sceneTwo;
    Mix_Chunk * sceneThree;
    Mix_Chunk * sceneFinal;
    Mix_Chunk * gameOverVoice;
    Mix_Chunk * gameOverSound;
    Mix_Chunk * gameWinSound;

    Mix_Music * gameMusic;


    /**Animation*/
    SDL_Rect clipsAsteroid[8];
    SDL_Rect clipsCow[6];

    /** Game time management **/
    int timer;

    /** Scrolling background offset **/
    int scrollingOffset;

    /** Windows management **/
    int windowId;

    /** Game End Bool **/
    bool quitGame;

public:

    /** Maximum axis velocity of the cow */
    static const int cowVel = 1;
    static const int asteroidWidth = 171;
    static const int asteroidHeight = 182;
    static const int cowWidth = 235;
    static const int cowHeight = 231;

    /** variables for animation */
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    /**
    * \brief Constructor
    */
    sdlGame();

    /**
    * \brief Destructor
    */
    ~sdlGame();

    /**Animation des sprites*/

    /**
    * \brief Set asteroid's clip
    */
    void setClipAsteroid ();

    /**
    * \brief Set cow's clip
    */
    void setClipCow ();

    /**
    * \brief function to print text on screen
    * @param const char * text, int posX, int posY, TTF_Font * fontType, SDL_Color color
    */
    void printText(const char * text, int posX, int posY, TTF_Font * fontType, SDL_Color color);

    /**
    * \brief draw game top bar
    */
    void topBar(); // game top bar (score, health...)

    /** game windows **/
    void introWindow(); // windowId is 1
    void levels(); // windowId is 2
    void highScoreWindow(); // windowId is 3
    void scene1(); // windowId is 4
    void level1(); // windowId is 5
    void scene2(); // windowId is 6
    void level2(); // windowId is 7
    void scene3(); // windowId is 8
    void level3(); // windowId is 9
    void congratulation(); // windowId is 10
    void gameOverWindow(); // windowId is 11
    void resetVariables();

    /**
    * \brief draw cow on screen
    */
    void drawCow();

    /**
    * \brief handle keyboard actions
    * @param SDL_Event& e
    */
    void handleEvent(SDL_Event& e);

    /**
    * \brief move cow position
    */
    void move();

    /**
    * \brief window handler
    * manage the switch between windows
    * @param SDL_Event e
    */
    void windowHandler(SDL_Event e);

    /**
    * \brief Game loop
    */
    void sdlLoop();

    /**
    * \brief Regression test
    */
    void testRegression();

};

#endif //PROJECT_SDLGAME_H
