#include <iostream>
#include <vector>
#include <fstream>
#include "Pokemon.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {
    public:
        Player();

        // setters
        void setPlayerName(string n);
        void setx_Cor(int x);
        void sety_Cor(int y);
        void setActivePokemon(Pokemon p);
        void incrementWildEncounter();
        void incrementEscapeAttempt();
        void decrementActivePokemonHP(double sub);
        void healPokemonPartyCentre();
        bool switchActivePokemon();
        bool switchPartyPokemon();
        void decrementPokeballs(int n);
        void addBadge(string badge);
        void incrementPokeballs(int n);
        void incrementPoints(int n);
        void incrementActivePokemonLevel();
        bool incrementSelectPokemonLevel();
        void removePartyPokemon(int index);

        // getters
        double getPlayerPoints();
        int getx_Cor();
        int gety_Cor();
        string getPlayerName();
        int getPokemonTotalSize();
        int getPokemonPartySize();
        string getActivePokemonName();
        double getActivePokemonMaxHP();
        double getActivePokemonHP();
        double getActivePokemonAttack();
        double getActivePokemonDefence();
        double getActivePokemonSpeed();
        double getActivePokemonMax();
        int getPokeBalls();
        int getWildEncounter();
        int getEscapeAttempt();
        int getBadgesSize();
        double getPoints();
        vector<string> getBadges();
        int getDiffTypes();
        vector<string> getActivePokemonType();
        int getActivePokemonLevel();

        // other
        void addPokemon(Pokemon p);
        void rest();
        void viewPartyPokemon();
        bool checkPartyPokemonHP();

        // called after each turn
        void updateActivePokemon();
        void updatePartyPokemon();

    private:
        string name;
        double points;
        vector<Pokemon> pokemonTotal;
        vector<Pokemon> partyPokemon;
        Pokemon activePokemon;
        int pokeBalls, xCor, yCor, wildEncounter, escapeAttempt;
        vector<string> badges;
};

#endif