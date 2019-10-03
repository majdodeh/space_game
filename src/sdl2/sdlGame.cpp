#include "sdlGame.h"
#include <cassert>

using namespace std;


/**Constructor*/
Image::Image(){
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

Image::~Image() {
    SDL_DestroyTexture(texture);
}

void Image::loadImage(const char * fileName, SDL_Renderer * renderer){
    surface = IMG_Load(fileName);
    if(surface == NULL){
        cerr << "Error: cannot load the image " <<fileName<<" "<<endl;
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL){
        cerr<<"Error: cannot create the texture of "<<fileName<<" "<<endl;
        exit(1);
    }

    SDL_FreeSurface(surface);
}

void Image::draw(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Rect *portion) {
    int ok;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer,texture,portion,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() {
    return texture;
}

SDL_Surface * Image::getSurface() {
    return surface;
}

/**Constructor sdl*/
sdlGame::sdlGame() : world(800,800,350,500,400,80), background(), cow(), hunter() {


    /** Initialization of the SDL **/
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cout<<"Erreur d'initialisation de la SDL"<<SDL_GetError();
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout<<"Erreur d'initialisation de la SDL"<<SDL_GetError();
    }
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;SDL_Quit();exit(1);
    }

    cout << "sdl init" << endl;

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;SDL_Quit();exit(1);
    }

    /** Creation of the window **/
    window = SDL_CreateWindow("Space Cow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, world.getTerrain().getDimX(), world.getTerrain().getDimY(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    /** Creation of the renderer **/
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    /** Initialize the velocity */
    cowVelX = 0;
    cowVelY = 0;

    /** Images **/

    background.loadImage("./data/background-stars.png", renderer);

    cow.loadImage("./data/cow.png", renderer);
    cowNormal.loadImage("./data/cow-normal.png", renderer);
    cowLeft.loadImage("./data/left_cow.png",renderer);
    cowRight.loadImage("./data/right_cow.png",renderer);
    hunter.loadImage("./data/hunter.png", renderer);
    bulletHunter.loadImage("./data/bulletHunter.png",renderer);
    asteroid.loadImage("./data/asteroid_crash.png", renderer);
    healthBonus.loadImage("./data/healthBonus.png", renderer);
    bullet.loadImage("./data/bullet.png", renderer);
    scoreIcon.loadImage("./data/scoreIcon.png", renderer);
    ammoIcon.loadImage("./data/ammoIcon.png", renderer);
    heartIcon.loadImage("./data/heart.png", renderer);
    topBarShadow.loadImage("./data/topbar-shadow.png", renderer);
    introImage.loadImage("./data/intro-window.png", renderer);
    levelsImage.loadImage("./data/levels.png", renderer);
    highScoreImage.loadImage("./data/intro-window.png", renderer);
    scene1Image.loadImage("./data/scene-1-window.png", renderer);
    scene1CowImage.loadImage("./data/cow-scene-1.png", renderer);
    scene1EarthImage.loadImage("./data/earth-pollution.png", renderer);
    scene2Image.loadImage("./data/scene-2-window.png", renderer);
    scene2PlanetImage.loadImage("./data/second-planet.png", renderer);
    scene3Image.loadImage("./data/scene-3-window.png", renderer);
    scene3PlanetImage.loadImage("./data/third-planet.png", renderer);
    finalImage.loadImage("./data/final-window.png", renderer);
    finalPlanetImage.loadImage("./data/fourth-planet.png", renderer);
    victoryBadge.loadImage("./data/badge-victory.png", renderer);


    /** Animation Sprite **/

    setClipAsteroid();
    setClipCow();

    /** Fonts **/
    font = TTF_OpenFont("./data/JosefinSans-Bold.ttf", 24); //this opens a font style and sets a size
    fontMedium = TTF_OpenFont("./data/JosefinSans-Bold.ttf", 32); //this opens a font style and sets a size
    fontBig = TTF_OpenFont("./data/JosefinSans-Bold.ttf", 42); //this opens a font style and sets a size
    whiteFont = {255, 255, 255};

    /** initialize timer and scrollingOffset **/
    timer = 0;
    scrollingOffset = 0;

    /** Sounds **/
    sound = Mix_LoadWAV("./data/sound.wav");
    bgSound = Mix_LoadWAV("./data/deep-space.wav");
    fireBullet = Mix_LoadWAV("./data/fire.wav");
    ammoBonus = Mix_LoadWAV("./data/ammoBonus.wav");
    scoreSound = Mix_LoadWAV("./data/scoreSound.wav");
    movement = Mix_LoadWAV("./data/move.wav");
    cowCrash = Mix_LoadWAV("./data/cow-crash.wav");

    sceneOne = Mix_LoadWAV("./data/scene1.wav");
    sceneTwo = Mix_LoadWAV("./data/scene2.wav");
    sceneThree = Mix_LoadWAV("./data/scene3.wav");
    sceneFinal = Mix_LoadWAV("./data/final_modified.wav");
    gameOverVoice = Mix_LoadWAV("./data/game-over-voice.wav");
    gameOverSound = Mix_LoadWAV("./data/game-over-sound.wav");
    gameWinSound = Mix_LoadWAV("./data/game-win-sound.wav");

    gameMusic = Mix_LoadMUS("./data/deep-space.wav");

    if (bgSound == NULL) {
        cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
    }

    /** windows management **/
    windowId = 1;

}

/**destructor sdl*/
sdlGame::~sdlGame () {
    Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlGame::printText(const char *  message, int posX, int posY, TTF_Font * fontType, SDL_Color color) {
    int w, h; // texture width & height

    /** create surfaces for texts **/
    SDL_Surface* surfaceText = TTF_RenderText_Blended(fontType, message, color);

    /** create textures from surfaces for text **/
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surfaceText); //now you can convert it into a texture

    /** get the width and height of texts' rectangles **/
    SDL_QueryTexture(text, NULL, NULL, &w, &h);

    /** create rectangles for score, health... **/
    SDL_Rect textRect = { posX, posY, w, h }; //create a rect

    /** free surfaces **/
    SDL_FreeSurface(surfaceText);

    /** copy texts to renderer **/
    SDL_RenderCopy(renderer, text, NULL, &textRect);

    /** destroy texture at the end **/
    SDL_DestroyTexture(text);
}


void sdlGame::topBar() {
    /** Topbar section below **/
    if( font == NULL ){ cout << "FAILED" << endl; }

    /** draw images for score, ammo... **/
    topBarShadow.draw(renderer,0,-20,800,80);
    scoreIcon.draw(renderer,102,27,30,30);
    heartIcon.draw(renderer,285,27,30,30);
    ammoIcon.draw(renderer,715,27,30,30);

    printText(("Score      " + std::to_string(world.getScore().getScore())).c_str(), 30, 30, font, whiteFont);
    printText(("Health      " + std::to_string(world.getHealth().getHealth()) + "%").c_str(), 200, 30, font, whiteFont);
    printText(("Bullets       " + std::to_string(world.getAmmo())).c_str(), 630, 30, font, whiteFont);

    /** Health bar **/
    SDL_Rect healthBar = { 385, 30, world.getHealth().getHealth()*2, 20 };
    SDL_Rect healthBarBg = { 385, 30, 200, 20 };
    SDL_SetRenderDrawColor(renderer,0x4B, 0x4B, 0x6D, 0xFF);
    SDL_RenderFillRect(renderer, &healthBarBg);
    if(world.getHealth().getHealth() > 70)
        SDL_SetRenderDrawColor(renderer,0x34,0xBF,0x49,0xFF);
    else
    if(world.getHealth().getHealth() > 30)
        SDL_SetRenderDrawColor(renderer,0xF4,0x89,0x24,0xFF);
    else
        SDL_SetRenderDrawColor(renderer,0xFF,0x4C,0x4C,0xFF);

    SDL_RenderFillRect(renderer, &healthBar);
}

