#include <string>

#include "Model.h"
#include "InputHandling.h"

Model::Model()
{
    time = 0;

    Trainer* T1 = new Trainer("Ash", 1, 'T', 1, Point2D(5, 1));
    Trainer* T2 = new Trainer("Misty", 2, 'T', 2, Point2D(10, 1));
    PokemonCenter * C1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    PokemonCenter * C2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
    PokemonGym * G1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
    PokemonGym * G2 = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5, 5));
    WildPokemon * W1 = new WildPokemon("Ditto", 5, 2, false, 1, Point2D(10, 12));
    WildPokemon * W2 = new WildPokemon("Piplup", 5, 2, false, 2, Point2D(15, 5));
   
    //trainer_ptrs list
    trainer_ptrs.push_back(T1);
    trainer_ptrs.push_back(T2);

    //center_ptrs list
    center_ptrs.push_back(C1);
    center_ptrs.push_back(C2);

    //gym_ptrs list
    gym_ptrs.push_back(G1);
    gym_ptrs.push_back(G2);

    //wildpokemon_ptrs list
    wildpokemon_ptrs.push_back(W1);
    wildpokemon_ptrs.push_back(W2);

    //object_ptrs list
    object_ptrs.push_back(T1);
    object_ptrs.push_back(T2);
    object_ptrs.push_back(C1);
    object_ptrs.push_back(C2);
    object_ptrs.push_back(G1);
    object_ptrs.push_back(G2);
    object_ptrs.push_back(W1);
    object_ptrs.push_back(W2);

    //active_ptrs list
    active_ptrs.push_back(T1);
    active_ptrs.push_back(T2);
    active_ptrs.push_back(C1);
    active_ptrs.push_back(C2);
    active_ptrs.push_back(G1);
    active_ptrs.push_back(G2);
    active_ptrs.push_back(W1);
    active_ptrs.push_back(W2);

    cout << "Model default constructed" << endl;
};

// Destruct Object
Model::~Model()
{
	for (list <GameObject*>::iterator obj_it = object_ptrs.begin(); obj_it != object_ptrs.end(); obj_it++) {
        delete *obj_it;
    }

	cout << "Model destructed." << endl;
};

//Returns the pointer of the Trainer ID requested
Trainer* Model::getTrainerPtr(int id)
{
	for (list <Trainer*>::iterator obj_it = trainer_ptrs.begin(); obj_it != trainer_ptrs.end(); obj_it++) {
        if ((*obj_it) -> GetId() == id)
            return (*obj_it);
    }
    return 0;
}

//Returns the pointer of the PokemonCenter ID requested
PokemonCenter* Model::getPokemonCenterPtr(int id)
{
	for (list <PokemonCenter*>::iterator obj_it = center_ptrs.begin(); obj_it != center_ptrs.end(); obj_it++) {
        if ((*obj_it) -> GetId() == id)
            return (*obj_it);
    }
    return 0;
}

//Returns the pointer of the PokemonGym ID requested
PokemonGym* Model::getPokemonGymPtr(int id)
{
	for (list <PokemonGym*>::iterator obj_it = gym_ptrs.begin(); obj_it != gym_ptrs.end(); obj_it++) {
        if ((*obj_it) -> GetId() == id)
            return (*obj_it);
    }
    return 0;
}
//Returns the pointer of the PokemonGym ID requested
WildPokemon* Model::getWildPokemonPtr(int id)
{
	for (list <WildPokemon*>::iterator obj_it = wildpokemon_ptrs.begin(); obj_it != wildpokemon_ptrs.end(); obj_it++) {
        if ((*obj_it) -> GetId() == id)
            return (*obj_it);
    }
    return 0;
}

