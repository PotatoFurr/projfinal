#pragma once
#include "VertexSets.hpp"
#include "Vector3d.hpp"
#include <vector>
#include "Vector2d.hpp"


namespace Krec{

    class Object3d{
        protected:
        Complex* obj;
        Vector3d<float> position;

        public:
        Object3d():obj(new Complex()),position(Vector3d<float>()){
        //intentionly left blank
        }
        Object3d(Complex* complex):obj(complex),position(Vector3d<float>()){
        //intentionly left blank
        }
        Object3d(Complex* complex, Vector3d<float> _position):obj(complex),position(_position){
        //intentionly left blank
        }
        Object3d(Object3d& oldObj):obj(oldObj.obj),position(oldObj.position){
        //intentionly left blank
        }
        ~Object3d(){
            delete obj;
        }

        
    };

 




}//namespace krec