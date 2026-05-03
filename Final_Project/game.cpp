#include <iostream>

#include "3dEngine.hpp"


using namespace engine;
View* view = new View(800, 800, 90.0f);


Player * const Player::self = new Player(0.0f,0.0f,110.0f);
int main(){
    // Complex* bottom = new Cube(5, vmi::Color::Cyan);
    // bottom->position = Vector3D_h(0,0,10,0);
    Wall::spawn();
    view->moveView(Vector3D_h(0,0,0,1));
    Complex::renderAll(view);
    Game game = Game(800,800, view);
    game.playGame();
    return 0;
}