//Updates all objects and advances a time click
bool Model::Update()
{
    EncounterPokemon();
    time++;

	int gyms_beaten = 0;
    for (list <PokemonGym*>::iterator obj_it = gym_ptrs.begin(); obj_it != gym_ptrs.end(); obj_it++) 
    {
        if ((*obj_it) -> passed()) 
        {
            gyms_beaten++;
        }
    }
    if (gyms_beaten == gym_ptrs.size()) 
    {
        cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
        exit(0);
    }

    int dead_pokemon = 0;
    for (list <Trainer*>::iterator obj_it = trainer_ptrs.begin(); obj_it != trainer_ptrs.end(); obj_it++) 
    {
        if ((*obj_it) -> HasFainted()) 
        {
            dead_pokemon++;
        }
    }
    if (dead_pokemon == trainer_ptrs.size()) 
    {
        cout << "GAME OVER: You lose! All Trainers have fainted!" << endl;
        exit(0);
    }

    // Update all GameObjects
    for (list <GameObject*>::iterator obj_it = active_ptrs.begin(); obj_it != active_ptrs.end(); obj_it++) 
    {
        (*obj_it) -> Update();
    }

    // Find dead objects in the active_ptrs list
    vector <GameObject*> tempRemove;
    for (list <GameObject*>::iterator obj_it = active_ptrs.begin(); obj_it != active_ptrs.end(); obj_it++) 
    {
        if (!(*obj_it) -> ShouldBeVisible()) 
        {
            tempRemove.push_back(*obj_it);
            cout << "Dead object removed" << endl;
        }
    }
}

// Creates the view of the model to be output to screen
void Model::Display(View &view)
{
    view.Clear();
	cout << "Time: " << time << endl;

    for (list <GameObject*>::iterator obj_it = active_ptrs.begin(); obj_it != active_ptrs.end(); obj_it++) 
    {
        view.Plot(*obj_it);
    }

    view.Draw();
}

// prints status of all objects
void Model::ShowStatus()
{
	//outputs status of all the Game_Objects
	for (list <GameObject*>::iterator obj_it = object_ptrs.begin(); obj_it != object_ptrs.end(); obj_it++) 
    {
        (*obj_it) -> ShowStatus();
    }
}
void Model::EncounterPokemon()
{
    for (list <Trainer*>::iterator trainer_it = trainer_ptrs.begin(); trainer_it != trainer_ptrs.end(); trainer_it++)
    {
        for (list <WildPokemon*>::iterator wild_it = wildpokemon_ptrs.begin(); wild_it != wildpokemon_ptrs.end(); wild_it++)
        {
            if(GetDistanceBetween((*trainer_it)->GetLocation(), (*wild_it)->GetLocation()) <= 1.0)
            {
                if(!((*wild_it)->get_Trainer() == (*trainer_it)))
                {
                    (*wild_it)->follow(*trainer_it);
                    (*trainer_it)->setWildNum(true);
                }
            }
        }
    }
}

