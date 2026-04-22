//HR: GeeksforGeeks on errors
#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>


namespace Krec{

template<typename scalarType> class Vector3d{
    
    protected:
        scalarType x;
        scalarType y;
        scalarType z;
        scalarType w;
        friend class Simplex;
        friend class Matrix;

    public:
    Vector3d(): x(0), y(0), z(0),w(1){
        //left blank
    }
    Vector3d(scalarType scalar): x(scalar), y(scalar), z(scalar), w(1){
        //left blank
    }
    Vector3d(scalarType _x,scalarType _y,scalarType _z): x(_x), y(_y), z(_z), w(1){
        //left blank
    }
    Vector3d(scalarType _x,scalarType _y,scalarType _z, scalarType _w): x(_x), y(_y), z(_z), w(_w){
        //left blank
    }
    ~Vector3d(){}

    
    ///////////////
    ///@breif Unary operators
    ///
    /////////////////
    friend Vector3d operator-(Vector3d vect){
        return Vector3d(-vect.x,-vect.y,-vect.z);
    }
    scalarType operator[](char index) const{
        switch (index){
            case 1:
            return this->x;
            case 2:
            return this->y;
            case 3: 
            return this->z;
            case 4:
            return this->w;
            default:
            throw std::invalid_argument( "Improper Index:\n\t index must be 1,2,3" );
        }
    }
    
    //////////////////////////////////////////////
    /// @brief Operations for Vector on Vector
    /// @return 
    ///////////////////////////////////////////////
    
    friend Vector3d operator+=(Vector3d lhs, Vector3d rhs){
        return Vector3d(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z,1);
    }
    friend Vector3d operator+(Vector3d lhs,Vector3d rhs){
        return lhs += rhs;
    }
    friend Vector3d operator-=(Vector3d lhs,Vector3d rhs){
        return lhs + (-rhs);
    } 
    friend Vector3d operator-(Vector3d lhs,Vector3d rhs){
        return lhs -= rhs;
    }
    
    
    ////////////////////////////////////////
    /// @brief sclar - vector operations
    /// @return 
    //////////////////////////////////////////
    
    friend Vector3d operator+(scalarType scalar, Vector3d vector){
        return Vector3d(scalar) += vector;
    }
    friend Vector3d operator-(scalarType scalar, Vector3d vector){
        return Vector3d(scalar) -= vector;
    }
    friend Vector3d operator+(Vector3d vector, scalarType scalar){
        return Vector3d(scalar) += vector;
    }
    friend Vector3d operator-(Vector3d vector, scalarType scalar){
        return Vector3d(scalar) -= vector;
    }
    friend Vector3d operator*(Vector3d vector, scalarType scalar){
        return Vector3d(scalar*vector.x,scalar*vector.y,scalar*vector.z,scalar*vector.w);
    }
    friend Vector3d operator*(scalarType scalar,Vector3d vector){
        return Vector3d(scalar*vector.x,scalar*vector.y,scalar*vector.z,scalar*vector.w);
    }
    friend Vector3d operator/(Vector3d vector, scalarType scalar){
        return Vector3d(vector.x/scalar,vector.y/scalar,vector.z/scalar);
    }
    Vector3d perspective_division(){
        if(this->w == 0){
            return *this;
        }
        return *this/this->w;
    }
    //////////////////////////////////////////
    /// @brief Scalar and Cross Products
    //////////////////////////////////////////
    friend scalarType operator*(Vector3d lhs, Vector3d rhs){
        return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w);
    }
    friend Vector3d operator^(Vector3d l, Vector3d r){
        // i  j  k
        // lx ly lz
        // rx ry rz
        return Vector3d(
            l.y*r.z-l.z*r.y,
            l.z*r.x - l.x*r.z,
            l.x*r.y-l.y*r.x
        );
    }
    scalarType magnitude(){
        return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
    }
    ///////////
    /// Boolean Operations
    ///
    ///////////

    friend unsigned char operator==(Vector3d lhs, Vector3d rhs){
        return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
    }
    friend unsigned char operator!=(Vector3d lhs, Vector3d rhs){
        return !(lhs==rhs);
    }


    /////////
    // Output Operators
    /////////
    friend std::ostream& operator<<(std::ostream& os, Vector3d vect){
        os << "("<< vect.x << ", " << vect.y << ", " << vect.z << ", " << vect.w << ")";
        return os;
    }



};




}//namespace Kreckman
#define e1 Krec::Vector3d<float>(1,0,0)
#define e2 Krec::Vector3d<float>(0,1,0)
#define e3 Krec::Vector3d<float>(0,0,1)

#define E1 Krec::Vector3d<float>(1,0,0,0)
#define E2 Krec::Vector3d<float>(0,1,0,0)
#define E3 Krec::Vector3d<float>(0,0,1,0)
#define E4 Krec::Vector3d<float>(0,0,0,1)