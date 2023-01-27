#include <iostream>
#include "Trainer.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "GameCommand.h"
#include "Model.h"
#include "View.h"
#include "InputHandling.h"

using namespace std;

int main()
{
    srand(time(NULL));

    char inputCommand, type;
    int id1, id2, x, y;

    Model model = Model(); // make the models of trainers and buildings
	View view = View(); 
    model.ShowStatus();
    model.Display(view);
	cout << endl << endl;

    while(inputCommand != 'q') // while the user has not quit continue requesting new command
    {
		try
		{
        cout << "Enter command: ";
		cin >> inputCommand;
		if(!isalpha(inputCommand))
		{
			throw Invalid_Input("Was expecting a char for the command");
		}

        switch (inputCommand)
        {
			case 'm': // move command
			
                if(!(cin >> id1 >> x >> y))
				{
					throw Invalid_Input("Was expecting a digit for Trainer and Location");
				}
				DoMoveCommand(model, id1, Point2D(x, y));
				break;
			case 'c': // move to center command
                if(!(cin >> id1 >> id2))
				{
					throw Invalid_Input("Was expecting a digit for Trainer and Center");
				}
				DoMoveToCenterCommand(model, id1, id2);
				break;	
			case 'g': // move to gym command
                if(!(cin >> id1 >> id2))
				{
					throw Invalid_Input("Was expecting a digit for Trainer and Gym");
				}
				DoMoveToGymCommand(model, id1, id2);
				break;
			case 's': // stop command
                if(!(cin >> id1))
				{
					throw Invalid_Input("Was expecting a digit for Trainer");
				}
				DoStopCommand(model, id1);
				break;
			case 'p': // recover health in center command
                if(!(cin >> id1 >> x))
				{
					throw Invalid_Input("Was expecting a digit for Trainer and Potions");
				}
				DoRecoverInCenterCommand(model, id1, x);
				model.Display(view);
				break;
			case 'b': // battle in gym command
                if(!(cin >> id1 >> x))
				{
					throw Invalid_Input("Was expecting a digit for Trainer and Battles");
				}
			    DoBattleCommand(model, id1, x);
				model.Display(view);
				break;
			case 'n':
                if (!(cin >> type)) 
				{
                 	cin.ignore(100, '\n');
                	cin.clear();
                	throw Invalid_Input("Expected a char and three integers");
                    cout << endl;
                }
				model.NewCommand(type);
				model.Display(view);
			case 'a': // advance one tick command
				DoAdvanceCommand(model, view);
                break;
			case 'r': // advance 5 ticks or until next event command
                DoRunCommand(model, view);
				break;
            case 'q': // quit game
            {
				cout << "Terminated Program" << endl;
                break;
            }
			default:
				cout << "Invalid input. Try again..." << endl;
				while (!(cin.get() == '\n'));	
		}
		}

		catch (Invalid_Input &except) 
		{
			cout << "Invalid Input - " << except.msg_ptr << endl;
			cin.clear();
			cin.ignore(100, '\n');

		}
    }


}