void Model::NewCommand(char type) 
{
    int maxbattle, healthloss, exp, id, x, y, attack, maxpotion, speed, health;
    double cost;
    string pokename, name;
    if (type == 'g' || type == 'c' || type == 't' || type == 'w') 
    {
        switch (type) 
        {
            case 'g':
                
                cout << "What are the max numbers of battles: ";
                cin >> maxbattle;
                cout << "How much health is lost per battle: ";
                cin >> healthloss;
                cout << "How much does each battle cost: ";
                cin >> cost; 
                cout << "How much experience is gained per battle: ";
                cin >> exp;
                cout << "What is the gym's id: ";
                cin >> id;
                cout << "What is the x and y coordinate of the gym: ";
                cin >> x >> y;
                for (list <PokemonGym*>::iterator obj_it = gym_ptrs.begin(); obj_it != gym_ptrs.end(); obj_it++) 
                {
                    if ((*obj_it) -> GetId() == id) 
                    {
                        throw Invalid_Input("A Pokemon Gym with that ID already exists!");
                        return;
                    }
                }
                
                if (id > 9) 
                {
                    throw Invalid_Input("ID values greater than 9 cannot be displayed on the grid. Please choose a single-digit ID");
                    return;
                } 
                else 
                {
                    gym_ptrs.push_back(new PokemonGym(maxbattle, healthloss, cost, exp, id, Point2D(x, y)));
                    object_ptrs.push_back(new PokemonGym(maxbattle, healthloss, cost, exp, id, Point2D(x, y)));
                    active_ptrs.push_back(new PokemonGym(maxbattle, healthloss, cost, exp, id, Point2D(x, y)));
                    break;
                }
            case 'c':
                
                cout << "What is the center's id: ";
                cin >> id;
                cout << "How much does it cost per potion: ";
                cin >> cost;
                cout << "How many potions does the center have: ";
                cin >> maxpotion;
                cout << "What is the x and y coordinate of the center: ";
                cin >> x >> y;


                for (list <PokemonCenter*>::iterator obj_it = center_ptrs.begin(); obj_it != center_ptrs.end(); obj_it++) 
                {
                    if ((*obj_it) -> GetId() == id) 
                    {
                        throw Invalid_Input("A Pokemon Center with that ID already exists!");
                        return;
                    }
                }

                if (id > 9) {
                    throw Invalid_Input("ID values greater than 9 cannot be displayed on the grid. Please choose a single-digit ID");
                    return;
                } else {
                    center_ptrs.push_back(new PokemonCenter(id, cost, maxpotion, Point2D(x, y)));
                    object_ptrs.push_back(new PokemonCenter(id, cost, maxpotion, Point2D(x, y)));
                    active_ptrs.push_back(new PokemonCenter(id, cost, maxpotion, Point2D(x, y)));
                    break;
                }
            case 't':
                cout << "What is the trainer's name: ";
                cin >> name;
                cout << "What is the trainer's id: ";
                cin >> id;
                cout << "What is the trainer's speed: ";
                cin >> speed;
                cout << "What is the x and y coordinate of the trainer: ";
                cin >> x >> y;
                for (list <Trainer*>::iterator obj_it = trainer_ptrs.begin(); obj_it != trainer_ptrs.end(); obj_it++) 
                {
                    if ((*obj_it) -> GetId() == id) 
                    {
                        throw Invalid_Input("A Trainer with that ID already exists!");
                        return;
                    }
                }

                if (id > 9) 
                {
                    throw Invalid_Input("ID values greater than 9 cannot be displayed on the grid. Please choose a single-digit ID");
                    return;
                }
                else 
                {
                    
                    trainer_ptrs.push_back(new Trainer(name, id, 'T', speed, Point2D(x, y)));
                    object_ptrs.push_back(new Trainer(name, id, 'T', speed, Point2D(x, y)));
                    active_ptrs.push_back(new Trainer(name, id, 'T', speed, Point2D(x, y)));
                    break;
                }
            case 'w':
                
                cout << "What is the Pokemon's name: ";
                cin >> pokename;
                cout << "What is the Pokemon's id: ";
                cin >> id;
                cout << "What is the Pokemon's attack: ";
                cin >> attack;
                cout << "What is the Pokemon's health: ";
                cin >> health;
                cout << "What is the x and y coordinate of the wild pokemon: ";
                cin >> x >> y;

                for (list <WildPokemon*>::iterator obj_it = wildpokemon_ptrs.begin(); obj_it != wildpokemon_ptrs.end(); obj_it++) 
                {
                    if ((*obj_it) -> GetId() == id) 
                    {
                        throw Invalid_Input("A WildPokemon with that ID already exists!");
                        return;
                    }
                }

                if (id > 9) 
                {
                    throw Invalid_Input("ID values greater than 9 cannot be displayed on the grid. Please choose a single-digit ID");
                    return;
                } 

                else 
                {
                    wildpokemon_ptrs.push_back(new WildPokemon(pokename, attack, health, false, id, Point2D(x, y)));
                    object_ptrs.push_back(new WildPokemon(pokename, attack, health, false, id, Point2D(x, y)));
                    active_ptrs.push_back(new WildPokemon(pokename, attack, health, false, id, Point2D(x, y)));
                    break;
                }
        }
    } 
    else 
    {
        throw Invalid_Input("Accepted parameters are: 'g', 'c', 't', or 'w'.");
        return;
    } 
}
