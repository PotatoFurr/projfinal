#pragma once
#include "3dEngine.hpp"
#include "lane.hpp"
#include "LANE.h"

using namespace Krec;

class Obstacle : public Complex
{
    public:
        Obstacle() : Cube(100) //for now will be a cube
        {



        };

        ~Obstacle()
        {

            delete Complex;

        };    

        void MoveObj()
        {
            Matrix_h T = Translation(0.0f, 0.0f, dt*5);
            this->operator*(T);
            
        };
        
        void handleCollision(const Thing* other)
        {
            if (typeid(*other) == typeid(Wall))
                {
                die();
                }

        };

    private:

    bool onscreen;

};