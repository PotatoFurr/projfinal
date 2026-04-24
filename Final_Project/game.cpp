#include <iostream>

#include "3dEngine.hpp"

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

    //here for future
    /*
    
        nplayer = new Runner(vmi::Key::A, vmi::Key::D)
    
    */
   Matrix_h T = Translation(.10f,0.0f,0.0f);

    Complex complex;
    complex.push_back(Simplex(O ,e1 , e2, vmi::Color::White));
    complex.push_back(Simplex(e1 ,e2 ,Vector3D_h(1,1,0,1) ,vmi::Color::Magenta));
    T*complex;
    complex.render(view, 100.0f);

    game.playGame();
    return 0;
}