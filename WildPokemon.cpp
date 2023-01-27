#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>     /* time */
#include <math.h>

#include "Trainer.h"
#include "Vector2D.h"
#include "Point2D.h"
#include "WildPokemon.h"
#include "GameObject.h"

using namespace std;


WildPokemon::WildPokemon(string in_name, double in_attack, double in_health, bool in_variant, int in_id, Point2D in_loc)
    : GameObject(in_loc, in_id, 'W')
{
    state = IN_ENVIRONMENT;
    name = in_name;
    attack = in_attack;
    health = in_health;
    variant = in_variant;
    id_num = in_id;
    location = in_loc;
    in_combat = false;
    current_trainer = NULL;
    cout << "Wild Pokemon Constructed" << endl;
}

void WildPokemon::follow(Trainer* t)
{
    if (t != 0)
    {
        current_trainer = t;
        state = IN_TRAINER;
        in_combat = true;
    }
    else
    {
        cout << "That is not a trainer" << endl;
    }
}
bool WildPokemon::get_variant()
{
    return variant;
}
double WildPokemon::get_attack()
{
    return attack;
}
double WildPokemon::get_health()
{
    return health;
}
bool WildPokemon::get_in_combat()
{
    return in_combat;
}
bool WildPokemon::ShouldBeVisible()
{
    if (state == FAINTED) // if trainer has fainted they are not visible
    {
        return false;
    }
    else
    {
        return true;
    }
}

//bool EncounterTrainer::
bool WildPokemon::Update()
{
    if(current_trainer != 0)
    {
        state = IN_TRAINER;

        double location_x = location.x;
        double location_y = location.y;

        location.x = current_trainer->GetLocation().x;
        location.y = current_trainer->GetLocation().y;

        if(this->IsAlive())
        {
            current_trainer->WildPokemonAttack(get_attack());
        }

        if(health < 1)
        {
            health = 0;
            state = DEAD;
        }
        else
        {
            health--;
        }
    }
    else
    {
        state = IN_ENVIRONMENT;
    }
}
void WildPokemon::ShowStatus()
{
    cout << "WildPokemon status: " ;
    GameObject::ShowStatus();

    switch (state)
    {
        case IN_ENVIRONMENT:
        {
            cout << " is in the environment" << endl;
            cout << "\t Health: " << get_health() << endl;
            cout << "\t Attack: " << get_attack() << endl;
            cout << "\t Variant: " << get_variant() << endl;
            break;
        }
        case DEAD:
        {
            cout << " Pokemon has fainted" << endl;
            cout << "\t Health: " << get_health() << endl;
            cout << "\t Attack: " << get_attack() << endl;
            cout << "\t Variant: " << get_variant() << endl;
            break;
        }
        case IN_TRAINER:
        {
            cout << " is following trainer" << current_trainer->GetId() << endl;
            cout << "\t Health: " << get_health() << endl;
            cout << "\t Attack: " << get_attack() << endl;
            cout << "\t Variant: " << get_variant() << endl;
            cout << "\t In Combat With Trainer: " << current_trainer->GetTrainerName() << endl;
            break;
        }
    }
}
bool WildPokemon::IsAlive()
{
    if (health == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Trainer* WildPokemon::get_Trainer()
{
    return current_trainer;
}
