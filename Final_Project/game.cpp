#include <iostream>
#include "VMIGameInterface.hpp"
#include <VertexSets.hpp>
#include <Vector3d.hpp>
#include <Movement.hpp>
#include <Thing.hpp>




using namespace iml;
iml::Screen* screen = new iml::Screen(800, 800);

// Translation T = Translation((5*e3));
// Projection P = Projection(1.0,10.0);
// Simplex simplex = Simplex(0,e1,e1+e2);
// std::cout << "Translation Matrix:" << T << "Projection Matrix:" << P 
// << "Simplex:" << simplex<< std::endl 
// << "Translation:" << T*simplex << std::endl 
// << "Projection" << P*(T*simplex);
// simplex = T*simplex;

int main(){
    Game game;
    Krec::Translation T = Krec::Translation(.5*e2+.3e1);
    Cube cube = Cube();
    cube.render(screen, 100.0f);

    game.playGame();


    return 0;
}