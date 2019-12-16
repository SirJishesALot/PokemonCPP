#include <iostream>
#include <vector>
#include <fstream>
#include "Pokemon.h"
#include "Player.h"
#include "Trainer.h"

using namespace std;

#ifndef LOCATION_H
#define LOCATION_H

class Location {
    public:
        Location();
        Location(string pokemonFile, string mapFile);

        // getters
        int getWildPokemonIndex();
        string getWildPokemonName();
        Pokemon getWildPokemon();
        int getTrainerIndexAt(int x, int y);
        bool getTrainerStateAt(int index);

        // setters
        void wildPokemonLevelUp();
        void setWildPokemonMaxHP();

        // random functions
        bool fleeWildPokemon(bool mode);
        void teleportPlayer();

        // Functions called from within the constructors
        void readPokemon(string fileName); // Reads all the pokemon from the file.
        void readMap(string fileName); // Reads the map from the file.
        void loadWildPokemon();
        void loadTrainerPokemon();
        void convertMap();
        void loadTrainerLocations();
        void scatterWildPokemon();

        // Do this after asking the user for a choice
        void setPlayerLocation(int x, int y);

        // Called according to the user
        int updatePlayerLocation(char m);
        Pokemon getPokemon(string pokemonName);
        void fightWildPokemon();
        bool runWildPokemon();
        void removeWildPokemon(int index);
        void viewWildPokemonStats();
        bool tryYourLuck();
        int fightTrainer(int index);
        void defeatTrainer(int index);

        void update();
        // Functions called after every turn
        void updateWildPokemonLocation();
        void showMiniMap();
        char checkPlayerLocation();
        void showActiveStats();
        bool checkWildPokemon();
        bool checkWin();
        bool findTreasure();
        bool randomDeath();

        // under the hood
        int checkFightWildPokemon();
        void transferPokemon(Pokemon p);

        // for testing purposes
        void viewAllPokemon();
        void viewMap();
        void viewWildPokemon();
        void viewTrainerPokemon();
        void viewTrainerLocations();
        void viewWildPokemonLocations();
        void viewPlayerLocation();

        Player player;
        Trainer trainers[15];

    private:
        vector<Pokemon> allPokemon;
        vector<Pokemon> wildPokemon;
        string map[25][16];
        int wildPokemonIndex;
};

#endif