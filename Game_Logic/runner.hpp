#pragma once

#include "3dEngine.hpp"

#include "lane.hpp"
#include <Keyboard.hpp>
#include "LANE.h"


class Runner : public Complex
{
    public:
        Runner(const Key A, const Key D) : Vector3D_h(), Lane(L2), score(0.0), A(A), D(D)/*fix this: add constructor to lane and make it so number given is what lane player is put in. */ 
        {

            //construct complex of runner, assign x,y,z value

            //just basic box for pm
            vector<Simplex> comlpxmodel = {
            ((0,5,0), (5,5,0), (5,5,5)), ((0,5,0), (0,5,5), (5,5,5)), 
            ((5,5,0), (5,0,0), (5,0,5)), ((5,5,0), (5,5,5), (5,0,5)),
            ((0,0,0), (0,5,5), (5,0,5)), ((0,0,0), (0,0,5), (5,0,5)),
            ((0,0,5), (0,5,5), (5,5,5)), ((0,0,5), (5,0,5), (5,5,5)),
            ((0,0,0), (0,5,0), (5,5,0)), ((0,0,0), (0,5,5), (5,5,0)),
            }
            Complex(comlpxmodel);

        };

        ~Runner()
        {

            delete player;
            delete comlpxmodel;
            

        };

        const Runner* getPlayer() const 
        {

            return player;

        };

        void is_colliding(const Complex* other)
        {



        };

        float GetScore() const
        {

            return score;

        };

        

        void move()
        {
            //moving left
            if (((Game::isKeyPressed(Key::A)) || (Game::isKeyPressed(Key::A))) && (player->GetLane() == L2)) {
                player->ChangeLane(L1);
            };

            if (((Game::isKeyPressed(Key::A)) || (Game::isKeyPressed(Key::A))) && (player->GetLane() == L3)) {
                player->ChangeLane(L2);
            };

            //moving right
            if (((Game::isKeyPressed(Key::D)) || (Game::isKeyPressed(Key::D))) && (player->GetLane() == L1)) {
                player->ChangeLane(L2);
            };

            if (((Game::isKeyPressed(Key::D)) || (Game::isKeyPressed(Key::D))) && (player->GetLane() == L2)) {
                player->ChangeLane(L3);
            };
    

        };


    private:

        bool alive;
        float score;

        Key A;
        Key D;


        float IncScore(double dt) const
        {

            score = (dt * 0.1);

        };
};