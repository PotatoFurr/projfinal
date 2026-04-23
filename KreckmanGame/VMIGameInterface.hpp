#pragma once
#include <Game.hpp>
#include <Keyboard.hpp>
#include <PolygonShape.hpp>
#include <Thing.hpp>
#include <MovingThing.hpp>
#include <Timer.hpp>
#include <Color.hpp>
#include <iostream>

#include <Vector3d.hpp>
#include <VertexSets.hpp>
#include <Movement.hpp>

#define HEIGHT 800
#define WIDTH 800

#define CENTER vmi::Vector2d(WIDTH/2,HEIGHT/2)




namespace iml{
    class Screen{
        private:
            int width;
            int height;
            vmi::Vector2d center;

        public:
        Screen(int _width, int _height): width(_width), height(_height), center(vmi::Vector2d(_width/2,_height/2)){
            //intentionaly left blank
        }
        void resize(int w, int h){
            height = h;
            width = w;
            center.setX(w/2);
            center.setY(h/2);
        }
        vmi::Vector2d getCenter(){
            return center;
        }
    };

    class Game : public vmi::Game{
        public:
            Game() : vmi::Game("3D Game", WIDTH, HEIGHT){
                //Intetionly left blank
            }
            void update(double dt){

            }

    };


///////////////////
/// @brief For interaction between the thing class and 3d thing
/// @param Vector2d x;       position of thing
/// @param double angle;     rotation angle
/// @param Vector2d center;  center point, used for rotation
/// @param double scale;     scaling factor
/// @param Shape *shape;     shape for drawing
/// @param bool alive;  whether or not this thing is still alive
/////////////////////
    class Renderable: public vmi::Thing{
        private:
        Screen* screen;
        friend class Simplex;
        friend class Complex;

        vmi::PolygonShape* render(Krec::Simplex simplex){
            Krec::Projection P = Krec::Projection(0.1f,100.0f);
            simplex = P*simplex;
            vmi::PolygonShape* shape = new vmi::PolygonShape();
            shape->addPoint(vmi::Vector2d(simplex[1][1],simplex[1][2]));
            shape->addPoint(vmi::Vector2d(simplex[2][1],simplex[2][2]));
            shape->addPoint(vmi::Vector2d(simplex[3][1],simplex[3][2]));
            shape->setFill(vmi::Color::White);
            return shape;
        }
    
        public:
        Renderable(Krec::Simplex gameObject, Screen* _screen): 
        vmi::Thing(_screen->getCenter(),render(gameObject)),
        screen(_screen)
        {
        // intetionaly left blank
        }
        void shutUpError(){
            std::cout << "center" << this->screen->getCenter();
        }

        void handleCollision(const vmi::Thing* other){

        }
    
    
    };

    class Simplex : public Krec::Simplex{
        private:
        Renderable* img;

        public:
        ~Simplex(){
            if(img != NULL){
            img->die();
            }
        }
        Simplex(Krec::Vector3d<float> v1, Krec::Vector3d<float> v2, Krec::Vector3d<float> v3): Krec::Simplex(v1,v2,v3), img(NULL){
        }
        Simplex(Krec::Simplex simplex): Krec::Simplex(simplex), img(NULL){

        }
        friend iml::Simplex operator*(Krec::Matrix M , iml::Simplex simplex){
            simplex.Vertex1 = M * simplex.Vertex1;
            simplex.Vertex2 = M * simplex.Vertex2;
            simplex.Vertex3 = M * simplex.Vertex3;
            simplex.Normal  = M * simplex.Normal;
            return simplex; 
        }

        void render(Screen* screen, double _scale = 1.0){
            img = new Renderable(*dynamic_cast<Krec::Simplex*>(this),screen);
            img->scale = _scale;
        }
        
        Renderable* getRend(){
            return img;
        }


    };


    class Complex{
        private:
        std::vector<iml::Simplex> complex;

        public:
        friend class iml::Simplex;
        Complex(): complex(std::vector<iml::Simplex>()){
            //intentionaly left balnk
        }
        Complex(Complex& oldComplex){
            complex = oldComplex.complex;
        }
        Complex(Krec::Complex& oldComplex){
            for(int i=1; i<oldComplex.size(); ++i){
            complex.push_back(Simplex(oldComplex[i]));
            }
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

        friend Complex& operator*(Krec::Matrix M, Complex& complex){
            for(int i = 0; i < complex.complex.size(); i++){
                complex.complex.at(i) = M*(complex.complex.at(i));
            }
            return complex;
        }
        void render(Screen* screen, std::vector<vmi::Color> colors = vmi::Color::White, double _scale = 1.0){
            int len = colors.size();
            for(int i = 0; i< this->size(); ++i){
                this->complex.at(i).render(screen, _scale);
            }
        }
    };

    class Cube : public iml::Complex{

        public:
        Cube(){
            this->push_back(Simplex(0,e1,e1+e2));
            this->push_back(Simplex(0,e2,e1+e2));
            this->push_back(Simplex(e2,e1+e2,e2+e3));
            this->push_back(Simplex(e2,e1+e2,e2+e3));
        }

    };

}; // namespace Interface