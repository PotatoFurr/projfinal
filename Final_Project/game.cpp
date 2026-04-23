#include <iostream>

#include "3dEngine.hpp"

Game game = Game(800,800);
View view = View(800, 800);

int main(){
    view.updateProjection();

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