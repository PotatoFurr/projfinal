#include "3dEngine.hpp"
#include "Movement.hpp"
#include "Vector3d.hpp"
#include "VertexSets.hpp"
#include "VMIGameInterface.hpp"
#include "obstacles.hpp"
#include "runner.hpp"
#include "LANE.h"

using namespace Krec;



class Lane
{
    public:
        Lane(lan slane, Runner* player) : slane(slane) //for player, will make slane two
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

            return slane;

        };

        lan ChangeLane(lan inp)
        {

            slane = inp;
            player->Vector3d(slane,400,10);
            return slane;

        };

    private:

        lan slane;
        Runner* player;

};