#include <iostream>

#include "3dEngine.hpp"
#include "runner.hpp"
#include "LANE.h"

Game game = Game(800,800);
View view = View(800, 800);

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

int main(){
    view.updateProjection();

     Runner(Key::A, Key::D);
    
   Matrix_h T = Translation(1.00f,0.0f,0.0f);
   Matrix_h Ry = Rotation_y(M_PI/8);
   Matrix_h Rx = Rotation_x(M_PI/8);
   Matrix_h Rz = Rotation_z(M_PI/8);

    Complex complex = Cube();
    Rx*complex;
    Ry*complex;
    Rz*complex;
    complex.render(view, 100.0f);
    
    game.setComplex(&complex);
    game.playGame();
    return 0;
}