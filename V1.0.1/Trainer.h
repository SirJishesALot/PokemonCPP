#include <iostream>
#include <vector>
#include <fstream>
#include "Pokemon.h"

using namespace std;

#ifndef TRAINER_H
#define TRAINER_H

class Trainer {
    public:
        Trainer();

        // setters
        void setTrainerPokemon(vector<Pokemon> p);
        void setx_Cor_y_Cor(int x, int y);
        void setBadge();
        void setActivePokemon();
        bool updateActivePokemon();
        void setState(bool s);
        void decrementActivePokemonHP(double sub);
        void incrementActivePokemonLevel();
        void updateActivePokemonStats();

        // getters
        int getx_Cor();
        int gety_Cor();
        bool getState();
        string getBadge();
        int getTotalPokemonSize();
        string getActivePokemonName();
        double getActivePokemonMaxHP();
        double getActivePokemonHP();
        double getActivePokemonAttack();
        double getActivePokemonDefence();
        double getActivePokemonSpeed();
        double getActivePokemonMax();
        Pokemon getActivePokemon();

        // for testing purposes
        void viewPokemon();
        void viewActivePokemon();
        
    private:
        int xCor, yCor;
        bool state;
        vector<Pokemon> trainerPokemon;
        string badge;
        Pokemon activePokemon;
};

#endif 