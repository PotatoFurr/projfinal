#include <iostream>

#include "3dEngine.hpp"
#include "runner.hpp"
#include "LANE.h"

Game game = Game(800,800);
View view = View(800, 800);

int main(){
    view.updateProjection();

     Runner(Key::A, Key::D);
    

    Simplex simplex = Simplex(
        O,
        e1,
        e2,
        vmi::Color::Magenta
    );
    Matrix_h T = Translation(.01f,0.0f,0.0f);
    simplex = T*simplex;
    simplex.render(view, 100.0f);

    game.playGame();

    return 0;
}