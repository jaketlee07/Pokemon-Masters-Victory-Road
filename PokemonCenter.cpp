#include <iostream>

#include "PokemonCenter.h"

// Default Pokemon center constructor
PokemonCenter::PokemonCenter()
    : Building()
{
    display_code = 'C';
    potion_capacity = 100;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter default constructed" << endl;
}
//Construct a new Pokemon Center
PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc)
    : Building('C', in_id, in_loc)
{
    id_num = in_id;
    potion_capacity = potion_cap;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = potion_cost;
    cout << "PokemonCenter constructed" << endl;
    state = POTIONS_AVAILABLE;
}
//Destruct Pokemon Center
PokemonCenter::~PokemonCenter()
{
    cout << "PokemonCenter destructed" << endl;
}

// return if the pokemon center has potions left
bool PokemonCenter::HasPotions()
{
    if (num_potions_remaining >= 1) // there is 1 or more potion in the center
    {
        return true;
    }
    else // there are no more potions in the center
    {
        return false;
    }
}
// Return the number of potions remaining at the center
unsigned int PokemonCenter::GetNumPotionRemaining()
{
    return num_potions_remaining;
}
// return if the trainer can afford the requested amount of potions
bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget)
{
    if (potion * pokedollar_cost_per_potion < budget)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// return the cost of the requested amount of potioins
double PokemonCenter::GetPokeDollarCost(unsigned int potion)
{
    return potion * pokedollar_cost_per_potion;
}
// distribute the potions from the center to the trainer
unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed)
{
    if(num_potions_remaining >= potion_needed)
    {
        num_potions_remaining -= potion_needed;
        return potion_needed;
    }
    else
    {
        unsigned int remaining = num_potions_remaining;
        num_potions_remaining = 0;
        return remaining;
    }
}

bool PokemonCenter::Update()
{
    if(num_potions_remaining == 0)
    {
        state = NO_POTIONS_AVAILABLE;
        display_code = 'c';
        cout << "PokemonCenter " << id_num << " has ran out of potions" << endl;
        num_potions_remaining = -1;
        return true;
    }
    else
    {
        return false;
    }
}
void PokemonCenter::ShowStatus()
{
    cout << "PokemonCenter Status: ";
    Building::ShowStatus();
    cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << endl;
    cout << "has " << num_potions_remaining << " potion(s) remainming." << endl;
}