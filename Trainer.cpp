#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>     /* time */
#include <math.h>

#include "Trainer.h"
#include "Vector2D.h"
#include "Point2D.h"

// Default Trainer constructor
Trainer::Trainer()
    : GameObject('T')
{
    speed = 5;
    cout << "Trainer default constructed." << endl;
}

// Construct new trainer object
Trainer::Trainer(char in_code)
    : GameObject(in_code)
{
    speed = 5;
    cout << "Trainer constructed." << endl;

    state = STOPPED;
    display_code = in_code;
}
// Construct new trainer object
Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
    : GameObject(in_loc, in_id, in_code)
{
    speed = in_speed;
    name = in_name;

    cout << "Trainer constructed" << endl;
}
//Destruct Trainer
Trainer::~Trainer()
{
    cout << "Trainer destructed" << endl;
}

// Begin moving the gym
void Trainer::StartMoving(Point2D dest)
{
    // Set destination to given point

    //If trainer was at center/gym remove the trainer from the center/gym
    if (state == AT_CENTER)
    {
        currrent_center->RemoveOneTrainer();
    }
    else if (state == IN_GYM)// if trainer is in gym remove from gym 
    {
        current_gym->RemoveOneTrainer();
    }

    // Check trainers location or state
    if (dest.x == GetLocation().x && dest.y == GetLocation().y) // trainer is already at given location
    {
        cout << display_code << GetId() << ": I'm already there See?" << endl;
        state = STOPPED;
    }
    else if (this->HasFainted()) // trainer is fainted
    {
        cout << display_code << GetId() << ": My pokemon have fainted. I may move but you cannot see me." << endl;
        state = FAINTED;
    }
    else // trainer moves
    {
        cout << display_code << GetId() << ": On my way." << endl;
    }

    SetupDestination(dest);
    state = MOVING;
}

