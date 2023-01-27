#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H
#include <iostream>
#include "Model.h"

using namespace std;

void DoMoveCommand(Model &model, int, Point2D );
void DoMoveToCenterCommand(Model & model, int, int);
void DoMoveToGymCommand(Model & model, int, int);
void DoStopCommand(Model & model, int);
void DoBattleCommand(Model & model, int, unsigned int);
void DoRecoverInCenterCommand(Model& model, int, unsigned int);
void DoAdvanceCommand(Model& model, View& view);
void DoRunCommand(Model& model, View& view);


#endif