#include <iostream>

#include "PokemonGym.h"

// Default pokemon gym constructor
PokemonGym::PokemonGym()
    : Building()
{
    display_code = 'G';
    state = NOT_DEFEATED;
    max_number_of_battles = 10;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = 1;
    PokeDollar_cost_per_battle = 1.0;
    experience_per_battle = 2;
    cout << "PokemonGym default constructed" << endl;
}
// Construct a new pokemon gym
PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, double 
PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc)
    : Building('G', in_id, in_loc)
{
    id_num = in_id;
    max_number_of_battles = max_battle;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = health_loss;
    experience_per_battle = exp_per_battle;
    PokeDollar_cost_per_battle = PokeDollar_cost;
    cout << "PokemonGym constructed" << endl;
}
//Destruct Pokemon Center
PokemonGym::~PokemonGym()
{
    cout << "PokemonGym destructed" << endl;
}

// Public Member Functions
double PokemonGym::GetPokeDollarCost(unsigned int battle_qty)
{
    return PokeDollar_cost_per_battle * battle_qty;
}
unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty)
{
    return health_cost_per_battle * battle_qty;
}
unsigned int PokemonGym::GetNumBattlesRemaining()
{
    return num_battle_remaining;
}
bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health)
{
    // trainer has enough money and enough health
    if (budget >= PokeDollar_cost_per_battle*battle_qty && health >= health_cost_per_battle*battle_qty)
    {
        return true;
    }
    else // trainer does not have enough money or health
    {
        return false;
    }
}
unsigned int PokemonGym::TrainPokemon(unsigned int battle_units)
{
    if (num_battle_remaining >= battle_units)
    {
        num_battle_remaining -= battle_units;
        return battle_units * experience_per_battle;
    }
    else 
    {
        return num_battle_remaining * experience_per_battle;
    }
}
unsigned int PokemonGym::GetExperiencePerBattle()
{
    return experience_per_battle;
}
//Update the pokemon gym
bool PokemonGym::Update()
{
    if (num_battle_remaining == 0)
    {
        state = DEFEATED;
        display_code = 'g';
        cout << display_code << " " << id_num << "has been beaten" << endl;
        num_battle_remaining = -1;
        return true;
    }
    else
    {
        return false;
    }
}
// return if the gym has been passed
bool PokemonGym::passed()
{
    if (num_battle_remaining == 0) // if no battles remaining gym passed
    {
        return true;
    }
    else // gym is not passed
    {
        return false;

    }
}
//Status of the pokemon gym
void PokemonGym::ShowStatus()
{
    cout << "PokemonGym Status: ";
    Building::ShowStatus();
    cout << "Max number of battles: " << max_number_of_battles << endl;
    cout << "Health cost per battle: " << health_cost_per_battle << endl;
    cout << "PokeDollar per battle: " << PokeDollar_cost_per_battle << endl;
    cout << "Experience per battle: " << experience_per_battle << endl;
    cout << num_battle_remaining << " battle(s) are remaining for this PokemonGym" << endl;
}