// Begin moving trainer to the gym
void Trainer::StartMovingToGym(PokemonGym* gym)
{

    // Set destination to gym
    SetupDestination(gym->GetLocation());

    if (state == AT_CENTER) // if trainer is in center remove from center
    {
        currrent_center->RemoveOneTrainer();
    }

    // Check states
    if (this->HasFainted())// trainer is fainted
    {
        cout << display_code << id_num << ": My Pokemon have fainted so I can't move to gym..." << endl;
        state = FAINTED;
    }
    else if (state == IN_GYM) // trainer is already in the gym
    {
        cout << display_code << id_num << ": I am already at the PokemonGym!"; 
    }
    else // move trainer to gym
    {
        // set state of trainer to MOVING_TO_GYM
        state = MOVING_TO_GYM;
        current_gym = gym;
        cout << display_code << id_num << ": on my way to gym " << current_gym->GetId() << endl;
    }
}
// Begin moving trainer to the center
void Trainer::StartMovingToCenter(PokemonCenter* center)
{

    //Set destination to Center
    SetupDestination(center->GetLocation());

    if (state == IN_GYM)
    {
        current_gym->RemoveOneTrainer();
    }
    
    // Check states 
    if (this->HasFainted())
    {
        cout << display_code << id_num << ": My Pokemon have fainted I should have gone to the center..." << endl;
        state = FAINTED;
    }
    else if (state == AT_CENTER)
    {
        cout << display_code << id_num << ": I am already at the Center!" << endl; 
    }
    else
    {
        // set state of trainer to MOVING_TO_CENTER
        state = MOVING_TO_CENTER;
        currrent_center = center;
        cout << display_code << id_num << ": On my way to Center " << currrent_center->GetId() << endl;
    }

}
void Trainer::StartBattling(unsigned int num_battles)
{
    battles_to_buy = num_battles;
    PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();

    if (this->HasFainted()) // fainted trainer
    {
        cout << display_code << id_num << ": My Pokemon have fainted so no more battles for me..." << endl;
    }
    else if (state != IN_GYM) // trainer is not in gym
    {
        cout << display_code << id_num << ": I can only battle in a PokemonGym!" << endl;
    }
    else if (current_gym->GetPokeDollarCost(num_battles) > PokeDollars) // trainer doesnt have enough money
    {
        cout << display_code << id_num << ": Not enough money for battles" << endl;
    }

    else if (current_gym->GetNumBattlesRemaining() < 1 || current_gym->passed()) // trainers has completed all of the battles
    {
        cout << display_code << id_num << ": Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
    }
    else // else proceed to battling gym
    {
        state = BATTLING_IN_GYM;
        cout << display_code << ": Started to battle at the PokemonGym " << current_gym->GetId() << " with " << num_battles << " battles." << endl;

    }

    if(battles_to_buy > current_gym->GetNumBattlesRemaining()) // if trying to battle more battles than available set the battles to the remaining amount
    {
        battles_to_buy = current_gym->GetNumBattlesRemaining();
    }


}
//Start recovering trainer health
void Trainer::StartRecoveringHealth(unsigned int num_potions)
{
    if (currrent_center->CanAffordPotion(num_potions, PokeDollars) == false) // check if trainer has enough money
    {
        cout << display_code << id_num << ": Not enough money to recover health" << endl;
    }
    else if (currrent_center->GetNumPotionRemaining() < 1) // check if center has potions left
    {
        cout << display_code << id_num << ": Cannot recover! No potion remaining in this Pokemon Center." << endl;
    }
   else if (state != AT_CENTER) // check if trainer is at center
    {
       cout << display_code << id_num << ": I can only recover health at a Pokemon Center" << endl;
    }
    else // else proceed and recover health
    {
        state = RECOVERING_HEALTH;
        cout << display_code << id_num << ": Started recovering " << num_potions << " potions at PokemonCenter " << currrent_center->GetId() << endl;
        potions_to_buy = num_potions;
        health += (potions_to_buy*5);
        potions_to_buy = currrent_center->DistributePotion(num_potions);
    }
}
// stop trainer from moving
void Trainer::Stop()
{
    state = STOPPED;
    cout << display_code << id_num << ": Stopping..." << endl;
}
//return if trainer is fainted
bool Trainer::HasFainted()
{
    if (health == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}   
// return if trainer is visible
bool Trainer::ShouldBeVisible()
{
    if (this->HasFainted()) // if trainer has fainted they are not visible
    {
        return false;
    }
    else
    {
        return true;
    }
}
//Show status of the trainer
void Trainer::ShowStatus()
{
    cout << name << " status: ";
    GameObject::ShowStatus();

    switch(state)
    {
        case STOPPED: // STOPPED
        {
            cout << " stopped" << endl;
            break;
        }
        case MOVING: // MOVING
        {
            cout << " moving at a speed of " << speed << " to destination " << location << " at each step of " << delta << endl;
            break;
        }
        case FAINTED: // FAINTED
        {
            cout << " your trainer has fainted. " << endl;
            break;
        }
        case AT_CENTER: // AT_CENTER
        {
            cout << " inside PokemonCenter " << currrent_center->GetId() << endl;
            break;
        }
        case IN_GYM: // IN_GYM
        {
            cout << " inside PokemonGym " << current_gym->GetId() << endl;
            break;
        }
        case MOVING_TO_CENTER: // MOVING_TO_CENTER
        {
            cout << " heading to Pokemon Center " << currrent_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        }
        case MOVING_TO_GYM: // MOVING_TO_GYM
        {
            cout << " heading to PokemonGym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        }
        case BATTLING_IN_GYM: // BATTLING_IN_GYM
        {
            cout << " battling in PokemonGym " << current_gym->GetId() << endl;
            break;
        }
        case RECOVERING_HEALTH: // RECOVERING_HEALTH
        {
            cout << " recovering health in Pokemon Center " << currrent_center->GetId() << endl;
            break;
        }
    }
}
//update the stats of the trainer
bool Trainer::Update()
{
    switch(state)
    {
        case STOPPED: // STOPPED
        {
            cout << endl << name << "Stats" << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;

            return false;
            break;
        }
        case MOVING: // MOVING
        {

            if (UpdateLocation())
            {
                cout << endl << name << "Stats" << endl;
                cout << "Health: " << health << endl;
                cout << "PokeDollars: " << PokeDollars << endl;
                cout << "Experience: " << experience << endl;


                state = STOPPED;
                return true;
                break;
            }
            else
            {
                cout << endl << name << "Stats" << endl;
                cout << "Health: " << health << endl;
                cout << "PokeDollars: " << PokeDollars << endl;
                cout << "Experience: " << experience << endl;

                /*if(state == AT_CENTER)//if trainer is leaving center remove trainer
                {
                    currrent_center->RemoveOneTrainer();
                }

                if(state == IN_GYM)//if trainer is leaving gym remove trainer
                {
                    current_gym->RemoveOneTrainer();
                }*/

                state = MOVING;
                return false;
                break;
            }
        }
        case FAINTED:
        {
            cout << endl << name << "fainted, they can't move" << endl;
            return false;
            break;
        }
        case AT_CENTER: // AT_CENTER
        {
            cout << endl << name << "Stats" << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;

            return false;
            break;
        }
        case IN_GYM: // IN_GYM
        {
            cout << endl << name << "Stats" << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;

            return false;
            break;
        }
        case MOVING_TO_CENTER: // MOVING_TO_CENTER
        {

            
            if (UpdateLocation())// if at center 
            {
                cout << endl << name << "Stats" << endl;
                cout << "Health: " << health << endl;
                cout << "PokeDollars: " << PokeDollars << endl;
                cout << "Experience: " << experience << endl;
                cout << "AT CENTER" << endl;

                // add one trainer to center
                currrent_center->AddOneTrainer();

                state = AT_CENTER;
                return true;
                break;
            }
            else
            {
                cout << endl << name << "Stats" << endl;
                cout << "Health: " << health << endl;
                cout << "PokeDollars: " << PokeDollars << endl;
                cout << "Experience: " << experience << endl;


                state = MOVING_TO_CENTER;
                return false;
                break;
            }
        }
        case MOVING_TO_GYM: // MOVING_TO_GYM
        {
            /*if(state == AT_CENTER)//if trainer is leaving center remove trainer
            {
                currrent_center->RemoveOneTrainer();
            }*/

            
            if (UpdateLocation())// if at gym
            {
                cout << endl << name << "Stats" << endl;
                cout << "Health: " << health << endl;
                cout << "PokeDollars: " << PokeDollars << endl;
                cout << "Experience: " << experience << endl;
                cout << "AT GYM" << endl;

                // add one trainer to gym
                current_gym->AddOneTrainer();

                state = IN_GYM;
                return true;
                break;
            }
            else
            {
                cout << endl << name << "Stats" << endl;
                cout << "Health: " << health << endl;
                cout << "PokeDollars: " << PokeDollars << endl;
                cout << "Experience: " << experience << endl;

                state = MOVING_TO_GYM;
                return false;
                break;
            }
        }
        case BATTLING_IN_GYM: // BATTLING_IN_GYM
        {
            // Number of battles remaining in the gym
            int numBattles = current_gym->GetNumBattlesRemaining();

            // Reduce trainer health based on total health cost for the current gym request
            health -= current_gym->GetHealthCost(battles_to_buy);

            // Reduce the amount of PokeDollars based on the dollar cost for the current gym request
            PokeDollars -= current_gym->GetPokeDollarCost(battles_to_buy);

            // Increase Trainer experience based on experience gain for the current gym request
            int gainedExp = current_gym->TrainPokemon(battles_to_buy);
            experience += gainedExp;

            // Print 
            cout << "** " << name << " completed " << battles_to_buy << " battle(s)! **" << endl;
            cout << "** " << name << " gained " << gainedExp << " experience! **" << endl;

            cout << endl << name << " Stats" << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;

            state = IN_GYM;
            return true;
            break;
        }
        case RECOVERING_HEALTH: // RECOVERING_HEALTH
        {
            // Decrease trainer's pokedollars by the cost of potions
            PokeDollars -= currrent_center->GetPokeDollarCost(potions_to_buy);

            // Print
            cout << "** " << name << " recovered " << potions_to_buy*5 << " health! **" << endl;
            cout << "** " << name << " bought " << potions_to_buy << " potion(s) **" << endl;

            cout << endl << name << " Stats" << endl;
            cout << "Health: " << health << endl;
            cout << "PokeDollars: " << PokeDollars << endl;
            cout << "Experience: " << experience << endl;

            state = AT_CENTER;
            return true;
            break;

        }
    }
    
}
//Update the trainers location
bool Trainer::UpdateLocation()
{
    if(health <= 1) // trainers health is too low
    {
        health = 0;
        state = FAINTED;
    }
    else // remove 1 health from trainers health
    {
        health--;
    }

    // for(int i = 0; i < wild_num; i++)
    // {
        
    // }

    // Give trainer random amount of pokedollars
    PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();

    int my_id = GetId();
    bool inOneStep = (fabs(destination.x-location.x) <= fabs(delta.x)) && (fabs(destination.y - location.y) <= fabs(delta.y)); 
	if (inOneStep) // if the trainer is within one step from destination
	{
		location = destination;
		cout << display_code << my_id << ": I'm there!" << endl;
        
		return true;
	}
	else // update new location based on the step "delta"
	{
		location = location + delta;
		return false;
	}

}

// Setup the destination of the trainer
void Trainer::SetupDestination(Point2D dest)
{
    destination = dest;
	delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

// Return the trainers name
string Trainer::GetTrainerName()
{
    return name;
}

void Trainer::setWildNum(bool wild)
{
    if(wild)
    {
        wild_num++;
    }
    else
    {
        wild_num--;
    }
}

void Trainer::WildPokemonAttack(double attack)
{
    health -= attack;
}

// Return a random value for the Pokedollars from 0.0 - 2.0
static double GetRandomAmountOfPokeDollars()
{
    double randAmount = ((double)rand()) / RAND_MAX;
    double num = 2.0 * randAmount;
    return num;
}





