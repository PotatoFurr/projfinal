#pragma once
#include <iostream>
#include <cmath>

#include "Vector3d.hpp"
#include "VertexSets.hpp"


//HR: https://www.youtube.com/watch?v=eoXn6nwV694, https://www.youtube.com/watch?v=U0_ONQQ5ZNM on how 3D projetion works and make
//roations and movements in homogenuous cordinates
// https://www.tomdalling.com/blog/explaining-homogenous-coordinates-and-projective-geometry/ has an explanation for deriving the
//matricies needed to make the rendering work
namespace Krec{

class Matrix: public Vector3d< Vector3d<float> > {
    public:
    Matrix(){
        x = Vector3d<float>();
        y = Vector3d<float>();
        z = Vector3d<float>();
        w = Vector3d<float>();
    }
    Matrix(Vector3d<float> c1, Vector3d<float> c2, Vector3d<float> c3, Vector3d<float> c4){
        x = c1;
        y = c2;
        z = c3;
        w = c4;
    }
    
    Vector3d<float> operator*(Vector3d<float> vector){
        return Vector3d<float>(
            this->x * vector,
            this->y * vector,
            this->z * vector,
            this->w * vector
        ).perspective_division();
    }

    friend std::ostream& operator<<(std::ostream& os, Matrix M){
         os << std::endl << M[1] <<"," << std::endl
            << M[2] << "," << std::endl
            << M[3] << "," << std::endl
            << M[4] << "," << std::endl;
        return os;
    }

};

#define I Matrix(E1,E2,E3,E4)

class Translation : public Matrix{
    public:
    Translation(Vector3d<float> position): Matrix(
        Vector3d<float>(1,0,0,position[1]),
        Vector3d<float>(0,1,0,position[2]),
        Vector3d<float>(0,0,1,position[3]),
        Vector3d<float>(0,0,0,1)
    ){
        //intentionaly left blank
    }
};

class Projection : public Matrix{
    public:
    /// @brief 
    /// @param n  near plane z value or FOV
    /// @param f  far plane value or max Redner distance
    Projection(float n, float f): Matrix(
        Vector3d<float>(1,0,0,0),
        Vector3d<float>(0,1,0,0),
        Vector3d<float>(0,0,n+f, -n*f),
        Vector3d<float>(0,0,1,0)
    ){
        //intentionaly left blank
    }
    //     Projection(float n, float f, float r= 400, float t= 400):Matrix(
    //     Vector3d<float>(r/n,0,0,0),
    //     Vector3d<float>(0,r/t,0,0),
    //     Vector3d<float>(0,0,(n+f)/(f-n), -2*n*f/(f-n)),
    //     Vector3d<float>(0,0,1,0))
    // {}
};


}//nampespace Krec