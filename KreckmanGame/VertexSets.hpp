#pragma once
#include <stdexcept>
#include <vector>

#include "Vector3d.hpp"
#include "Movement.hpp"
namespace Krec{

    class Simplex{
        public:
        Vector3d<float> Vertex1;
        Vector3d<float> Vertex2;
        Vector3d<float> Vertex3;
        Vector3d<float> Normal;

        Vector3d<float> calculateNormal(Vector3d<float> Vertex1, Vector3d<float> Vertex2, Vector3d<float> Vertex3){
            Vector3d<float> n = (Vertex2 - Vertex1) ^ (Vertex3 - Vertex1);
            return n/n.magnitude();
        }

        public:
        
        Simplex(): 
        Vertex1(Vector3d<float>()), 
        Vertex2(Vector3d<float>()), 
        Vertex3(Vector3d<float>()),
        Normal(Vector3d<float>()){
            //intetionly left blank
        }

        Simplex(Vector3d<float> v1, Vector3d<float> v2, Vector3d<float> v3):
        Vertex1(v1), 
        Vertex2(v2), 
        Vertex3(v3),
        Normal(calculateNormal(v1,v2,v3)){
            //intetionly left blank
        }

        Vector3d<float> operator[](uint8_t index){
            switch(index){
                case 1: return Vertex1;
                case 2: return Vertex2;
                case 3: return Vertex3;
                default: throw std::out_of_range("Index out of range 1-3");
            }
        }

        friend std::ostream& operator<<(std::ostream& os, Simplex simplex){
            os << "{"<< simplex[1] << ", " << simplex[2] << ", " << simplex[3] << "}";
            return os;
        }

        friend Simplex operator*(Matrix M , Simplex simplex){
            simplex.Vertex1 = M * simplex.Vertex1;
            simplex.Vertex2 = M * simplex.Vertex2;
            simplex.Vertex3 = M * simplex.Vertex3;
            simplex.Normal  = M * simplex.Normal;
            return simplex; 
        }


    };

    class Complex{
        private:
        std::vector<Simplex> complex;

        public:
        Complex(): complex(std::vector<Simplex>()){
            //intentionaly left balnk
        }
        Complex(Complex& oldComplex){
            complex = oldComplex.complex;
        }
        // ~Complex(){
        //     for(int i = 1; i <= complex.size(); i++){
        //         delete complex[i];
        //     }
        // }
        void push_back(Simplex simplex){
            complex.push_back(simplex);
        }
        int size(){
            return this->complex.size();
        }

        Simplex operator[](int index){
            if(0 < index && index <= this->complex.size()){
                return this->complex.at(index-1);
            }
            throw std::out_of_range("Index out of range");
        }

        friend std::ostream& operator<<(std::ostream& os, Complex complex){
            os << "[" << std::endl;
            for(int i=1; i<=complex.complex.size(); ++i){
                os<< complex[i] << "," << std::endl;
            }
            os << "]";
            return os;
        }

        friend Complex& operator*(Matrix M, Complex& complex){
            for(int i = 0; i < complex.complex.size(); i++){
                complex.complex.at(i) = M*(complex.complex.at(i));
            }
            return complex;
        }
    };

}//namespace Krec