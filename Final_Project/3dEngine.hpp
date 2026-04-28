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
namespace engine{
class Vector3D_h{
    private:
    float x;
    float y;
    float z;
    float w;
    friend class Matrix_h;


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
    void perspective_division(){
        if(this->w == 0){
            return;
        }
        this->x = this->x / this->w;
        this->y = this->y / this->y;
        this->z = this->z / this->z;
        this->w = 1.0f;
    }

    friend std::ostream& operator<<(std::ostream& os, Vector3D_h vect){
        os << "("<< vect.x << ", " << vect.y << ", " << vect.z << ", " << vect.w << ")";
        return os;
    }

    float operator[](int index){
        switch(index){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::runtime_error("Out of Bounds Indexing");
        }
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
    Matrix_h(){
        //intetionly left blank
    }
    Matrix_h(Vector3D_h _c1, Vector3D_h _c2, Vector3D_h _c3, Vector3D_h _c4): r1(_c1), r2(_c2), r3(_c3), r4(_c4){
        //intetionaly left blank
    }
    ///////
    /// @brief FIX ME
    /// @param M1,M2 
    //////
    friend Matrix_h operator*(Matrix_h M1, Matrix_h& M2){
        return Matrix_h();
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
        Vector3D_h(1.0f,0.0f,0.0f,V[0]),
        Vector3D_h(0.0f,1.0f,0.0f,V[1]),
        Vector3D_h(0.0f,0.0f,1.0f,V[2]),
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
    Matrix_h cameraMatrix; // holds the maipulation of the world so new objects can have it applied and tracked
    float FOV = 120;
    Matrix_h projectionMatrix; /// changex with the with and height
    friend class Renderable;
    friend class Simplex;
    friend class Complex;

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

    public:
    void updateProjection(){
        projectionMatrix = Projection(*this);
    }
     void update(int newHeight, int newWidth, float newFOV){
        height = newHeight;
        width = newWidth;
        FOV = newFOV;
        this->updateProjection();
     }

    View(int _w, int _h, float _FOV): width(_w), height(_h), FOV(_FOV), projectionMatrix(Projection(*this)){
    //intentionly left blank
    }

    void transform(Matrix_h M){
        M * cameraMatrix;
    }
    void setFOV(float _FOV){
        FOV = _FOV;
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

    void render(View view, float _scale){
            img = new Renderable(view);
            img->scale =_scale;
            vmi::PolygonShape* shape = new vmi::PolygonShape();
            //projects the matrix down to 2d
            view.projectionMatrix*(*this);
            //HR: Calude on the formula only given in the quote
            //pixel_x = (x_ndc + 1) / 2 * width
            //pixel_y = (1 − y_ndc) / 2 * height     ← note the flip!
            //creates the shape for vmi engine to render 
                int w = view.width;
                int h = view.height;

                shape->addPoint({(V1.x/V1.z )/2*w,(1/2-V1.y/V1.z)/2*h});
                shape->addPoint({(V2.x/V2.z )/2*w,(1/2-V2.y/V2.z)/2*h});
                shape->addPoint({(V3.x/V3.z )/2*w,(1/2-V3.y/V3.z)/2*h});
                shape->setFill(color);

            //Sets the renderables shape
            // img->setZ(-(V1.z+V2.z+V3.z)/3);
            img->setShape(shape);
    }

    friend std::ostream& operator<<(std::ostream& os, Simplex S){
        os << "{" <<  S.V1 << ", " << S.V2 << ", " << S.V3 << "}" << std::endl << "Renderable @ " << S.img;
        return os;
    }


};

class Complex{
    public:
    std::vector<Simplex> complex;
    float size = 100;
    friend class Game;
    friend class Cube;
    
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
    void render(View view){
        //hr stack overflow
        int i = 0;
        for(i = 0; i < this->complex.size(); ++i){
            this->complex.at(i).render(view,1.0f);  
        }
    }
    friend std::ostream& operator<<(std::ostream& os, Complex complex){
        for(auto it = begin(complex.complex); it != end(complex.complex); ++it){
            os << *it << std::endl;
        }
        return os;
    }

    public:
    static void renderAll(View view){
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
            //Back
            this->push_back(Simplex(_size*e3, _size*(e1+e3), _size*(e1+e2+e3), vmi::Color::Magenta));
            this->push_back(Simplex(_size*e3, _size*(e2+e3), _size*(e1+e2+e3), vmi::Color::Magenta));
            //Left Side
            this->push_back(Simplex(O, _size*e3, _size*(e2+e3), vmi::Color::Yellow));
            this->push_back(Simplex(O, _size*e2, _size*(e2+e3), vmi::Color::Yellow));
            // //Right Side
            // this->push_back(Simplex(_size*e1, _size*(e1+e3), _size*(e1+e2+e3), vmi::Color::Yellow));
            // this->push_back(Simplex(_size*e1, _size*(e1+e2), _size*(e1+e2+e3), vmi::Color::Yellow));
            //Top
            this->push_back(Simplex(_size*e2, _size*(e1+e2), _size*(e1+e2+e3), vmi::Color::Blue));
            this->push_back(Simplex(_size*e2, _size*(e2+e3), _size*(e1+e2+e3), vmi::Color::Blue));
            //Bottom
            this->push_back(Simplex(O, _size*(e1), _size*(e1+e3), vmi::Color::Blue));
            this->push_back(Simplex(O, _size*(e3), _size*(e1+e3), vmi::Color::Blue));
            //Front
            this->push_back(Simplex(O, _size*e1, _size*(e1+e2), vmi::Color::Magenta));
            this->push_back(Simplex(O, _size*e2, _size*(e1+e2), vmi::Color::Magenta));
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
    const static vmi::Key U = vmi::Key::W;
    const static vmi::Key D = vmi::Key::S;
    const static vmi::Key F = vmi::Key::Q;
    const static vmi::Key B = vmi::Key::E;
    static Player* const self;

    public:
    Player() : Cube(20){
        Matrix_h T = Translation(0.0f,0.0f,100.0f);
        this->operator*(T);
    }

    static void move(float dt, float speed){
        if(vmi::Game::isKeyPressed(R)){
            Matrix_h T = Translation(dt*speed, 0.0f, 0.0f);
            self->operator*(T);
        }
        if(vmi::Game::isKeyPressed(L)){
            Matrix_h T = Translation(-dt*speed, 0.0f, 0.0f);
            self->operator*(T);

        }
        if(vmi::Game::isKeyPressed(D)){
            Matrix_h T = Translation(0.0f, dt*speed, 0.0f);
            self->operator*(T);
        }
        if(vmi::Game::isKeyPressed(U)){
            Matrix_h T = Translation(0.0f, -dt*speed, 0.0f);
            self->operator*(T);

        }
        if(vmi::Game::isKeyPressed(F)){
            Matrix_h T = Translation(0.0f, 0.0f, dt*speed);
            self->operator*(T);
        }
        if(vmi::Game::isKeyPressed(B)){
            Matrix_h T = Translation(0.0f, 0.0f, -dt*speed);
            self->operator*(T);
        }

        if(vmi::Game::isKeyPressed(vmi::Key::LAlt)){
            if(vmi::Game::isMouseButtonPressed(vmi::MouseButton::Left)){
                Matrix_h R = Rotation_z(dt);
                self->operator*(R);
            }
            if(vmi::Game::isMouseButtonPressed(vmi::MouseButton::Right)){
                Matrix_h R = Rotation_z(-dt);
                self->operator*(R);
            }
        }

        if(vmi::Game::isKeyPressed(vmi::Key::Left)){
            Matrix_h R = Rotation_y(dt);
            self->operator*(R);
        }
        if(vmi::Game::isKeyPressed(vmi::Key::Right)){
            Matrix_h R = Rotation_y(-dt);
            self->operator*(R);
        }

        if(vmi::Game::isKeyPressed(vmi::Key::Up)){
            Matrix_h R = Rotation_x(dt);
            self->operator*(R);
        }
        if(vmi::Game::isKeyPressed(vmi::Key::Down)){
            Matrix_h R = Rotation_x(-dt);
            self->operator*(R);
        }
    }
};

class Floor: public Complex{
    
    public:
    Floor(float _size){
    Matrix_h T = Translation(0.0f,0.0f,100.0f);
    this->push_back(Simplex(O, _size*(e1), _size*(e1+e3), vmi::Color::White));
    this->push_back(Simplex(O, _size*(e3), _size*(e1+e3), vmi::Color::White));
    this->operator*(T);
    }
};

class Game : public vmi::Game{
    private:
    View& view; 
    public:
        Game(int _width, int _height, View& _view) : vmi::Game("3D Game", _width, _height), view(_view){
            //Intetionly left blank
        }
        void update(double dt){
            dt = (float) dt;
            Player::move(dt, 20.0f);
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