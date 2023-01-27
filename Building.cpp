#include <iostream>

#include "Building.h"


//Default Builidng Constructor
Building::Building()
    : GameObject('B'), trainer_count(0)
{
    display_code = 'B';
    cout << "Building default constructed" << endl;
}

//Create new Buildling Constructor
Building::Building(char in_code, int in_Id, Point2D in_loc)
    : GameObject(in_loc, in_Id, in_code), trainer_count(0)
{
    id_num = in_Id;
    location = in_loc;
    display_code = in_code;

    cout << "Building constructed" << endl;
}

//Destruct Building
Building::~Building()
{
    cout << "Building destructed" << endl;
}

//Public Member Functions
void Building::AddOneTrainer()
{
    trainer_count++;
}

void Building::RemoveOneTrainer()
{
    trainer_count--;
}

void Building::ShowStatus()
{
    GameObject::ShowStatus();
    cout << trainer_count << " trainers ";
    if (trainer_count == 1)
    {
        cout << "is in this building" << endl;
    }
    else
    {
        cout << "are in this building" << endl;
    }
}

bool Building::ShouldBeVisible()
{
    //buildings always visible
    return true;
}