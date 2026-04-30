#pragma once
//Standrd Library
#include <vector>
#include <cmath>
//VMI Game Engine
#include <Color.hpp>
#include <Thing.hpp>
#include <PolygonShape.hpp>
#include <Vector2d.hpp>
#include <Game.hpp>

#define near 1
#define far 100
#define _Y_MIN -50.0f
namespace engine{
class Vector3D_h{
    public:
    float x;
    float y;
    float z;
    float w;
    friend class Matrix_h;
    friend class Player;



    public:
    friend class Vector3D_h;
    friend class Matrix_h;
    friend class Simplex;
    friend class Complex; 
    
    //////
    /// @brief Initilizes a blank Vector with all Values of 0
    //////
    Vector3D_h(): x(0.0f), y(0.0f), z(0.0f), w(0.0f){
        //intetionaly left blank
    }

    //////
    /// @brief Initilizes a Vector with the specified Values
    /// @param _x,_y,_z,_w 
    //////
    Vector3D_h(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w){
        //intetioaly left blank
    }
    ///////
    /// @brief The dot product of two Vectors
    /// @param V1,V2 
    //////
    friend float operator*(Vector3D_h V1, Vector3D_h V2){
        return (V1.x*V2.x) + (V1.y*V2.y) + (V1.z*V2.z) + (V1.w*V2.w);
    }
    
    //////
    /// @brief Returns the cross product of two Vectors, which is perpendicular to both
    /// @param V1,V2 
    //////
    friend Vector3D_h operator^(Vector3D_h V1, Vector3D_h V2){
        return Vector3D_h(
            V1.y*V2.z-V1.z*V2.y,
            V1.z*V2.x - V1.x*V2.z,
            V1.x*V2.y-V1.y*V2.x,
            1
        );
    }
    friend Vector3D_h operator*(int scale, Vector3D_h V){
        V.x *= scale;
        V.y *= scale;
        V.z *= scale;
        return V;
    }

    friend std::ostream& operator<<(std::ostream& os, Vector3D_h vect){
        os << "("<< vect.x << ", " << vect.y << ", " << vect.z << ", " << vect.w << ")";
        return os;
    }

    friend Vector3D_h operator+(Vector3D_h V1, Vector3D_h V2){
        V1.x = V1.x + V2.x;
        V1.y = V1.y + V2.y;
        V1.z = V1.z + V2.z;
        return V1;
    }

};
#define e1 Vector3D_h(1,0,0,1)
#define e2 Vector3D_h(0,1,0,1)
#define e3 Vector3D_h(0,0,1,1)
#define O Vector3D_h(0,0,0,1)

class Matrix_h{
    public:
    Vector3D_h r1;
    Vector3D_h r2;
    Vector3D_h r3;
    Vector3D_h r4;
    friend class Projection;

