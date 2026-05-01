#include "../Final_Project/3dEngine.hpp"
class Wall: public Complex{


    public:
    Wall(float _size, float hole):{
        
        //left side of wall

        this->push_back(Simplex(O, hole*e1, _size*e2, vmi::Color::Green));
        this->push_back(Simplex(O, _size*e2, _size*(x2), vmi::Color::Green));

        //wall above hole
        this->push_back(Simplex(_size*(Vector3D_h((xv-e),5,0,1)), _size*(Vector3D_h((xv+e),5,0,1)), _size*(x4), vmi::Color::Green));
        this->push_back(Simplex(_size*(Vector3D_h((xv-e),5,0,1)), _size*(x2), _size*(x4), vmi::Color::Green));

        //right side of wall    
        this->push_back(Simplex(_size*x3, _size*e1, _size*(e1+e2), vmi::Color::Green));
        this->push_back(Simplex(_size*x3, _size*x4, _size*(e1+e2), vmi::Color::Green));

    }

};