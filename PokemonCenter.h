#ifndef POKEMONCENTER_H
#define	POKEMONCENTER_H
#include <iostream>

#include "Point2D.h"
#include "Building.h"
#include "GameObject.h"

enum PokemonCenterStates
{
    POTIONS_AVAILABLE = 0,
    NO_POTIONS_AVAILABLE = 1
};

class PokemonCenter : public Building
{
    private:
        unsigned int potion_capacity;
        unsigned int num_potions_remaining;
        double pokedollar_cost_per_potion;

    public:
        PokemonCenter();
        PokemonCenter(int, double, unsigned int, Point2D);
        ~PokemonCenter();

        bool HasPotions();
        unsigned int GetNumPotionRemaining();
        bool CanAffordPotion(unsigned int, double);
        double GetPokeDollarCost(unsigned int);
        unsigned int DistributePotion(unsigned int);
        bool Update();
        void ShowStatus();
};


#endif