void sdlGame::introWindow() {
//    timer++;
    /** clear the screen **/
    SDL_RenderClear(renderer);
    introImage.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());

    printText("Press SPACE To Start Playing", 180, 400, fontMedium, whiteFont);
    printText("Choose Level \"L\"", 280, 480, fontMedium, whiteFont);
    printText("High Score \"H\"", 300, 560, fontMedium, whiteFont);
    printText("Press \"Q\" to Exit", 320, 720, font, whiteFont);

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::highScoreWindow() {
    /** clear the screen **/
    SDL_RenderClear(renderer);
    introImage.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());
    printText(("High Score " + std::to_string(world.getHighScore().getScore())).c_str(), 260, 400, fontBig, whiteFont);
    printText(R"(Press "R" to Return | "Q" to Exit)", 220, 720, font, whiteFont);

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::levels() {
    /** clear the screen **/
    SDL_RenderClear(renderer);
    levelsImage.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());

    printText("Choose a Level", 320, 360, font, whiteFont);
    printText("Level 1 Easy (Press E)", 240, 405, fontMedium, whiteFont);
    printText("Level 2 Medium (Press M)", 240, 500, fontMedium, whiteFont);
    printText("Level 3 Hard (Press H)", 240, 610, fontMedium, whiteFont);
    printText(R"(Press "R" to Return | "Q" to Exit)", 220, 720, font, whiteFont);

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::scene1() {
    timer++;
    /** clear the screen **/
    SDL_RenderClear(renderer);
    scene1Image.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());

    if(timer % 3 == 0 && timer < 600) x1--;
    if(timer % 80 == 0 && timer < 9000) y2++;
    if(timer % 150 == 0 && timer < 9000) x2++;
    if(timer % 2 == 0 && timer > 8600) y1-= 2;

    scene1EarthImage.draw(renderer,-50+x2,50+y2,400,400);
    scene1CowImage.draw(renderer,600+x1,300+y1,341,220);

    printText("Level 1", 40, 40, font, whiteFont);

    if(timer < 1500) printText("Hello everyone! Would you like to hear my story?", 100, 620, font, whiteFont);
    if(timer > 1500 && timer < 3000){ printText("It is about a cow which was forced to quit its home.", 100, 620, font, whiteFont);};
    if(timer > 3000 && timer < 4900){ printText("Why? Simply because of the spreading pollution on our planet.", 40, 620, font, whiteFont);};
    if(timer > 4900 && timer < 6600){ printText("People do not care about the Earth", 200, 570, font, whiteFont);};
    if(timer > 4900 && timer < 6600){ printText("and so they throw garbage everywhere.", 190, 620, font, whiteFont);};
    if(timer > 6600 && timer < 8400){ printText("I better run away and find another planet where I could live!", 40, 620, font, whiteFont);};
    if(timer > 8400){ printText("Lets go for it! Meeeeowwww!!!!", 250, 620, font, whiteFont);};

    printText(R"(Press "S" to Skip)", 300, 720, font, whiteFont);