    public:
    Matrix_h():
       r1(Vector3D_h(1,0,0,0)), r2(Vector3D_h(0,1,0,0)), r3(Vector3D_h(0,0,1,0)), r4(Vector3D_h(0,0,0,1)){
        //intetionly left blank
    }
    Matrix_h(Vector3D_h _c1, Vector3D_h _c2, Vector3D_h _c3, Vector3D_h _c4): r1(_c1), r2(_c2), r3(_c3), r4(_c4){
        //intetionaly left blank
    }
    ///////
    /// @brief FIX ME
    /// @param M1,M2 
    //////
    friend Matrix_h operator*(Matrix_h M1, Matrix_h M2){
        Vector3D_h c1 = Vector3D_h(M2.r1.x,M2.r2.x,M2.r3.x,M2.r4.x);
        Vector3D_h c2 = Vector3D_h(M2.r1.y,M2.r2.y,M2.r3.y,M2.r4.y);
        Vector3D_h c3 = Vector3D_h(M2.r1.z,M2.r2.z,M2.r3.z,M2.r4.z);
        Vector3D_h c4 = Vector3D_h(M2.r1.w,M2.r2.w,M2.r3.w,M2.r4.w);
        return Matrix_h(M1*c1,M1*c2,M1*c3,M1*c4);
    }
    friend Vector3D_h operator*(Matrix_h M, Vector3D_h V){
        Vector3D_h ans = Vector3D_h(
            M.r1*V,
            M.r2*V,
            M.r3*V,
            M.r4*V
        );
        // ans.perspective_division();
        return ans;
    }
    friend std::ostream& operator<<(std::ostream& os, Matrix_h M){
        os << M.r1 << std::endl;
        os << M.r2 << std::endl;
        os << M.r3 << std::endl;
        os << M.r4 << std::endl;
        return os;
    }

};


class Translation : public Matrix_h{
    private:
    Translation(){
        //intetionly left blank
    }
    public:
    Translation(Vector3D_h V): Matrix_h(
        Vector3D_h(1.0f,0.0f,0.0f,V.x),
        Vector3D_h(0.0f,1.0f,0.0f,V.y),
        Vector3D_h(0.0f,0.0f,1.0f,V.z),
        Vector3D_h(0.0f,0.0f,0.0f,1.0f)){
            //intetionly left blank
        }
    Translation(float x, float y, float z): Matrix_h(
        Vector3D_h(1.0f,0.0f,0.0f,x),
        Vector3D_h(0.0f,1.0f,0.0f,y),
        Vector3D_h(0.0f,0.0f,1.0f,z),
        Vector3D_h(0.0f,0.0f,0.0f,1)){
            //intetionly left blank
        }

};
class Rotation_x : public Matrix_h{
    public:
    //HR: Got the principle rotation matricies from wikipidia
    Rotation_x(float angle): Matrix_h(Vector3D_h(1.0f,0.0f,0.0f,0.0f),
    Vector3D_h(0.0f,cos(angle), -sin(angle), 0.0f),
    Vector3D_h(0.0f,sin(angle), cos(angle), 0.0f),
    Vector3D_h(0.0f,0.0f,0.0f,1.0f)){
        //intetionly left blank
    }

};
class Rotation_y : public Matrix_h{
    public:
    //HR: Got the principle rotation matricies from wikipidia
    Rotation_y(float angle): Matrix_h(
    Vector3D_h(cos(angle),0.0f, -sin(angle), 0.0f),
    Vector3D_h(0.0f,1,0.0f,0.0f),
    Vector3D_h(-sin(angle), 0.0f, cos(angle), 0.0f),
    Vector3D_h(0.0f,0.0f,0.0f,1.0f)){
        //intetionly left blank
    }

};
class Rotation_z : public Matrix_h{
    public:
    //HR: Got the principle rotation matricies from wikipidia
    Rotation_z(float angle): Matrix_h(
    Vector3D_h(cos(angle), -sin(angle), 0.0f, 0.0f),
    Vector3D_h(sin(angle), cos(angle),0.0f, 0.0f),
    Vector3D_h(0.0f,0.0f,1.0f,0.0f),
    Vector3D_h(0.0f,0.0f,0.0f,1.0f)){
        //intetionly left blank
    }

};
class View{
    private:
    int width; /// window width
    int height; /// window height
    float FOV = 120;
    Matrix_h R_camera; // holds the maipulation of the world so new objects can have it applied and tracked
    Vector3D_h T_camera; /// changex with the with and height
    Matrix_h projectionMatrix; /// changex with the with and height
    friend class Renderable;
    friend class Simplex;
    friend class Complex;
    friend class Player;


    class Projection : public Matrix_h{
    public:
    /// @param FOV the horizontal angle of view
    Projection(View view){
        float ASPECT_RATIO = view.width/view.height;
        float t = 1/tan(view.FOV*M_PI/360);
        float r = t*ASPECT_RATIO;
        float n = .10f;
        float f = 1000.0f;

        r1 = Vector3D_h(n/r,0,0,0);
        r2 = Vector3D_h(0,n/t,0,0);
        r3 = Vector3D_h(0,0,-(f+n)/(f-n), -2*f*n/(f-n));
        r4 = Vector3D_h(0,0,-1,0);
    }
};
    void updateProjection(){
        projectionMatrix = Projection(*this);
    }

    public:
     void update(int newHeight, int newWidth, float newFOV){
        height = newHeight;
        width = newWidth;
        FOV = newFOV;
        this->updateProjection();
     }

    View(int _w, int _h, float _FOV): width(_w), height(_h), FOV(_FOV), projectionMatrix(Projection(*this)){
    //intentionly left blank
    }
    void setFOV(float _FOV){
        FOV = _FOV;
    }
    void moveView(Vector3D_h shift){
        T_camera = shift + T_camera;
    }
    void rotateView(Matrix_h viewRotation){
        R_camera = viewRotation * R_camera;

    }
    



};
class Renderable : public vmi::Thing{
    public:
    friend class Simplex;
    Renderable(View view) : Thing({(double)view.width/2, (double)view.height/2},nullptr){
        //intetionaly left blank
    }
    void setShape(vmi::PolygonShape* _shape){
        shape = _shape;
    }

