#include <iostream>

#include "3dEngine.hpp"


using namespace engine;
View view = View(800, 800, 100.0f);

// void inline DebugProj(Simplex simplex){
//     Matrix_h T = Translation(10.0f,0.0f,0.0f);
//     Matrix_h P = Projection(1.0f,100.0f,0.0f);

//     std::cout << "Translation: " << std::endl << T ;
//     std::cout << "Projection: " << std::endl << P ;
//     std::cout << "Simplex: " << simplex << std::endl;
//     simplex = T*simplex;
//     std::cout << "Translated: " << simplex << std::endl;
//     simplex = P*simplex;
//     std::cout << "Projected: " <<simplex << std::endl;

// }

Player * const Player::self = new Player();
int main(){
    view.updateProjection();
    
   Matrix_h T = Translation(-80.0f,80.0f,40.0f);
   Matrix_h Ry = Rotation_y(M_PI/8);
   Matrix_h Rx = Rotation_x(M_PI/8);
//    Matrix_h Rz = Rotation_z(M_PI/8);


//    Player::self->operator*(Rx);
//    Player::self->operator*(Ry);
   Player::self->operator*(T);

    Complex::renderAll(view);
    Game game = Game(800,800, view);
    game.playGame();
    return 0;
}