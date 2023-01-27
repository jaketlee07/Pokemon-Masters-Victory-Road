#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "WildPokemon.h"

using namespace std;

class Model{
	private:
		int time;

		list <GameObject*> object_ptrs;
        list <GameObject*> active_ptrs;
        list <Trainer*> trainer_ptrs;
        list <PokemonCenter*> center_ptrs;
        list <PokemonGym*> gym_ptrs;
		list <WildPokemon*> wildpokemon_ptrs;

	public:
		Model();
		~Model();
		Trainer * getTrainerPtr(int id);
		PokemonCenter * getPokemonCenterPtr(int id);
		PokemonGym * getPokemonGymPtr(int id);
		WildPokemon * getWildPokemonPtr(int id);
		bool Update();
		void Display(View& view);
		void ShowStatus();
		void EncounterPokemon();
		void NewCommand(char);
};

#endif 