    //////
    /// @brief /// DO NOT USE ///
    //////
    void handleCollision(const Thing *other){
        //intenonlay left blank
    }


};

//////
/// @brief A simplex is a 2d triangle embeded in 3d space, this object exists as
/// @brief long as the asset is used, but the rendered aspect is changed based on game requiremnts 
//////
class Simplex{
    private:
    Vector3D_h V1;
    Vector3D_h V2;
    Vector3D_h V3;
    vmi::Color color;
    Renderable* img;
    friend class Player;

    public:
    Simplex(Vector3D_h _V1, Vector3D_h _V2, Vector3D_h _V3, vmi::Color _color): V1(_V1), V2(_V2), V3(_V3), color(_color), img(nullptr){
        //intetionly left blank
    }
    Simplex(Vector3D_h _V1, Vector3D_h _V2, Vector3D_h _V3, vmi::Color _color, Renderable* _img): V1(_V1), V2(_V2), V3(_V3), color(_color), img(_img){
        //intetionly left blank
    }

    friend Simplex operator*(Matrix_h M, Simplex simplex){
        return Simplex(
        M*simplex.V1,
        M*simplex.V2,
        M*simplex.V3,
        simplex.color,
    simplex.img);
    }
    Simplex operator+(Vector3D_h V){
        return Simplex(
        V1 + V,
        V2 + V,
        V3 + V,
        color,img);
    }

    void render(View* view, Vector3D_h pos){
            img = new Renderable(*view);
            vmi::PolygonShape* shape = new vmi::PolygonShape();
            //projects the matrix down to 2d
            Simplex worldSimplex = this->operator+(pos);
            worldSimplex = worldSimplex + view->T_camera;
            worldSimplex = view->R_camera*worldSimplex;
            //HR: Calude on the formula only given in the quote
            //pixel_x = (x_ndc + 1) / 2 * width
            //pixel_y = (1 − y_ndc) / 2 * height     ← note the flip!
            //creates the shape for vmi engine to render 
                int w = view->width;
                int h = view->height;

                shape->addPoint({( worldSimplex.V1.x /  worldSimplex.V1.z   )/2*w,(1/2- worldSimplex.V1.y /  worldSimplex.V1.z ) /2*h});
                shape->addPoint({( worldSimplex.V2.x /  worldSimplex.V2.z   )/2*w,(1/2- worldSimplex.V2.y /  worldSimplex.V2.z ) /2*h});
                shape->addPoint({( worldSimplex.V3.x /  worldSimplex.V3.z   )/2*w,(1/2- worldSimplex.V3.y /  worldSimplex.V3.z ) /2*h});
                shape->setFill(color);

            //Sets the renderables shape
            img->setZ(-(worldSimplex.V1.z+worldSimplex.V2.z+worldSimplex.V3.z)/3);
            // std::cout << *this << ", z-Value: " << (V1.z+V2.z+V3.z)/3 << std::endl;;
            img->setShape(shape);
    }

    friend std::ostream& operator<<(std::ostream& os, Simplex S){
        os << "{" <<  S.V1 << ", " << S.V2 << ", " << S.V3 << "}" ;
        return os;
    }


};

class Complex{
    public:
    std::vector<Simplex> complex;
    Vector3D_h position;
    friend class Game;
    friend class Cube;
    friend class Player;

    
    public:
    
    std::optional<Complex> operator*(Matrix_h M){
        std::optional<Complex> ans;
        if(typeid(M) != typeid(View::Projection)){
            for(auto it = begin(complex); it != end(complex); ++it){
                *it = M*(*it);
            }
            return ans;
        }
        assert(typeid(M) == typeid(View::Projection));
        for(auto it = begin(complex); it != end(complex); ++it){
            ans->push_back(M*(*it));
        }
        return ans;

    }
    
    Complex(){
        objects.push_back(this);
    }
    void push_back(Simplex simplex){
        complex.push_back(simplex);
    }
    //HR: std::optional from Stack overflow

