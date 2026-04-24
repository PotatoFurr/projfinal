#include <Color.hpp>
#include <Thing.hpp>
#include <PolygonShape.hpp>
#include <Vector2d.hpp>
#include <Game.hpp>

class Game : public vmi::Game{
    public:
        Game(int _width, int _height) : vmi::Game("3D Game", _width, _height){
            //Intetionly left blank
        }
        void update(double dt){
        }
};
class Vector3D_h{
    private:
    float x;
    float y;
    float z;
    float w;

    void perspective_division(){
        if(this->w == 0){
            return;
        }
        this->x = this->x / this->w;
        this->y = this->y / this->y;
        this->z = this->z / this->z;
        this->w = 1.0f;
    }

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
        return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z + V1.w+V2.w;
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


};
#define e1 Vector3D_h(1,0,0,1)
#define e2 Vector3D_h(0,1,0,1)
#define e3 Vector3D_h(0,0,1,1)
#define O Vector3D_h(0,0,0,1)

class Matrix_h{
    private:
    Vector3D_h r1;
    Vector3D_h r2;
    Vector3D_h r3;
    Vector3D_h r4;

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
        return Vector3D_h(
            M.r1*V,
            M.r2*V,
            M.r3*V,
            M.r4*V
        );
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
        Vector3D_h(0.0f,0.0f,0.0f,V[0]),
        Vector3D_h(0.0f,0.0f,0.0f,V[1]),
        Vector3D_h(0.0f,0.0f,0.0f,V[2]),
        Vector3D_h(0.0f,0.0f,0.0f,1.0f)){
            //intetionly left blank
        }
    Translation(float x, float y, float z): Matrix_h(
        Vector3D_h(0.0f,0.0f,0.0f,x),
        Vector3D_h(0.0f,0.0f,0.0f,y),
        Vector3D_h(0.0f,0.0f,0.0f,z),
        Vector3D_h(0.0f,0.0f,0.0f,1)){
            //intetionly left blank
        }

};

class View{
    private:
    int width; /// window width
    int height; /// window height
    Matrix_h cameraMatrix; // holds the maipulation of the world so new objects can have it applied and tracked
    Matrix_h projectionMatrix; /// changex with the with and height
    friend class Renderable;
    friend class Simplex;

    public:
    void updateProjection(){
        projectionMatrix = Matrix_h(
            Vector3D_h(1,0,0,0),
            Vector3D_h(0,1,0,0),
            Vector3D_h(0,0,1,0),
            Vector3D_h(0,0,1,0)
        );

    }

    View(int _w, int _h): width(_w), height(_h){
    //intentionly left blank
    }

    void transform(Matrix_h M){
        M * cameraMatrix;
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

    friend Simplex operator*(Matrix_h M, Simplex simplex){
        return Simplex(
        M*simplex.V1,
        M*simplex.V2,
        M*simplex.V3,
        simplex.color);
        
    }

    void render(View view, float _scale){
        if(img == nullptr){
            img = new Renderable(view);
        }
        if(img->getShape() != nullptr){
            delete img->getShape();
        }
        img->scale =_scale;
        vmi::PolygonShape* shape = new vmi::PolygonShape();
        //projects the matrix down to 2d
        Simplex S = view.projectionMatrix*(*this);

        //creates the shape for vmi engine to render 
            shape->addPoint({S.V1.x,S.V1.y});
            shape->addPoint({S.V2.x,S.V2.y});
            shape->addPoint({S.V3.x,S.V3.y});
            shape->setFill(color);

        //Sets the renderables shape
        img->setShape(shape);
    }

    friend std::ostream& operator<<(std::ostream& os, Simplex S){
        os << "{" <<  S.V1 << ", " << S.V2 << ", " << S.V3 << "}";
        return os;
    }


};