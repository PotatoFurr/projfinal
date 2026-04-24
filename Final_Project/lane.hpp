#include "3dEngine.hpp"
#include "Movement.hpp"
#include "Vector3d.hpp"
#include "VertexSets.hpp"
#include "VMIGameInterface.hpp"
#include "obstacles.hpp"
#include "runner.hpp"

using namespace Krec;

enum lan
{

    L1 = 1,
    L2 = 2,
    L3 = 3

};

class Lane
{
    public:
        Lane(lan slane) : slane(slane) //for player, will make slane two
        {

            

        };

        Lane() //for obstacles, will randomize lane 
        {

            

        };
    
        ~Lane()
        {

            delete slane;

        };

        lan GetLane()
        {

            return curlane;

        };

        lan ChangeLane(lan inp)
        {

            return inp;

        };

    private:

        lan slane;

};