#include "txtgame.h"
#include <random>

int main(int argc, char **argv) {

    World game(80,24,40,20,100,100);
//    cout << rand() % game.getTerrain().getDimY() << endl;
//    cout << game.getAmmo() << endl;
    int init_status = init();

    if(init_status == 0)
        run(game);
    close();

    return 0;
}