    friend std::optional<Complex> operator*(Matrix_h M, Complex &complex){
        return complex*M;
    }
    void render(View* view){
        //hr stack overflow
        int i = 0;
        for(i = 0; i < this->complex.size(); ++i){
            this->complex.at(i).render(view, position);  
        }
    }
    Vector3D_h getWorldPosition(View view){
        return position + view.T_camera;
    }
    friend std::ostream& operator<<(std::ostream& os, Complex complex){
        for(auto it = begin(complex.complex); it != end(complex.complex); ++it){
            os << *it << std::endl;
        }
        return os;
    }

    public:
    static void renderAll(View* view){
        for(int complex = 0; complex < objects.size(); ++complex){
            objects.at(complex)->render(view);
        }
    }
    //list of all objects
    private:
    static inline std::vector<Complex* > objects;

};

class Cube : public Complex{
    public:
        Cube(float _size){
            //Front
            this->push_back(Simplex(O, _size*e1, _size*(e1+e2), vmi::Color::Magenta));
            this->push_back(Simplex(O, _size*e2, _size*(e1+e2), vmi::Color::Magenta));
            //Left Side
            this->push_back(Simplex(O, _size*e3, _size*(e2+e3), vmi::Color::Yellow));
            this->push_back(Simplex(O, _size*e2, _size*(e2+e3), vmi::Color::Yellow));
            //Bottom
            this->push_back(Simplex(O, _size*(e1), _size*(e1+e3), vmi::Color::Blue));
            this->push_back(Simplex(O, _size*(e3), _size*(e1+e3), vmi::Color::Blue));
            //Right Side
            this->push_back(Simplex(_size*e1, _size*(e1+e3), _size*(e1+e2+e3), vmi::Color::Yellow));
            this->push_back(Simplex(_size*e1, _size*(e1+e2), _size*(e1+e2+e3), vmi::Color::Yellow));
            //Back
            this->push_back(Simplex(_size*e3, _size*(e1+e3), _size*(e1+e2+e3), vmi::Color::Magenta));
            this->push_back(Simplex(_size*e3, _size*(e2+e3), _size*(e1+e2+e3), vmi::Color::Magenta));
            //Top
            this->push_back(Simplex(_size*e2, _size*(e1+e2), _size*(e1+e2+e3), vmi::Color::Blue));
            this->push_back(Simplex(_size*e2, _size*(e2+e3), _size*(e1+e2+e3), vmi::Color::Blue));
            // //Front
            // this->push_back(Simplex(O, _size*e1, _size*(e1+e2), vmi::Color::Magenta));
            // this->push_back(Simplex(O, _size*e2, _size*(e1+e2), vmi::Color::Magenta));
            // this->size = _size;
        }
        Cube(float _size, vmi::Color color){
            //Front
            this->push_back(Simplex(O, _size*e1, _size*(e1+e2), color));
            this->push_back(Simplex(O, _size*e2, _size*(e1+e2), color));
            //Left Side
            this->push_back(Simplex(O, _size*e3, _size*(e2+e3), color));
            this->push_back(Simplex(O, _size*e2, _size*(e2+e3), color));
            //Bottom
            this->push_back(Simplex(O, _size*(e1), _size*(e1+e3), color));
            this->push_back(Simplex(O, _size*(e3), _size*(e1+e3), color));
            //Right Side
            this->push_back(Simplex(_size*e1, _size*(e1+e3), _size*(e1+e2+e3), color ));
            this->push_back(Simplex(_size*e1, _size*(e1+e2), _size*(e1+e2+e3), color ));
            //Back
            this->push_back(Simplex(_size*e3, _size*(e1+e3), _size*(e1+e2+e3), color ));
            this->push_back(Simplex(_size*e3, _size*(e2+e3), _size*(e1+e2+e3), color));
            //Top
            this->push_back(Simplex(_size*e2, _size*(e1+e2), _size*(e1+e2+e3), color));
            this->push_back(Simplex(_size*e2, _size*(e2+e3), _size*(e1+e2+e3), color)) ;
            // //Front
            // this->push_back(Simplex(O, _size*e1, _size*(e1+e2), vmi::Color::Magenta));
            // this->push_back(Simplex(O, _size*e2, _size*(e1+e2), vmi::Color::Magenta));
            // this->size = _size;
        }

};

class Player: public Cube{
    public:
    const static vmi::Key R = vmi::Key::A;
    const static vmi::Key L = vmi::Key::D;
    const static vmi::Key F = vmi::Key::W;
    const static vmi::Key B = vmi::Key::S;
    static Player* const self;

