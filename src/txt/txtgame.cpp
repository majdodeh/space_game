#include "txtgame.h"
#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif // WIN32mak
#include <unistd.h>
#include <unistd.h>
#include <ctime>

WINDOW* gameWindow;

int init() {

    /******************/
    /** Start Window **/
    /******************/

    /** initialize random number generator **/
    srand(static_cast<unsigned int>(time(nullptr)));

    /** initialize window **/
    gameWindow = initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    /** clear(), refresh() **/
    keypad(gameWindow, true);

    /** nodelay causes getch to be a non-blocking call **/
    nodelay(gameWindow, true);

    /** make cursor invisible **/
    curs_set(0);

    /** verify if the terminal support colors **/
    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support colors.\n");
        exit(1);
    }


    /** this function enables using colors **/
    start_color();

    /** draw border **/
    attron(A_BOLD);
    box(gameWindow, 0, 0);
    attroff(A_BOLD);

    /** initialization for color pairs **/
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    wbkgd(gameWindow, COLOR_PAIR(3));

    /** START SCREEN LOOP **/

    while(1) {
        int in_char = wgetch(gameWindow);

        wattron(gameWindow, COLOR_PAIR(5));
        mvprintw(4,14," ___________  ___  _____ _____   _____ _____ _    _ ");
        mvprintw(5,14,"/  ___| ___ \\/ _ \\/  __ |  ___| /  __ |  _  | |  | |");
        mvprintw(6,14,"\\ `--.| |_/ / /_\\ | /  \\| |__   | /  \\| | | | |  | |");
        mvprintw(7,14," `--. |  __/|  _  | |   |  __|  | |   | | | | |/\\| |");
        mvprintw(8,14,"/\\__/ | |   | | | | \\__/| |___  | \\__/\\ \\_/ \\  /\\  /");
        mvprintw(9,14,"\\____/\\_|   \\_| |_/\\____\\____/   \\____/\\___/ \\/  \\/ ");

        wattron(gameWindow, COLOR_PAIR(4));
        mvprintw(12,37,"LIFAP4");
        wattron(gameWindow, COLOR_PAIR(1));
        mvprintw(15,25,"PRESS SPACE TO START PLAYING");


        mvprintw(20,7,"Ali BAKIR 11607221 | Majd ODEH 11608951 | Rodislav IVANOV 11511441");


        if(in_char == ' '){
            break;
        }

        wrefresh(gameWindow);

        usleep(10000); // 1 ms
    }

    werase(gameWindow);

    return 0;
}