//    if(timer > 10500){ resetVariables(); world.resetGameSdl(350,500,0,100); Mix_ResumeMusic(); windowId = 5; }

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::level1() {
    /** timer to control the game **/
    timer++;


    /** add score + sound for each 100 points of score **/
    if (timer % 400 == 0 && timer < 10000) {
        world.getScore().addScore(1);
        if (world.getScore().getScore() % 100 == 0)
            Mix_PlayChannel(-1, scoreSound, 0);
    }

    /** clear the screen **/
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    /** display the moving background **/
    if (timer % 5 == 0){ scrollingOffset++; }
    if(scrollingOffset > world.getTerrain().getDimY()){ scrollingOffset = 0; }
    background.draw(renderer,0,scrollingOffset,world.getTerrain().getDimX(),world.getTerrain().getDimY());
    background.draw(renderer,0,scrollingOffset-world.getTerrain().getDimY(),world.getTerrain().getDimX(),world.getTerrain().getDimY());

    if(timer < 1000){
        scene1EarthImage.draw(renderer,200,500+(timer/2),400,400);
    }

    /** cow gravity force **/
    if (timer % 6 == 0 && world.getCow().getPosition().getPosY() < world.getTerrain().getDimY() -100 ){
        world.moveCow('s');
    }

    /** draw planet at the end **/
    if(timer > 10000){
        if(((timer-10350) / 3) < 575){
            scene2PlanetImage.draw(renderer,150,((timer-10350) / 3) - 350,500,350);
            printText("Well done! You finished the first level :)", 180, ((timer-10350) / 3) + 20, font, whiteFont);
        }else{
            scene2PlanetImage.draw(renderer,150,225,500,350);
            printText("Well done! You finished the first level :)", 180, 597, font, whiteFont);
        }
    }

    /** draw bullets **/
    for(const auto & bulletObj : world.getBullets()){
        bullet.draw(renderer, bulletObj.getPosition().getPosX(), bulletObj.getPosition().getPosY(), 30, 30);
    }

    /** draw Bullet Hunter**/
    for(const auto & bulletObj : world.getBulletsHunter()){
        bulletHunter.draw(renderer, bulletObj.getPosition().getPosX(), bulletObj.getPosition().getPosY(), 30, 30);
    }

    /** draw asteroids **/

    for(size_t id = 0; id < world.getAsteroids().size(); id++) {
        asteroid.draw(renderer, world.getAsteroids().at(id).getPosition().getPosX(), world.getAsteroids().at(id).getPosition().getPosY(), 80, 80, &clipsAsteroid[world.getAsteroids().at(id).getframe()]);
    }

    /** draw ammoBonus **/
    for(const auto & ammoBonusObj : world.getAmmoBonus()){
        ammoIcon.draw(renderer, ammoBonusObj.getPosition().getPosX(), ammoBonusObj.getPosition().getPosY(), 30, 30);
    }

    /** draw healthBonus **/
    for(const auto & healthBonusObj : world.getHealthBonus()){
        healthBonus.draw(renderer, healthBonusObj.getPosition().getPosX(), healthBonusObj.getPosition().getPosY(), 50, 50);
    }

    /** draw cow **/
    sdlGame::drawCow();

    /** update asteroids **/
    if(timer % 500 == 0 && timer < 10000){
        world.addAsteroidsSdl();
    }


    /** destroy asteroid when crash with the cow **/
    for(size_t id = 0; id < world.getAsteroids().size(); id++) {
        if (world.verifyAsteroidCowCrashSdl(id)) {
            if(!world.getAsteroids().at(id).getCrashed()) {
                world.getCow().setCrashTimer(60);
                world.getHealth().removeHealth(20);
                world.asteroidCrashed(id);
                Mix_PlayChannel(-1,cowCrash,0);
            }
        }
    }

    /** update the recoil of the Cow if crash*/
    if (world.getCow().getCrashTimer()!=0) {
        if (world.getCow().getPosition().getPosY() < world.getTerrain().getDimY()-100) {
            world.getCow().addPosY(1);
            world.getCow().setCrashTimer(world.getCow().getCrashTimer() - 1);
        }
        if (world.getCow().getPosition().getPosY() >= world.getTerrain().getDimY()-100) {
            world.getCow().setCrashTimer(0);
        }
    }

    /** update Asteroids every 2 loops **/
    if(timer % 2 == 0){
        world.updateAsteroidsSdl();
    }

    /** update bullets every 5 loops **/
    if(!world.getBullets().empty())
        world.updateBulletsSdl();

    if(!world.getBulletsHunter().empty()){
        world.updateBulletsHunterSdl();
    }

    /** update ammoBonus **/
    if (timer > 100 && timer % 3 == 0){
        world.updateAmmoBonusSdl();
    }
    if (timer > 100 && timer % 2000 == 0 && timer < 10000){
        world.addAmmoBonusSdl();
    }

    /** update healthBonus **/
    if (timer > 100 && timer % 3 == 0){
        world.updateHealthBonus();
    }
    if (timer > 100 && timer % 2200 == 0 && timer < 10000){
        world.addHealthBonus();
    }

    /** increase ammo when obtaining an ammoBonus **/
    for(size_t i = 0; i < world.getAmmoBonus().size(); i++) {
        if(world.verifyAmmoBonusCowSdl(i)) {
            Mix_PlayChannel(-1,ammoBonus,0);
            world.increaseAmmo(world.getAmmoBonusTxt().at(i).getValue());
            world.removeAmmoBonus(i);
        }
    }

    /** increase health when obtaining an healthBonus **/
    for(size_t i = 0; i < world.getHealthBonus().size(); i++) {
        if(world.verifyHealthBonusCow(i)) {
            Mix_PlayChannel(-1,ammoBonus,0);
            world.getHealth().addHealth(10);
            world.removeHealthBonus(i);
        }
    }

    /** verify crash between bullets and asteroids **/
    for(size_t i = 0; i < world.getAsteroids().size(); i++) {
        for(size_t y = 0; y < world.getBullets().size(); y++) {
            if(world.verifyBulletAsteroidSdl(y,i) && !world.getAsteroids().at(i).getCrashed()){
                Mix_PlayChannel(-1,ammoBonus,0);
                world.getScore().addScore(5);
                world.asteroidCrashed(i);
                world.removeBullet(y);
            }
        }
    }

    /** animation until the asteroid is destroied */
    for(size_t i = 0; i < world.getAsteroids().size(); i++) {
        if(world.getAsteroids().at(i).getCrashed() && timer % 50 ==0) {
            world.AnimationAsteroid(i);
            if (world.getAsteroids().at(i).getframe() == 7) {
                world.removeAsteroidSdl(i);
            }
        }
    }

    /** draw top bar **/
    topBar();

    printText("Level 1", 40, 740, font, whiteFont);

    if(timer == 2){
        printText("3", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    if(timer == 3){
        printText("2", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    if(timer == 4){
        printText("1", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }


    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);

    /** Game Conditions | game over or win**/
    if(world.getHealth().getHealth() == 0) {
        if(world.getHighScore().getScore() < world.getScore().getScore()){
            int newScore = world.getScore().getScore();
            world.getHighScore().setScore(newScore);
        }

        cout << "+=============================+" << endl;
        cout << "====== +++ GAME OVER +++ ======" << endl;
        cout << "+=============================+" << endl;
        cout << " The score is: " << world.getScore().getScore() << endl;
        Mix_PauseMusic();
        Mix_PlayChannel(-1,gameOverVoice,0);
        Mix_PlayChannel(-1,gameOverSound,0);
        windowId = 11;
    }

    if(world.getHealth().getHealth() != 0 && timer > 14000) {
        if(world.getHighScore().getScore() < world.getScore().getScore()){
            int newScore = world.getScore().getScore();
            world.getHighScore().setScore(newScore);
        }
        Mix_PauseMusic();
        Mix_PlayChannel(-1,gameWinSound,0);
        Mix_PlayChannel(-1,sceneTwo,0);
        resetVariables();
        windowId = 6;
    }

    if(timer%400==0){
        cout << "==============================" << endl;
        cout << "On ~ ("<< timer/400 << ") seconds we have: "<<world.getAsteroids().size() << " asteroids" << endl;
        cout << " SpaceCow is on X:" << world.getCow().getPosition().getPosX() << " and Y: " << world.getCow().getPosition().getPosY() << endl;
        cout << "  The actual score is:" << world.getScore().getScore() << endl;
        cout << "    The health is: "<< world.getHealth().getHealth() << endl;
    }
}

void sdlGame::scene2() {
    timer++;
    /** clear the screen **/
    SDL_RenderClear(renderer);
    scene2Image.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());


    if(timer % 3 == 0 && timer < 600) x1--;
    if(timer % 2 == 0 && timer > 8600) y1-= 2;
    if(timer == 1){ x2 = 341; y2 = 220; };
    if(timer % 30 == 0 && timer > 1000 && timer < 5000){ y2--; };
    if(timer % 20 == 0 && timer > 1000 && timer < 5000){ x2--; };

    /** update asteroids **/
    if(timer % 500 == 0 && timer < 10000 && timer > 2000){
        world.addAsteroidsSdl();
    }

    /** update Asteroids every 1 loop **/
    if(timer % 4 == 0){
        world.updateAsteroidsSdl();
    }

    /** draw asteroids **/
    for(size_t id = 0; id < world.getAsteroids().size(); id++) {
        asteroid.draw(renderer, world.getAsteroids().at(id).getPosition().getPosX(), world.getAsteroids().at(id).getPosition().getPosY(), 80, 80, &clipsAsteroid[world.getAsteroids().at(id).getframe()]);
    }

    scene2PlanetImage.draw(renderer,150,225,500,350);
    scene1CowImage.draw(renderer,600+x1,300+y1,x2,y2);

    printText("Level 2", 40, 40, font, whiteFont);

    if(timer < 2000) printText("The Cow managed to reach the planet X", 170, 620, font, whiteFont);
    if(timer > 2000 && timer < 3500){ printText("but it was permanently attacked by asteroids", 140, 620, font, whiteFont);};
    if(timer > 3500 && timer < 5200){ printText("That is why she decided to not", 220, 570, font, whiteFont);};
    if(timer > 3500 && timer < 5200){ printText("sacrifice her comfort and to fly away.", 190, 620, font, whiteFont);};
    if(timer > 5200 && timer < 7000){ printText("Too much asteroids, I am done here,", 200, 570, font, whiteFont);};
    if(timer > 5200 && timer < 7000){ printText("I will search for another planet", 210, 620, font, whiteFont);};
    if(timer > 7000){ printText("Meeeeowwww!!!!", 320, 620, font, whiteFont);};

    printText(R"(Press "S" to Skip)", 300, 720, font, whiteFont);

//    if(timer > 10000){ resetVariables(); world.resetGameSdl(350,500,0,100); Mix_ResumeMusic(); windowId = 7; }

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::level2() {
    /** timer to control the game **/
    timer++;

    /** add score + sound for each 100 points of score **/
    if (timer % 400 == 0 && timer < 10000) {
        world.getScore().addScore(1);
        if (world.getScore().getScore() % 100 == 0)
            Mix_PlayChannel(-1, scoreSound, 0);
    }

    /** clear the screen **/
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    /** display the moving background **/
    if (timer % 4 == 0){ scrollingOffset++; }
    if(scrollingOffset > world.getTerrain().getDimY()){ scrollingOffset = 0; }
    background.draw(renderer,0,scrollingOffset,world.getTerrain().getDimX(),world.getTerrain().getDimY());
    background.draw(renderer,0,scrollingOffset-world.getTerrain().getDimY(),world.getTerrain().getDimX(),world.getTerrain().getDimY());

    if(timer < 1000){
        scene2PlanetImage.draw(renderer,150,500+(timer/2),500,350);
    }

    /** cow gravity force **/
    if (timer % 6 == 0 && world.getCow().getPosition().getPosY() < world.getTerrain().getDimY() -100 ){
        world.moveCow('s');
    }

    /** draw planet at the end **/
    if(timer > 10400){
        if(((timer-10400) / 3) < 600){
            scene3PlanetImage.draw(renderer,150,((timer-10400) / 3) - 400,500,400);
            printText("Well done! You finished the second level :)", 180, ((timer-10400) / 3) + 20, font, whiteFont);
        }else{
            scene3PlanetImage.draw(renderer,150,200,500,400);
            printText("Well done! You finished the second level :)", 180, 622, font, whiteFont);
        }
    }

    /** draw bullets **/
    for(const auto & bulletObj : world.getBullets()){
        bullet.draw(renderer, bulletObj.getPosition().getPosX(), bulletObj.getPosition().getPosY(), 30, 30);
    }

    /** draw Bullet Hunter**/
    for(const auto & bulletObj : world.getBulletsHunter()){
        bulletHunter.draw(renderer, bulletObj.getPosition().getPosX(), bulletObj.getPosition().getPosY(), 30, 30);
    }

    /** draw asteroids **/

    for(size_t id = 0; id < world.getAsteroids().size(); id++) {
        asteroid.draw(renderer, world.getAsteroids().at(id).getPosition().getPosX(), world.getAsteroids().at(id).getPosition().getPosY(), 80, 80, &clipsAsteroid[world.getAsteroids().at(id).getframe()]);
    }

    /** draw ammoBonus **/
    for(const auto & ammoBonusObj : world.getAmmoBonus()){
        ammoIcon.draw(renderer, ammoBonusObj.getPosition().getPosX(), ammoBonusObj.getPosition().getPosY(), 30, 30);
    }

    /** draw healthBonus **/
    for(const auto & healthBonusObj : world.getHealthBonus()){
        healthBonus.draw(renderer, healthBonusObj.getPosition().getPosX(), healthBonusObj.getPosition().getPosY(), 50, 50);
    }

    /** draw cow **/
    sdlGame::drawCow();

    /** update asteroids **/
    if(timer % 200 == 0 && timer < 10000){
        world.addAsteroidsSdl();
    }


    /** destroy asteroid when crash with the cow **/
    for(size_t id = 0; id < world.getAsteroids().size(); id++) {
        if (world.verifyAsteroidCowCrashSdl(id)) {
            if(!world.getAsteroids().at(id).getCrashed()) {
                world.getCow().setCrashTimer(60);
                world.getHealth().removeHealth(20);
                world.asteroidCrashed(id);
                Mix_PlayChannel(-1,cowCrash,0);
            }
        }
    }

    /** update the recoil of the Cow if crash*/
    if (world.getCow().getCrashTimer()!=0) {
        if (world.getCow().getPosition().getPosY() < world.getTerrain().getDimY()-100) {
            world.getCow().addPosY(1);
            world.getCow().setCrashTimer(world.getCow().getCrashTimer() - 1);
        }
        if (world.getCow().getPosition().getPosY() >= world.getTerrain().getDimY()-100) {
            world.getCow().setCrashTimer(0);
        }
    }

    /** update Asteroids every 1 loop **/
    if(timer % 1 == 0){
        world.updateAsteroidsSdl();
    }

    /** update bullets every 5 loops **/
    if(!world.getBullets().empty())
        world.updateBulletsSdl();

    if(!world.getBulletsHunter().empty()){
        world.updateBulletsHunterSdl();
    }

    /** update ammoBonus **/
    if (timer > 100 && timer % 3 == 0){
        world.updateAmmoBonusSdl();
    }
    if (timer > 100 && timer % 2000 == 0 && timer < 10000){
        world.addAmmoBonusSdl();
    }

    /** update healthBonus **/
    if (timer > 100 && timer % 3 == 0){
        world.updateHealthBonus();
    }
    if (timer > 100 && timer % 2200 == 0 && timer < 10000){
        world.addHealthBonus();
    }

    /** increase ammo when obtaining an ammoBonus **/
    for(size_t i = 0; i < world.getAmmoBonus().size(); i++) {
        if(world.verifyAmmoBonusCowSdl(i)) {
            Mix_PlayChannel(-1,ammoBonus,0);
            world.increaseAmmo(world.getAmmoBonusTxt().at(i).getValue());
            world.removeAmmoBonus(i);
        }
    }

    /** increase health when obtaining an healthBonus **/
    for(size_t i = 0; i < world.getHealthBonus().size(); i++) {
        if(world.verifyHealthBonusCow(i)) {
            Mix_PlayChannel(-1,ammoBonus,0);
            world.getHealth().addHealth(10);
            world.removeHealthBonus(i);
        }
    }

    /** verify crash between bullets and asteroids **/
    for(size_t i = 0; i < world.getAsteroids().size(); i++) {
        for(size_t y = 0; y < world.getBullets().size(); y++) {
            if(world.verifyBulletAsteroidSdl(y,i) && !world.getAsteroids().at(i).getCrashed()){
                Mix_PlayChannel(-1,ammoBonus,0);
                world.getScore().addScore(5);
                world.asteroidCrashed(i);
                world.removeBullet(y);
            }
        }
    }

    /** animation until the asteroid is destroied */
    for(size_t i = 0; i < world.getAsteroids().size(); i++) {
        if(world.getAsteroids().at(i).getCrashed() && timer % 50 ==0) {
            world.AnimationAsteroid(i);
            if (world.getAsteroids().at(i).getframe() == 7) {
                world.removeAsteroidSdl(i);
            }
        }
    }

    /** draw top bar **/
    topBar();

    printText("Level 2", 40, 740, font, whiteFont);

    if(timer == 2){
        printText("3", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    if(timer == 3){
        printText("2", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    if(timer == 4){
        printText("1", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);

    /** Game Conditions | game over or win**/
    if(world.getHealth().getHealth() == 0) {
        if(world.getHighScore().getScore() < world.getScore().getScore()){
            int newScore = world.getScore().getScore();
            world.getHighScore().setScore(newScore);
        }

        cout << "+=============================+" << endl;
        cout << "====== +++ GAME OVER +++ ======" << endl;
        cout << "+=============================+" << endl;
        cout << " The score is: " << world.getScore().getScore() << endl;
        Mix_PauseMusic();
        Mix_PlayChannel(-1,gameOverVoice,0);
        Mix_PlayChannel(-1,gameOverSound,0);
        windowId = 11;
    }

    if(world.getHealth().getHealth() != 0 && timer > 14000) {
        if(world.getHighScore().getScore() < world.getScore().getScore()){
            int newScore = world.getScore().getScore();
            world.getHighScore().setScore(newScore);
        }
        Mix_PauseMusic();
        Mix_PlayChannel(-1,gameWinSound,0);
        Mix_PlayChannel(-1,sceneThree,0);
        resetVariables();
        windowId = 8;
    }
    if(timer%400==0){
        cout << "==============================" << endl;
        cout << "On ~ ("<< timer/400 << ") seconds we have: "<<world.getAsteroids().size() << " asteroids" << endl;
        cout << " SpaceCow is on X:" << world.getCow().getPosition().getPosX() << " and Y: " << world.getCow().getPosition().getPosY() << endl;
        cout << "  The actual score is:" << world.getScore().getScore() << endl;
        cout << "    The health is: "<< world.getHealth().getHealth() << endl;
    }
}

void sdlGame::scene3() {
    timer++;
    /** clear the screen **/
    SDL_RenderClear(renderer);
    scene3Image.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());

    if(timer % 3 == 0 && timer < 600) x1--;
    if(timer % 2 == 0 && timer > 8600) y1-= 2;
    if(timer == 1){ x2 = 341; y2 = 220; };
    if(timer % 30 == 0 && timer > 1000 && timer < 5000){ y2--; };
    if(timer % 20 == 0 && timer > 1000 && timer < 5000){ x2--; };

    scene3PlanetImage.draw(renderer,150,200,500,400);
    scene1CowImage.draw(renderer,600+x1,300+y1,x2,y2);
    hunter.draw(renderer,100-(x1/2),100+(y1/2),200,135);

    printText("Level 3", 40, 40, font, whiteFont);

    if(timer < 1800) printText("When Space Cow arrived on X planet", 170, 620, font, whiteFont);
    if(timer > 1800 && timer < 4500){ printText("she realized that she was not alone", 210, 570, font, whiteFont);};
    if(timer > 1800 && timer < 4500){ printText("and there was a hunter living on it.", 210, 620, font, whiteFont);};
    if(timer > 4500 && timer < 6800){ printText("Hooooooo, a  Space Cow!", 230, 570, font, whiteFont);};
    if(timer > 4500 && timer < 6800){ printText("Come here, come here good girl!", 210, 620, font, whiteFont);};
    if(timer > 6800){ printText("Daaaamn! Leave me alone, man! Meeeeeooooooow", 100, 620, font, whiteFont);};


//    if(timer > 10000){ resetVariables(); world.resetGameSdl(350,500,0,100); Mix_ResumeMusic(); windowId = 9; }
    printText(R"(Press "S" to Skip)", 320, 720, font, whiteFont);

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::level3() {

    /** timer to control the game **/
    timer++;

    /** add score + sound for each 100 points of score **/
    if (timer % 400 == 0 && timer < 14000) {
        world.getScore().addScore(1);
        if (world.getScore().getScore() % 100 == 0)
            Mix_PlayChannel(-1, scoreSound, 0);
    }

    /** clear the screen **/
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    /** display the moving background **/
    if (timer % 5 == 0){ scrollingOffset++; }
    if(scrollingOffset > world.getTerrain().getDimY()){ scrollingOffset = 0; }
    background.draw(renderer,0,scrollingOffset,world.getTerrain().getDimX(),world.getTerrain().getDimY());
    background.draw(renderer,0,scrollingOffset-world.getTerrain().getDimY(),world.getTerrain().getDimX(),world.getTerrain().getDimY());

    if(timer < 1000){
        scene3PlanetImage.draw(renderer,150,500+(timer/2),500,400);
    }

    /** cow gravity force **/
    if (timer % 6 == 0 && world.getCow().getPosition().getPosY() < world.getTerrain().getDimY() -100 ){
        world.moveCow('s');
    }

    /** draw planet at the end **/
    if(timer > 14000){
        if(((timer-14400) / 3) < 600){
            finalPlanetImage.draw(renderer,150,((timer-14400) / 3) - 400,500,400);
            printText("Well done! You finished the third level :)", 180, ((timer-14400) / 3) + 20, font, whiteFont);
        }else{
            finalPlanetImage.draw(renderer,150,200,500,400);
            printText("Well done! You finished the third level :)", 180, 620, font, whiteFont);
        }
    }

    /** draw bullets **/
    for(const auto & bulletObj : world.getBullets()){
        bullet.draw(renderer, bulletObj.getPosition().getPosX(), bulletObj.getPosition().getPosY(), 30, 30);
    }


    /** draw Bullet Hunter**/
    for(const auto & bulletObj : world.getBulletsHunter()){
        bulletHunter.draw(renderer, bulletObj.getPosition().getPosX(), bulletObj.getPosition().getPosY(), 30, 30);
    }

    /** draw asteroids **/

    for(size_t id = 0; id < world.getAsteroids().size(); id++) {
        asteroid.draw(renderer, world.getAsteroids().at(id).getPosition().getPosX(), world.getAsteroids().at(id).getPosition().getPosY(), 80, 80, &clipsAsteroid[world.getAsteroids().at(id).getframe()]);
    }

    /** draw ammoBonus **/
    for(const auto & ammoBonusObj : world.getAmmoBonus()){
        ammoIcon.draw(renderer, ammoBonusObj.getPosition().getPosX(), ammoBonusObj.getPosition().getPosY(), 30, 30);
    }

    /** draw healthBonus **/
    for(const auto & healthBonusObj : world.getHealthBonus()){
        healthBonus.draw(renderer, healthBonusObj.getPosition().getPosX(), healthBonusObj.getPosition().getPosY(), 50, 50);
    }


    /** draw cow **/
    sdlGame::drawCow();

    /** draw Hunter **/
    if(timer > 14000){
        if(((timer-14400) / 3) < 450)
            hunter.draw(renderer,world.gethunter().getPosition().getPosX(),world.gethunter().getPosition().getPosY()-(((timer-14000) / 3)),100,70);
    }else{
        hunter.draw(renderer,world.gethunter().getPosition().getPosX(),world.gethunter().getPosition().getPosY(),100,70);
    }

    /** update asteroids **/
    if(timer % 300 == 0 && timer < 14000){
        world.addAsteroidsSdl();
    }


    /** destroy asteroid when crash with the cow **/
    for(size_t id = 0; id < world.getAsteroids().size(); id++) {
        if (world.verifyAsteroidCowCrashSdl(id)) {
            if(!world.getAsteroids().at(id).getCrashed()) {
                world.getCow().setCrashTimer(60);
                world.getHealth().removeHealth(20);
                world.asteroidCrashed(id);
                Mix_PlayChannel(-1,cowCrash,0);
            }
        }
    }

    /** update the recoil of the Cow if crash*/
    if (world.getCow().getCrashTimer()!=0) {
        if (world.getCow().getPosition().getPosY() < world.getTerrain().getDimY()-100) {
            world.getCow().addPosY(1);
            world.getCow().setCrashTimer(world.getCow().getCrashTimer() - 1);
        }
        if (world.getCow().getPosition().getPosY() >= world.getTerrain().getDimY()-100) {
            world.getCow().setCrashTimer(0);
        }
    }

    /** update Asteroids every 2 loops **/
    if(timer % 2 == 0){
        world.updateAsteroidsSdl();
    }

    /** update hunter and his bullets **/
    if(timer % 4 ==0) {
        world.updateHunterSdl();
    }

    if(timer % 400 == 0 && timer < 14000) {
        world.fireBulletHunterSdl();
        Mix_PlayChannel(-1,fireBullet,0);
    }

    /** update bullets **/
    if(!world.getBullets().empty())
        world.updateBulletsSdl();

    if(!world.getBulletsHunter().empty()){
        world.updateBulletsHunterSdl();
    }

    /** update ammoBonus **/
    if (timer > 100 && timer % 3 == 0){
        world.updateAmmoBonusSdl();
    }
    if (timer > 100 && timer % 2000 == 0 && timer < 14000){
        world.addAmmoBonusSdl();
    }

    /** update healthBonus **/
    if (timer > 100 && timer % 3 == 0){
        world.updateHealthBonus();
    }
    if (timer > 100 && timer % 2500 == 0 && timer < 14000){
        world.addHealthBonus();
    }

    /** increase ammo when obtaining an ammoBonus **/
    for(size_t i = 0; i < world.getAmmoBonus().size(); i++) {
        if(world.verifyAmmoBonusCowSdl(i)) {
            Mix_PlayChannel(-1,ammoBonus,0);
            world.increaseAmmo(world.getAmmoBonusTxt().at(i).getValue());
            world.removeAmmoBonus(i);
        }
    }

    /** increase health when obtaining an healthBonus **/
    for(size_t i = 0; i < world.getHealthBonus().size(); i++) {
        if(world.verifyHealthBonusCow(i)) {
            Mix_PlayChannel(-1,ammoBonus,0);
            world.getHealth().addHealth(10);
            world.removeHealthBonus(i);
        }
    }

    /** verify crash between bullets and asteroids **/
    for(size_t i = 0; i < world.getAsteroids().size(); i++) {
        for(size_t y = 0; y < world.getBullets().size(); y++) {
            if(world.verifyBulletAsteroidSdl(y,i) && !world.getAsteroids().at(i).getCrashed()){
                Mix_PlayChannel(-1,ammoBonus,0);
                world.getScore().addScore(5);
                world.asteroidCrashed(i);
                world.removeBullet(y);
            }
        }
    }

    /** verify crash between bullet of the Hunter and Cow**/
    for(size_t i = 0; i < world.getBulletsHunter().size(); i++) {
        if(world.verifyBulletCowHunterSdl(i)) {
            Mix_PlayChannel(-1,cowCrash,0);
            world.removeBulletHunter(i);
            world.getCow().setCrashTimer(60);
            world.getHealth().removeHealth(10);
        }
    }

    /** animation until the asteroid is destroied */
    for(size_t i = 0; i < world.getAsteroids().size(); i++) {
        if(world.getAsteroids().at(i).getCrashed() && timer % 50 ==0) {
            world.AnimationAsteroid(i);
            if (world.getAsteroids().at(i).getframe() == 7) {
                world.removeAsteroidSdl(i);
            }
        }
    }

    /** draw top bar **/
    topBar();

    printText("Level 3", 40, 740, font, whiteFont);

    if(timer == 2){
        printText("3", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    if(timer == 3){
        printText("2", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    if(timer == 4){
        printText("1", 390, 390, fontBig, whiteFont);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);

    /** Game Conditions | game over or win**/

    if(world.getHealth().getHealth() == 0) {
        if(world.getHighScore().getScore() < world.getScore().getScore()){
            int newScore = world.getScore().getScore();
            world.getHighScore().setScore(newScore);
        }

        cout << "+=============================+" << endl;
        cout << "====== +++ GAME OVER +++ ======" << endl;
        cout << "+=============================+" << endl;
        cout << " The score is: " << world.getScore().getScore() << endl;
        Mix_PauseMusic();
        Mix_PlayChannel(-1,gameOverVoice,0);
        Mix_PlayChannel(-1,gameOverSound,0);
        windowId = 11;
    }

    if(world.getHealth().getHealth() != 0 && timer > 18000) {
        if(world.getHighScore().getScore() < world.getScore().getScore()){
            int newScore = world.getScore().getScore();
            world.getHighScore().setScore(newScore);
        }
        Mix_PauseMusic();
        Mix_PlayChannel(-1,gameWinSound,0);
        Mix_PlayChannel(-1,sceneFinal,0);
        resetVariables();
        windowId = 10;
    }

    if(timer%400==0){
        cout << "==============================" << endl;
        cout << "On ~ ("<< timer/400 << ") seconds we have: "<<world.getAsteroids().size() << " asteroids" << endl;
        cout << " SpaceCow is on X:" << world.getCow().getPosition().getPosX() << " and Y: " << world.getCow().getPosition().getPosY() << endl;
        cout << "  The actual score is:" << world.getScore().getScore() << endl;
        cout << "    The health is: "<< world.getHealth().getHealth() << endl;
    }
}

void sdlGame::congratulation() {
    timer++;
    /** clear the screen **/
    SDL_RenderClear(renderer);
    finalImage.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());
    finalPlanetImage.draw(renderer,150,250,500,400);

    if(timer < 1000){
        victoryBadge.draw(renderer,400-timer/10,10,timer/5,timer/5);
    }else{
        victoryBadge.draw(renderer,300,10,200,200);
    }

    if(timer == 1){ x2 = 341; y2 = 220; };
    if(timer % 3 == 0 && timer < 600) x1--;
    if(timer % 40 == 0 && timer > 9000) y1-= 1;
    if(timer % 30 == 0 && timer > 1000 && timer < 6000){ y2--; };
    if(timer % 20 == 0 && timer > 1000 && timer < 6000){ x2--; };

    scene1CowImage.draw(renderer,600+x1,300+y1,x2,y2);

    printText("Congratulations, You Won :)", 195, 200, fontMedium, whiteFont);
    printText(("Your Score   " + std::to_string(world.getScore().getScore())).c_str(), 330, 260, font, whiteFont);
    printText("The End", 40, 40, font, whiteFont);

    if(timer < 2000) printText("In the end, our Space Cow landed on planet X", 150, 620, font, whiteFont);
    if(timer > 2000 && timer < 4500){ printText("wide valleys, green grass and fresh air everywhere.", 100, 620, font, whiteFont);};
    if(timer > 4500 && timer < 5700){ printText("Yeah Baby! I succeeded it!", 250, 620, font, whiteFont);};
    if(timer > 5700 && timer < 7500){ printText("This planet looks awesome", 240, 570, font, whiteFont);};
    if(timer > 5700 && timer < 7500){ printText("and it is full of other Space Cows!", 200, 620, font, whiteFont);};
    if(timer > 7500 && timer < 9000){ printText("I am staying here! Meeeeeoooowwww", 180, 620, font, whiteFont);};
    if(timer > 9000){ printText("Thank you for following this story.", 200, 570, font, whiteFont);};
    if(timer > 9000){ printText("We hope you learned an important lesson from it!", 120, 620, font, whiteFont);};


//    if(timer > 14000){ resetVariables(); world.resetGameSdl(350,500,0,100); Mix_ResumeMusic(); windowId = 1; }

    printText(R"(Press "R" to Return | "Q" to Exit)", 220, 720, font, whiteFont);

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::gameOverWindow() {
    /** clear the screen **/
    SDL_SetRenderDrawColor(renderer, 134, 111, 232, 255);
    SDL_RenderClear(renderer);

    introImage.draw(renderer,0,0,world.getTerrain().getDimX(),world.getTerrain().getDimX());
    printText("Game Over", 280, 400, fontBig, whiteFont);
    printText(("Your Score  " + std::to_string(world.getScore().getScore())).c_str(), 300, 500, fontMedium, whiteFont);
    printText(R"(Press "R" to Return | "Q" to Exit)", 220, 720, font, whiteFont);

    /** show renderer in the screen **/
    SDL_RenderPresent(renderer);
}

void sdlGame::resetVariables() {
    x1 = y1 = x2 = y2 = timer = 0;
    world.getCow().setAnimation(false);
    cowVelX = cowVelY = 0;
}

void sdlGame::drawCow() {

    /** draw cow **/
    if(world.getCow().getAnimation()) {
        if (world.getCow().getSens() == 0) {
            cowLeft.draw(renderer, world.getCow().getPosition().getPosX(), world.getCow().getPosition().getPosY(), 100, 100, &clipsCow[world.getCow().getframe()]);
        }
        if (world.getCow().getSens() == 1) {
            cowRight.draw(renderer, world.getCow().getPosition().getPosX(), world.getCow().getPosition().getPosY(), 100, 100, &clipsCow[world.getCow().getframe()]);
        }
        if (world.getCow().getSens() == 2) {
            cow.draw(renderer, world.getCow().getPosition().getPosX(), world.getCow().getPosition().getPosY(), 100, 100);
        }
        if (world.getCow().getSens() == 3) {
            cow.draw(renderer, world.getCow().getPosition().getPosX(), world.getCow().getPosition().getPosY(), 100, 100);
        }
        if ((world.getCow().getframe() != 5) && ((world.getCow().getSens() == 0) || (world.getCow().getSens() == 1))){
            world.getCow().addframe(1);
        }
    } else {
        cowNormal.draw(renderer, world.getCow().getPosition().getPosX(), world.getCow().getPosition().getPosY(), 100, 100);
        world.getCow().setframe(0);
    }
}

void sdlGame::setClipAsteroid () {

    clipsAsteroid[0].x = 0;
    clipsAsteroid[0].y = 0;
    clipsAsteroid[0].w = asteroidWidth;
    clipsAsteroid[0].h = asteroidHeight;

    clipsAsteroid[1].x = asteroidWidth;
    clipsAsteroid[1].y = 0;
    clipsAsteroid[1].w = asteroidWidth;
    clipsAsteroid[1].h = asteroidHeight;

    clipsAsteroid[2].x = asteroidWidth*2;
    clipsAsteroid[2].y = 0;
    clipsAsteroid[2].w = asteroidWidth;
    clipsAsteroid[2].h = asteroidHeight;

    clipsAsteroid[3].x = 0;
    clipsAsteroid[3].y = asteroidHeight;
    clipsAsteroid[3].w = asteroidWidth;
    clipsAsteroid[3].h = asteroidHeight;

    clipsAsteroid[4].x = asteroidWidth;
    clipsAsteroid[4].y = asteroidHeight;
    clipsAsteroid[4].w = asteroidWidth;
    clipsAsteroid[4].h = asteroidHeight;

    clipsAsteroid[5].x = asteroidWidth*2;
    clipsAsteroid[5].y = asteroidHeight;
    clipsAsteroid[5].w = asteroidWidth;
    clipsAsteroid[5].h = asteroidHeight;

    clipsAsteroid[6].x = 0;
    clipsAsteroid[6].y = asteroidHeight*2;
    clipsAsteroid[6].w = asteroidWidth;
    clipsAsteroid[6].h = asteroidHeight;

    clipsAsteroid[7].x = asteroidWidth;
    clipsAsteroid[7].y = asteroidHeight*2;
    clipsAsteroid[7].w = asteroidWidth;
    clipsAsteroid[7].h = asteroidHeight;
}

void sdlGame::setClipCow () {

    clipsCow[0].x = 0;
    clipsCow[0].y = 0;
    clipsCow[0].w = cowWidth;
    clipsCow[0].h = cowHeight;

    clipsCow[1].x = cowWidth;
    clipsCow[1].y = 0;
    clipsCow[1].w = cowWidth;
    clipsCow[1].h = cowHeight;

    clipsCow[2].x = cowWidth*3;
    clipsCow[2].y = 0;
    clipsCow[2].w = cowWidth;
    clipsCow[2].h = cowHeight;

    clipsCow[3].x = 0;
    clipsCow[3].y = cowHeight;
    clipsCow[3].w = cowWidth;
    clipsCow[3].h = cowHeight;

    clipsCow[4].x = cowWidth;
    clipsCow[4].y = cowHeight;
    clipsCow[4].w = cowWidth;
    clipsCow[4].h = cowHeight;

    clipsCow[5].x = cowWidth*2;
    clipsCow[5].y = cowHeight;
    clipsCow[5].w = cowWidth;
    clipsCow[5].h = cowHeight;

}

void sdlGame::handleEvent(SDL_Event &e) {

    /** If a key was pressed */
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        /** Adjust the velocity **/
        switch( e.key.keysym.sym ) {
            case SDLK_UP: cowVelY -= cowVel; Mix_PlayChannel(-1,movement,0); world.getCow().setAnimation(true); world.getCow().setSens(2); break;
            case SDLK_DOWN: cowVelY += cowVel; Mix_PlayChannel(-1,movement,0); world.getCow().setAnimation(true); world.getCow().setSens(3); break;
            case SDLK_LEFT: cowVelX -= cowVel; Mix_PlayChannel(-1,movement,0); world.getCow().setAnimation(true); world.getCow().setSens(0); break;
            case SDLK_RIGHT: cowVelX += cowVel; Mix_PlayChannel(-1,movement,0); world.getCow().setAnimation(true); world.getCow().setSens(1); break;
            case SDLK_SPACE:
                if (world.getAmmo() > 0) {
                    Mix_Volume(1,MIX_MAX_VOLUME);
                    Mix_PlayChannel(-1,fireBullet,0);
                    world.fireBulletSdl();
                    world.updateAmmo();
                }
                break;
            default:break;
        }
    }
        //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: cowVelY += cowVel; world.getCow().setAnimation(false); break;
            case SDLK_DOWN: cowVelY -= cowVel; world.getCow().setAnimation(false); break;
            case SDLK_LEFT: cowVelX += cowVel; world.getCow().setAnimation(false); break;
            case SDLK_RIGHT: cowVelX -= cowVel; world.getCow().setAnimation(false); break;
        }
    }
}

void sdlGame::move() {

    //Move the cow left or right
    world.addCowPosX(cowVelX);


    //If the cow went too far to the left or right
    if((world.getCow().getPosition().getPosX() < 0 ) || ( world.getCow().getPosition().getPosX() + 100 > world.getTerrain().getDimX())){
        //Move back
        world.addCowPosX(-cowVelX);
    }

    //Move the cow up or down
    world.addCowPosY(cowVelY);

    //If the cow went too far up or down
    if((world.getCow().getPosition().getPosY() < 100) || (world.getCow().getPosition().getPosY() + 100 > world.getTerrain().getDimY()))
    {
        //Move back
        world.addCowPosY(-cowVelY);
    }
}

/** function to manage the switch between the windows **/
void sdlGame::windowHandler(SDL_Event e) {
    /** intro window **/
    if(windowId == 1){
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){ quitGame = true; }
            if(e.key.keysym.sym == SDLK_2 || e.key.keysym.sym == SDLK_l){ windowId = 2; }
            if(e.key.keysym.sym == SDLK_3 || e.key.keysym.sym == SDLK_h){ windowId = 3; }
            if(e.key.keysym.sym == SDLK_4 || e.key.keysym.sym == SDLK_SPACE){ resetVariables(); Mix_PauseMusic(); Mix_PlayChannel(-1,sceneOne,0); windowId = 4; }
            if(e.key.keysym.sym == SDLK_5){ resetVariables(); world.resetGameSdl(350,500,0,100); windowId = 5; }
            if(e.key.keysym.sym == SDLK_6){ resetVariables(); Mix_PauseMusic(); Mix_PlayChannel(-1,sceneTwo,0); windowId = 6; }
            if(e.key.keysym.sym == SDLK_7){ resetVariables(); world.resetGameSdl(350,500,0,100); windowId = 7; }
            if(e.key.keysym.sym == SDLK_8){ resetVariables(); Mix_PauseMusic(); Mix_PlayChannel(-1,sceneThree,0); windowId = 8; }
            if(e.key.keysym.sym == SDLK_9){ resetVariables(); world.resetGameSdl(350,500,0,100); windowId = 9; }
            if(e.key.keysym.sym == SDLK_i){ resetVariables(); Mix_PauseMusic(); Mix_PlayChannel(-1,sceneFinal,0); windowId = 10; }
            if(e.key.keysym.sym == SDLK_o){ resetVariables(); Mix_PauseMusic(); Mix_PlayChannel(-1,gameOverVoice,0); Mix_PlayChannel(-1,gameOverSound,0); windowId = 11; }
        }
    }
    /** Levels window **/
    if(windowId == 2){
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_r){
                windowId = 1;
            }
            if(e.key.keysym.sym == SDLK_e){
                resetVariables();
                Mix_PauseMusic();
                Mix_PlayChannel(-1,sceneOne,0);
                windowId = 4;
            }
            if(e.key.keysym.sym == SDLK_m){
                resetVariables();
                Mix_PauseMusic();
                Mix_PlayChannel(-1,sceneTwo,0);
                windowId = 6;
            }
            if(e.key.keysym.sym == SDLK_h){
                resetVariables();
                Mix_PauseMusic();
                Mix_PlayChannel(-1,sceneThree,0);
                windowId = 8;
            }
        }
    }
    /** High score window **/
    if(windowId == 3){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_r){
                windowId = 1;
            }
        }
    }
    /** Scene 1 window **/
    if(windowId == 4){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_r){
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 1;
            }
            if(e.key.keysym.sym == SDLK_s){
                // reinitialize game
                resetVariables();
                world.resetGameSdl(350,500,0,100);
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 5;
            }
        }
    }
    /** Level 1 window **/
    if(windowId == 5){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1){
                windowId = 1;
            }
            handleEvent(e);
        }
    }
    /** Scene 2 window **/
    if(windowId == 6){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_r){
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 1;
            }
            if(e.key.keysym.sym == SDLK_s){
                // reinitialize game
                resetVariables();
                world.resetGameSdl(350,500,0,100);
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 7;
            }
        }
    }
    /** Level 2 window **/
    if(windowId == 7){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1){
                windowId = 1;
            }
            handleEvent(e);
        }
    }
    /** Scene 3 window **/
    if(windowId == 8){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_r){
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 1;
            }
            if(e.key.keysym.sym == SDLK_s){
                // reinitialize game
                resetVariables();
                world.resetGameSdl(350,500,0,100);
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 9;
            }
        }
    }
    /** Level 3 window **/
    if(windowId == 9){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1){
                windowId = 1;
            }
            handleEvent(e);
        }
    }
    /** congratulation window **/
    if(windowId == 10){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_r){
                resetVariables();
                world.resetGameSdl(350,500,0,100);
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 1;
            }
        }
    }
    /** game over window **/
    if(windowId == 11){
        while(SDL_PollEvent(&e) != 0 ){
            //User requests quit
            if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT){
                quitGame = true;
            }
            if(e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_r){
                Mix_HaltChannel(-1);
                Mix_ResumeMusic();
                windowId = 1;
            }
        }
    }

}

