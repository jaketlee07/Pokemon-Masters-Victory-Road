#ifndef TRAINER_H
#define	TRAINER_H
#include <iostream>
#include <string>
using namespace std;

#include "GameObject.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "Point2D.h"
// #include "WildPokemon.h"


enum TrainerStates 
{
    STOPPED = 0,
    MOVING = 1,
    FAINTED = 2,
    AT_CENTER = 3,
    IN_GYM = 4,
    MOVING_TO_CENTER = 5,
    MOVING_TO_GYM = 6,
    BATTLING_IN_GYM = 7,
    RECOVERING_HEALTH = 8
};

class Trainer : public GameObject
{
    public:
        Trainer();
        Trainer(char);
        Trainer(string, int, char, unsigned int, Point2D);
        ~Trainer();

        void StartMoving(Point2D);
        void StartMovingToGym(PokemonGym*);
        void StartMovingToCenter(PokemonCenter*);
        void StartBattling(unsigned int);
        void StartRecoveringHealth(unsigned int);
        void Stop();
        bool HasFainted();
        bool ShouldBeVisible();
        void ShowStatus();
        bool Update();
        string GetTrainerName();
        void setWildNum(bool);
        void WildPokemonAttack(double);

        bool HasPokemon;
    
    protected:
        bool UpdateLocation();
        void SetupDestination(Point2D);

    private:
        double speed;
        bool is_at_center;
        bool is_IN_GYM;
        unsigned int health = 20;
        unsigned int experience = 0;
        double PokeDollars = 0;
        unsigned int battles_to_buy = 0;
        unsigned int potions_to_buy = 0;
        string name;
        int wild_num;
        PokemonCenter* currrent_center = NULL;
        PokemonGym* current_gym = NULL;
        //WildPokemon* current_wildpokemon = NULL;
        Point2D destination;
        Vector2D delta;
};

static double GetRandomAmountOfPokeDollars();

#endif