    public:
    Player(Vector3D_h init_position) : Cube(20){
        position = init_position;
    }
    Player(float x, float y, float z) : Cube(20){
        position = {x,y,z,1.0f};
    }

    static void move(float dt, float speed, View* view){
        //Model Movemnets
        if(vmi::Game::isKeyPressed(R)){
            Vector3D_h T = Vector3D_h(-dt*speed, 0.0f, 0.0f,0.0f);
            self->position = self->position + T;
        }
        if(vmi::Game::isKeyPressed(L)){
            Vector3D_h T = Vector3D_h(dt*speed, 0.0f, 0.0f,0.0f);
            self->position = self->position + T;
        }
        if(vmi::Game::isKeyPressed(F)){
            Vector3D_h T = Vector3D_h(0.0f, 0.0f,dt*speed,0.0f);
            self->position = self->position + T;
        }
        if(vmi::Game::isKeyPressed(B)){
            Vector3D_h T = Vector3D_h(0.0f, 0.0f, -dt*speed, 0.0f);
            self->position = self->position + T;

        }

        //camera movements
        if(vmi::Game::isKeyPressed(vmi::Key::Right)){
            Vector3D_h T = Vector3D_h(-dt*speed, 0.0f, 0.0f,0.0f);
            view->T_camera = view->T_camera + T;
        }
        if(vmi::Game::isKeyPressed(vmi::Key::Left)){
            Vector3D_h T = Vector3D_h(dt*speed, 0.0f, 0.0f,0.0f);
            view->T_camera = view->T_camera + T;
        }
        if(vmi::Game::isKeyPressed(vmi::Key::Up)){
            Vector3D_h T = Vector3D_h(0.0f, 0.0f,dt*speed,0.0f);
            view->T_camera = view->T_camera + T;
        }
        if(vmi::Game::isKeyPressed(vmi::Key::Down)){
            Vector3D_h T = Vector3D_h(0.0f, 0.0f, -dt*speed, 0.0f);
            view->T_camera = view->T_camera + T;
        }

        /// @param Vy y velocity
        static float Vy = 0.0f;
        const float Y_MIN = _Y_MIN;
        const float GRAVITY = 40;
        float bottom = self->getWorldPosition(*view).y;
        // Jump Machenics
        if(vmi::Game::isKeyPressed(vmi::Key::Space)){
            Vy = 40.0f;
        }
        if(bottom >= Y_MIN){
            Vy -= GRAVITY*dt;
        }
        if(bottom <= Y_MIN && Vy <=0.0f){
            Vy = 0.0f;
        }
        std::cout << bottom << std::endl;
       self->position = self->position + Vector3D_h(0.0f,Vy*dt,0.0f,0.0f);

    }
};

class Floor: public Complex{
    
    public:
    Floor(float _size){
    Matrix_h T = Translation(0.0f,0.0f,100.0f);
    this->push_back(Simplex(O, -50*e2, _size*(e1+e3), vmi::Color::White));
    this->push_back(Simplex(O, _size*(e3), _size*(e1+e3), vmi::Color::White));
    this->operator*(T);
    }
};

class Game : public vmi::Game{
    private:
    View* view; 
    public:
        Game(int _width, int _height, View* _view) : vmi::Game("3D Game", _width, _height), view(_view){
            //Intetionly left blank
        }
        void update(double dt){
            dt = (float) dt;
            Player::move(dt, 20.0f, view);
            Complex::renderAll(view);
        }
            // Game loop
    inline void playGame()
    {
        sf::Clock clock; // clock for measuring frame time

        // game loop -- repeat until game ends or window is closed
        while (!isOver() && window->isOpen())
        {
            while (const std::optional event = window->pollEvent())
            {
                // Window closed or escape key pressed: exit
                if (event->is<sf::Event::Closed>())
                    window->close();
            }

            // measure frame time
            double dt = clock.restart().asSeconds();

            // make sure this stays sane
            dt = (dt > .04) ? .04 : dt;

            // update the timers
            vmi::Timer::updateTimers(dt);

            // update any game specific features
            update(dt);
            
            // remove all the dead things
            vmi::Thing::removeDeadThings();
            
            // draw everyone
            vmi::Thing::drawAll(*window);

            // claers the frame buffer for all objects 
            vmi::Thing::killAllThings();
        }

        // game is over, so delete the window
        delete window;
    }
};

}//namespace engine