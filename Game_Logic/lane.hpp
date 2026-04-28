#pragma once

#include "3dEngine.hpp"
#include "obstacles.hpp"
#include "LANE.h"
#include "Movement.hpp"
#include "Vector3d.hpp"
#include "VertexSets.hpp"
#include "VMIGameInterface.hpp"
#include <vector>

using namespace Krec;


/*  
for declaration

Lane lane1 = new Lane(L1, player, 100);
Lane lane1 = new Lane(L1, player, 400); (NUMBERS NOT FINAL, JUST FOR EXAMPLE)
Lane lane1 = new Lane(L1, player, 700);




*/
class Lane
{
    public:
        Lane(char lan, Runner* player const, int xval) : player(player), lan(lan), xval(xval)
        {
                //assigns player pointer for when lane is called, will most likely use some sort of player->getLane() function
                //assigns lan with assigned lane, will be used to compare if the lane is occupied by player
                //assigns xval with what value of x is assigned with the lane

        };
    
        ~Lane()
        {

            delete player;
        };

        void handleCollision(const Thing* other)
        {
                //intentionally blank

        };

        void SpawnObj()
        {
             // now set up to create the next pipes after a delay

            rObj = ((rand() % 3) + 1);

            new Obstacle(rObj, xval);

            int delayTime = (rand() % 3) + 1;         // between 1 and 3 seconds
            Timer::createTimer(delayTime, []() { Lane::SpawnObj(); });

        };


    private:
        char lan;
        int xval;
        int rObj;
        Runner* player const;

};