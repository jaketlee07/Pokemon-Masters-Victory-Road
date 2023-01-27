#include "GameCommand.h"
#include "View.h"
#include "InputHandling.h"

#include <iostream>


int id1, id2, x, y;

// Move command
void DoMoveCommand(Model &model, int trainer_id, Point2D p1)
{
	// Get trainer pointer
	Trainer *tptr = model.getTrainerPtr(trainer_id);

	try
	{
		if (tptr == 0) // valid trainer
		{
			throw Invalid_Input("Error: Trainer does not exist!");
		}
		tptr->Trainer::StartMoving(p1);
		cout << "Moving " << tptr->GetTrainerName() << " to " << p1 << endl;

	}
	catch(Invalid_Input &except) 
	{
		cout << "Invalid Input - " << except.msg_ptr << endl;
	}
}
// Move to center command
void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id)
{
	// get trainer pointer
	Trainer *tptr = model.getTrainerPtr(trainer_id);

	// get center pointer
	PokemonCenter *cptr = model.getPokemonCenterPtr(center_id);
	try
	{
		if (tptr == 0 && cptr == 0)
		{
			throw Invalid_Input("Error: Trainer or Center does not exist");
		}
		tptr->StartMovingToCenter(cptr);
		cout << "Moving " << tptr->GetTrainerName() << " to pokemon center " << cptr->GetId() << endl;
	}
	catch(Invalid_Input &except)
	{
		cout << "Invalid Input - " << except.msg_ptr << endl;
	}

}
//Move to gym command
void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id)
{
	// get trainer pointer
	Trainer *tptr = model.getTrainerPtr(trainer_id);

	// get gym pointer
	PokemonGym *gptr = model.getPokemonGymPtr(gym_id);

	try 
	{
		if (tptr == 0 && gptr == 0)
		{
			throw Invalid_Input("Error: Trainer or Gym does not exist");
		}

		tptr->StartMovingToGym(gptr);
		cout << "Moving " << tptr->GetTrainerName() << " to gym " << gptr->GetId() << endl;
	}
	catch(Invalid_Input &except) 
	{
		cout << "Invalid Input - " << except.msg_ptr << endl;
	}
	
}
// Stop command
void DoStopCommand(Model & model, int trainer_id)
{
	// get trainer pointer
	Trainer *tptr = model.getTrainerPtr(trainer_id);

	try 
	{
		if(tptr == 0)
		{
			throw Invalid_Input("Error: Trainer does not exist");
		}
		tptr->Stop();
		cout << "Stopping " << tptr->GetTrainerName();
	}
	catch(Invalid_Input &except)
	{
		cout << "Invalid Input - " << except.msg_ptr << endl;
	}
}

// Battle command
void DoBattleCommand(Model & model, int trainer_id, unsigned int battles)
{
	// get trainer pointer
	Trainer *tptr = model.getTrainerPtr(trainer_id);

	try
	{
		if(tptr == 0)
		{
			throw  Invalid_Input("Error: Trainer does not exist");
		}
		if (tptr->GetState() != IN_GYM)
		{
			throw  Invalid_Input("Error: Trainer is not in gym");
		}
		cout << tptr->GetTrainerName() << " is battling" << endl;
		tptr->StartBattling(battles);
		model.Update();
		model.ShowStatus();
	}
	catch(Invalid_Input &except)
	{
		cout << "Invalid Input - " << except.msg_ptr << endl;
	}
	
}
// Reciver health in the center command
void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed)
{
	// get trainer pointer
	Trainer *tptr = model.getTrainerPtr(trainer_id);

	try 
	{
		if (tptr == 0)
		{
			throw  Invalid_Input("Error: Trainer does not exist");
		}
		if (tptr->GetState() != AT_CENTER)
		{
			throw  Invalid_Input("Error: Trainer is not at center");
		}
		cout << "Recovering " << tptr->GetTrainerName() << "'s Pokemon's health" << endl;
		tptr->StartRecoveringHealth(potions_needed);
		model.Update();
		model.ShowStatus();
	} // not a valid trainer or trainer is not at center
	catch(Invalid_Input &except)
	{
		cout << "Invalid Input - " << except.msg_ptr << endl;
	}
}
// Advance one tick command
void DoAdvanceCommand(Model& model, View& view)
{
	model.Update();
	model.ShowStatus();
    model.Display(view);
	cout << "Advancing one tick" << endl;
}
// Advance 5 ticks or until event is reached
void DoRunCommand(Model& model, View& view)
{
	int loopCount = 0; // loop counter in order to run 5 times
	do
	{
		loopCount++; // this code runs 4 times
	} while ((loopCount!= 6) && (!(model.Update())));

		model.ShowStatus();
		model.Display(view);
	cout << "Advancing to next event" << endl;
}