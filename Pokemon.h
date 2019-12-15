#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#ifndef POKEMON_H
#define POKEMON_H

class Pokemon {
    public:
        // constructors
        Pokemon();
        Pokemon(string n, double h, double a, double d, double s, double m, vector<string> t);

        // setters
        void setPokemonName(string n);
        void setPokemonHP(double h);
        void setPokemonMaxHP(double h);
        void setPokemonAttack(double a);
        void setPokemonDefence(double d);
        void setPokemonSpeed(double s);
        void setPokemonMax(double m);
        void setPokemonType(vector<string> t);
        void pokemonLevelUp();
        void setx_Cor_y_Cor(int x, int y);
        void incrementPokemonHP();
        void incrementEscapeAttempt();
        void decrementPokemonHP(double sub);
        void incrementPokemonLevel();

        // getters
        string getPokemonName();
        double getPokemonHP();
        double getPokemonMaxHP();
        double getPokemonAttack();
        double getPokemonDefence();
        double getPokemonSpeed();
        double getPokemonMax();
        vector<string> getPokemonType();
        int getPokemonTypeSize();
        int getx_Cor();
        int gety_Cor();
        int getEscapeAttempt();
        int getPokemonLevel();
        int getRandomID();

    private:
        string name;
        double hitPoints, attack, defence, speed, maxAttackDefence, maxHP;
        vector<string> type;
        int level, xCor, yCor, escapeAttempt, randomID;
};

#endif 