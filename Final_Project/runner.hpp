#include "3dEngine.hpp"
#include "Movement.hpp"
#include "Vector3d.hpp"
#include "VertexSets.hpp"
#include "VMIGameInterface.hpp"
#include "lane.hpp"
#include <Keyboard.hpp>

using namespace Krec;
using namespace vmi;

enum lan
{

    L1 = 1,
    L2 = 2,
    L3 = 3

};

class Runner : public Complex
{
    public:
        Runner(const Key upKey, const Key downKey) : Vector3d(), Lane(2), score(0.0), upKey(upKey), downKey(downKey)/*fix this: add constructor to lane and make it so number given is what lane player is put in. */ 
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
            playermodel = new Complex(comlpxmodel)

        };

        ~Runner()
        {

            delete player;
            delete comlpxmodel;
            

        };

        void is_colliding(const Complex* other)
        {



        };

        float GetScore() const
        {

            return score;

        };

        

        void move(double dt)
        {

            if (((Game::isKeyPressed(Key::A)) || (Game::isKeyPressed(Key::A))) && (player->GetLane() == L2)) {
                player->ChangeLane(L1);
            };

            if (((Game::isKeyPressed(Key::A)) || (Game::isKeyPressed(Key::A))) && (player->GetLane() == L3)) {
                player->ChangeLane(L3);
            };
    

        };


    private:

        bool alive;
        float score;
        Runner player;
        Complex* playermodel;

        Key upKey;
        Key downKey;


        float IncScore(double dt) const
        {

            score = (dt * 0.1);

        };
};