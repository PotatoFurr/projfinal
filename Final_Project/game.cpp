#include <iostream>

#include "3dEngine.hpp"

Game game = Game(800,800);
View view = View(800, 800);

int main(){
    view.updateProjection();

    //here for future
    /*
    
        nplayer = new Runner(vmi::Key::A, vmi::Key::D)
    
    */

    Simplex simplex = Simplex(
        O,
        e1,
        e2,
        vmi::Color::White
    );
    simplex.render(view, 100.0f);

    game.playGame();

    return 0;
}