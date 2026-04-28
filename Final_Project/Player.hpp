#pragma once 

#include "3dEngine.hpp"
#include "Keyboard.hpp"
namespace engine{
using namespace engine;
class Player: public Complex{
    private:
    vmi::Key R = vmi::Key::A;
    vmi::Key L = vmi::Key::B;

    public:
    Player() : Cube(100){
        Matrix_h T = Translation(0.0f,0.0f,20.0f);
        this->operator*(T);
    }

    void move(float dt){
        if(Game::isKeyPressed(R)){
            Matrix_h T = Translation(dt/5, 0.0f, 0.0f);
            this->operator*(T);
        }
        if(Game::isKeyPressed(L)){
            Matrix_h T = Translation(-dt/5, 0.0f, 0.0f);
            this->operator*(T);

        }

    }


};

}//namespace engine