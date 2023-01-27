#ifndef WILDPOKEMON_H
#define	WILDPOKEMON_H
#include <iostream>
#include <string>
using namespace std;

#include "Trainer.h"
#include "GameObject.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "Point2D.h"


enum WildPokemonStates 
{
    IN_ENVIRONMENT = 0,
    DEAD = 1,
    IN_TRAINER = 2
};

class WildPokemon : public GameObject
{
    public:
        WildPokemon(string, double, double, bool, int, Point2D);
        void follow(Trainer* t);
        bool get_variant();
        double get_attack();
        double get_health();
        bool get_in_combat();
        bool Update();
        void ShowStatus();
        bool IsAlive();
        bool ShouldBeVisible();
        bool EncounterTrainer();
        Trainer* get_Trainer();

    protected:
        double attack = 5;
        double health = 2;
        bool variant;
        bool in_combat;
        string name;
        Trainer* current_trainer;
        
};


#endif