void sdlGame::sdlLoop() {

    /** game background music **/
//    Mix_PlayChannel(-1,bgSound,0);
    Mix_PlayMusic(gameMusic,-1);
//    cout << "test shape " << rand()%2 << endl;

    // main loop
    while (!quitGame) {

        /** Event handler **/
        SDL_Event e;

        /** function to manage switching between windows **/
        windowHandler(e);

        switch (windowId){
            case 1 :
                introWindow();
                break;
            case 2 :
                levels();
                break;
            case 3 :
                highScoreWindow();
                break;
            case 4 :
                scene1();
                break;
            case 5 :
                level1();
                if(timer % 2 == 0)
                    move();
                break;
            case 6 :
                scene2();
                break;
            case 7 :
                level2();
                if(timer % 2 == 0)
                    move();
                break;
            case 8 :
                scene3();
                break;
            case 9 :
                level3();
                if(timer % 2 == 0)
                    move();
                break;
            case 10 :
                congratulation();
                break;
            case 11 :
                gameOverWindow();
                break;
            default:
                break;
        }
    }
}


/** REGRESSION TEST **/
void sdlGame::testRegression(){

    //Initialization of a Testimage
    Image * ImForTest = NULL;
    assert(ImForTest == NULL);
    ImForTest = new Image();
    assert(ImForTest->getTexture()==NULL && ImForTest->getSurface()==NULL);

    delete ImForTest;
    ImForTest=NULL;
    assert(ImForTest==NULL);



    cout<<"Does the program can load an image? ";
    ImForTest = new Image();
    ImForTest->loadImage("./data/cow.png", renderer);
    assert(ImForTest->getTexture()!=NULL && ImForTest->getSurface()!=NULL);
    ImForTest->draw (renderer, 250, 250, 100, 100);
    cout<<"[ Yes, it does ]"<<endl;

    cout<<"Can the program get a texture of a file? ";
    if(ImForTest->getTexture() == NULL){
    cout<<" [ No, it can't! ;( ]"<<endl;
    }else{cout<<"[ Yes, it can] "<<endl;}

    SDL_Rect rectangle={0,0,40,50};
    assert(rectangle.x==0 && rectangle.y==0 && rectangle.w==40 && rectangle.h==50);

    cout <<"Is SpaceCow on the right place/mesurements?";
    int x=world.getCow().getPosition().getPosX();
    int y=world.getCow().getPosition().getPosY();
    assert(x>0 && x< world.getTerrain().getDimX() && y>0 && y< world.getTerrain().getDimY());
    cout<<" [Yes, it is]"<<endl;

    cout <<"Is the Health full?";
    assert(world.getHealth().getHealth() == 100);
    cout <<" [Yes,it is]"<<endl;

    cout <<"Does the Score start at zero? ";
    assert(world.getScore().getScore()==0);
    cout <<" [Yes, it does]"<<endl;

    cout <<"Does the Ammo start with 20? ";
    assert(world.getAmmo() == 20);
    cout <<" [Yes, it does]"<<endl;


    vector<Asteroid> tabA;
    Asteroid first(1,1);
    Asteroid second(2,2);

//    vector<Object>   tabO;
    int size= static_cast<int>(tabA.size());
    cout<<"Size of Asteroids at the beggining : "<<size<<endl;
    //world.addAsteroidsSdl();
    tabA.push_back(first);
    size= static_cast<int>(tabA.size());
    cout<<"Size of Asteroids after push back : "<<size<<endl;

    if(timer%100==0){

        cout<<"On("<< timer/100 << ") seconds we have: "<<world.getAsteroids().size()<<" asteroids"<<endl;
        cout<<" SpaceCow is on X:"<<world.getCow().getPosition().getPosX()<<" and Y: "<<world.getCow().getPosition().getPosY()<<endl;
        cout<<"  The actual score is:"<<world.getScore().getScore()<<endl;
        cout<<"    The health is: "<<world.getHealth().getHealth()<<endl;
    }
    tabA.clear();
}