void run(World & game) {

    /*****************/
    /** Game Window **/
    /*****************/

    /** game time counter **/
    int timer = 0;

    /** game speed, bigger number mean slower game **/
    int gameSpeed = 20;

    /** game level **/
    int level = 1;

    /** cow character **/
    char cow = 'O';

    /** draw cow initiale position **/
    mvaddch(game.getCow().getPosition().getPosY(), game.getCow().getPosition().getPosX(), cow);

    /** capture pressed key **/
    int in_char;

    //    Asteroid test(rand() % game.getTerrain().getDimX(),3);

    //    bool endGameRequested = false;
    bool gameOver = false;


    wrefresh(gameWindow);

    while(1) {

        in_char = wgetch(gameWindow);

        /*  erase cow characters */
        mvaddch(game.getCow().getPosition().getPosY(), game.getCow().getPosition().getPosX(), ' ');
        mvaddch(game.getCow().getPosition().getPosY() + 1, game.getCow().getPosition().getPosX(), ' ');
        mvaddch(game.getCow().getPosition().getPosY() + 1, game.getCow().getPosition().getPosX() + 1, ' ');
        mvaddch(game.getCow().getPosition().getPosY() + 1, game.getCow().getPosition().getPosX() - 1, ' ');


        for (const auto &astroid : game.getAsteroidsTxt()) {
            mvaddch(astroid.getPosition().getPosY(), astroid.getPosition().getPosX(), ' ');
        }

        for (const auto &ammoBonus : game.getAmmoBonusTxt()) {
            mvaddch(ammoBonus.getPosition().getPosY(), ammoBonus.getPosition().getPosX(), ' ');
        }

        for (const auto &bullet : game.getBulletsTxt()) {
            mvaddch(bullet.getPosition().getPosY(), bullet.getPosition().getPosX(), ' ');
        }

//        mvaddch(test.getPosition().getPosY(), test.getPosition().getPosX(), ' ');

        switch (in_char) {
            case 'q':
//                endGameRequested = true;
                game.setGameStatus(true);
                break;
            case KEY_UP:
            case 'w':
                if (game.getCow().getPosition().getPosY() > 2)
                    game.moveCow('w');
                break;
            case KEY_DOWN:
            case 's':
                if (game.getCow().getPosition().getPosY() < game.getTerrain().getDimY() - 3)
                    game.moveCow('s');
                break;
            case KEY_LEFT:
            case 'a':
                if (game.getCow().getPosition().getPosX() > 2)
                    game.moveCow('a');
                break;
            case KEY_RIGHT:
            case 'd':
                if (game.getCow().getPosition().getPosX() < game.getTerrain().getDimX() - 3)
                    game.moveCow('d');
                break;
            case ' ':
                if (game.getAmmo() > 0) {
                    game.fireBullet();
                    game.updateAmmo();
                    werase(gameWindow);
                }
                break;
            default:
                break;
        }

        /** draw cow characters **/
//        mvaddch(test.getPosition().getPosY(), test.getPosition().getPosX(), '#');
        wattron(gameWindow, A_BOLD);
        wattron(gameWindow, COLOR_PAIR(5));
        mvaddch(game.getCow().getPosition().getPosY(), game.getCow().getPosition().getPosX(), cow);
        wattron(gameWindow, COLOR_PAIR(1));
        mvaddch(game.getCow().getPosition().getPosY()+1, game.getCow().getPosition().getPosX(), '|');
        mvaddch(game.getCow().getPosition().getPosY()+1, game.getCow().getPosition().getPosX()+1, '>');
        mvaddch(game.getCow().getPosition().getPosY()+1, game.getCow().getPosition().getPosX()-1, '<');
        wattroff(gameWindow, COLOR_PAIR(1));
        wattroff(gameWindow, A_BOLD);

        /** remove asteroid if there is a crash with Cow **/
        for(size_t i = 0; i < game.getAsteroidsTxt().size(); i++) {
            if(game.verifyCrashTxt(i)) {
                game.removeAsteroidTxt(i);
                game.getHealth().removeHealth(20);
                werase(gameWindow);
            }
        }

        /** remove asteroid and bullet if there is a crash **/
        for(size_t i = 0; i < game.getAsteroidsTxt().size(); i++) {
            for(size_t y = 0; y < game.getBulletsTxt().size(); y++) {
                if(game.verifyBulletAsteroid(y,i)){
//                    game.removeAsteroidTxt(i);
                    game.asteroidCrashed(i);
                    game.removeBullet(y);
                }
            }
        }

        for(size_t i = 0; i < game.getAsteroids().size(); i++) {
            if(game.getAsteroids().at(i).getCrashed()) {
                game.removeAsteroidSdl(i);
            }
        }

        /** increase ammo when obtaining an ammoBonus **/
        for(size_t i = 0; i < game.getAmmoBonusTxt().size(); i++) {
            if(game.verifyAmmoBonusCow(i)) {
                game.increaseAmmo(game.getAmmoBonusTxt().at(i).getValue());
                game.removeAmmoBonus(i);
                werase(gameWindow);
            }
        }

        /** update asteroids every 15 loops **/
        if (timer > 100 && timer % gameSpeed == 0){
            game.updateAsteroidsTxt();
        }

        /** update game speed **/
        if(gameSpeed > 5){
            if(timer > 100 && timer % 800 == 0){
                gameSpeed--;
            }
        }

        /** update ammoBonus **/
        if (timer > 100 && timer % 40 == 0){
            game.updateAmmoBonusTxt();
        }
        if (timer > 100 && timer % 150 == 0){
            game.addAmmoBonusTxt();
        }

        /** update bullets every 5 loops **/
        if (timer % 5 == 0){
            if(!game.getBulletsTxt().empty())
                game.updateBullets();
        }

        /** update score every 20 loops **/
        if(timer % 20 == 0){
//            test.update();
            game.getScore().addScore(1);
        }

        /** update level **/
        if(gameSpeed <= 15){
            if(gameSpeed > 10){
                level = 2;
            }else{
                level = 3;
            }
        }

        /** print asteroids **/
        for(auto & asteroid : game.getAsteroidsTxt()){
            wattron(gameWindow, A_BOLD);
            wattron(gameWindow, COLOR_PAIR(2));
            mvwaddch(gameWindow, asteroid.getPosition().getPosY(), asteroid.getPosition().getPosX(), '*');
            wattroff(gameWindow, COLOR_PAIR(2));
            wattroff(gameWindow, A_BOLD);
        }

        /** print ammoBonus **/
        for(auto & ammoBonus : game.getAmmoBonusTxt()){
            wattron(gameWindow, A_BOLD);
            wattron(gameWindow, COLOR_PAIR(6));
            mvprintw(ammoBonus.getPosition().getPosY(), ammoBonus.getPosition().getPosX(), "%d", ammoBonus.getValue());
            wattroff(gameWindow, COLOR_PAIR(6));
            wattroff(gameWindow, A_BOLD);
        }

        /** print bullets **/
        for(auto & bullet : game.getBulletsTxt()){
            wattron(gameWindow, A_BOLD);
            wattron(gameWindow, COLOR_PAIR(3));
            mvwaddch(gameWindow, bullet.getPosition().getPosY(), bullet.getPosition().getPosX(), '^');
            wattroff(gameWindow, COLOR_PAIR(2));
            wattroff(gameWindow, A_BOLD);
        }

        /** print score **/
        wattron(gameWindow, A_BOLD);
        mvprintw(1,2,"SCORE");
        mvprintw(1,8,"%d", game.getScore().getScore());

//        wrefresh(gameWindow);

        /** print Health **/
        mvprintw(1,13,"HEALTH");
        mvprintw(1,20,"%d", game.getHealth().getHealth());

        /** print Level **/
        switch (level){
            case 1:
                wattron(gameWindow, COLOR_PAIR(5));
                mvprintw(1,26,"LEVEL 1");
                wattroff(gameWindow, COLOR_PAIR(5));
                break;
            case 2:
                wattron(gameWindow, COLOR_PAIR(4));
                mvprintw(1,26,"LEVEL 2");
                wattroff(gameWindow, COLOR_PAIR(4));
                break;
            case 3:
                wattron(gameWindow, COLOR_PAIR(6));
                mvprintw(1,26,"LEVEL 3");
                wattroff(gameWindow, COLOR_PAIR(6));
                break;
            default:
                break;
        }


        /** print Ammo **/
        mvprintw(1,63,"BULLETS");
        mvprintw(1,72,"%d", game.getAmmo());
        wattroff(gameWindow, A_BOLD);

        /** frame around screen **/
        wattron(gameWindow, A_BOLD);
        box(gameWindow, 0, 0);
        wattroff(gameWindow, A_BOLD);

        refresh();
//        werase(gameWindow);

        /** check player if dead **/
        if(game.getHealth().getHealth() <= 0)
            gameOver = true;


        if(gameOver){

            if(game.getHighScore().getScore() < game.getScore().getScore()){
                int newScore = game.getScore().getScore();
                game.getHighScore().setScore(newScore);
            }

            // store an approx location where text will be centered
            const int xPos = game.getTerrain().getDimX() / 2 - 6;
            const int yPos = game.getTerrain().getDimY() / 2 - 2;


            werase(gameWindow);
            wattron(gameWindow, A_BOLD);
            box(gameWindow, 0, 0);
            wattroff(gameWindow, A_BOLD);


            /** print on screen **/
            wattron(gameWindow, A_BOLD);
            wattron(gameWindow, COLOR_PAIR(1));
            mvwprintw(gameWindow, 3, xPos - 6, "YOUR HIGH SCORE IS");
            wattron(gameWindow, COLOR_PAIR(6));
            mvwprintw(gameWindow, 3, xPos + 13,"%d", game.getHighScore().getScore());
            wattron(gameWindow, COLOR_PAIR(5));
            mvprintw(5,8,"   _____          __  __ ______    ______      ________ _____  ");
            mvprintw(6,8,"  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ");
            mvprintw(7,8," | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
            mvprintw(8,8," | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ");
            mvprintw(9,8," | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ");
            mvprintw(10,8,"  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
            wattron(gameWindow, COLOR_PAIR(1));
            mvwprintw(gameWindow, yPos + 3, xPos - 3, "YOUR SCORE IS");
            wattron(gameWindow, COLOR_PAIR(4));
            mvwprintw(gameWindow, yPos + 3, xPos + 11,"%d", game.getScore().getScore());
            wattron(gameWindow, COLOR_PAIR(2));
            mvwprintw(gameWindow, yPos + 5, xPos , "GAME OVER");
            wattron(gameWindow, COLOR_PAIR(1));
            mvwprintw(gameWindow, yPos + 7, xPos - 7, "Press SPACE to play again");
            mvwprintw(gameWindow, yPos + 9, xPos - 7, "Press 'q' to quit the game");
            wattroff(gameWindow, A_BOLD);

            wrefresh(gameWindow);

            /** loop until player either quits or restarts game **/
            while(1) {

                in_char = wgetch(gameWindow);

                /** reset all variables and restart game **/
                if(in_char == ' ') {
                    timer = 0;
                    game.resetGameTxt(40, 20, 0, 100);
                    //                player.pos = {10, 10};
                    //                player.energy = 100;
                    //                stars.getData().clear();
                    //                asteroids.getData().clear();
                    in_char = 0;
                    //                game_over = false;
                    gameOver = false;
                    gameSpeed = 20;
                    level = 1;
                    werase(gameWindow);
                    break;
                }

                else if(in_char == 'q') {
//                    endGameRequested = true;
                    game.setGameStatus(true);
                    break;
                }

                wrefresh(gameWindow);

                timer++;
                usleep(10000); // 1 ms
            }
        }
        if(game.getGameStatus()) break;

        timer++;

        usleep(10000); // 10 ms
    }

}


void close() {
    endwin();
}