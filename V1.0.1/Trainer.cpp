#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include "Trainer.h"
#include "Pokemon.h"

using namespace std;

Trainer::Trainer() {
    setState(true);
    setBadge();
}

// setters
void Trainer::setTrainerPokemon(vector<Pokemon> p) {
    trainerPokemon = p;
}

void Trainer::setx_Cor_y_Cor(int x, int y) {
    xCor = x;
    yCor = y;
}

void Trainer::setBadge() {
    vector<string> badges = {"Boulder", "Thunder", "Volcano", "Soul", "Zephyr", "Mineral", "Glacier", "Plain", "Stone", "Balance", "Mind", "Dynamo", "Fire", "Hive", "Earth"};
    int random = rand() % 15;
    badge = badges[random];
}

void Trainer::setActivePokemon() {
    activePokemon = trainerPokemon[0];
}

bool Trainer::updateActivePokemon() {
    if (trainerPokemon.size() == 0) {
        return false;
    }

    else {
        trainerPokemon.erase(trainerPokemon.begin() + 0);
        if (trainerPokemon.size() == 0) {
            return false;
        }
        setActivePokemon();
        return true;
    }
}

void Trainer::updateActivePokemonStats() {
    for (int i = 0; i < trainerPokemon.size(); i++) {
        if (activePokemon.getPokemonName() == trainerPokemon[i].getPokemonName() && activePokemon.getRandomID() == trainerPokemon[i].getRandomID()) {
            trainerPokemon[i] = activePokemon;
            break;
        }
    }

    for (int i = 0; i < trainerPokemon.size(); i++) {
        if (activePokemon.getPokemonName() == trainerPokemon[i].getPokemonName() && activePokemon.getRandomID() == trainerPokemon[i].getRandomID()) {
            trainerPokemon[i] = activePokemon;
            break;
        }
    }
}

void Trainer::setState(bool s) {
    state = s;
}

void Trainer::decrementActivePokemonHP(double sub) {
    activePokemon.decrementPokemonHP(sub);
    updateActivePokemonStats();
}

void Trainer::incrementActivePokemonLevel() {
    activePokemon.incrementPokemonLevel();
    updateActivePokemonStats();
}

// getters
int Trainer::getx_Cor() {
    return xCor;
}

int Trainer::gety_Cor() {
    return yCor;
}

bool Trainer::getState() {
    return state;
}

string Trainer::getBadge() {
    return badge;
}

int Trainer::getTotalPokemonSize() {
    return trainerPokemon.size();
}

string Trainer::getActivePokemonName() {
    return activePokemon.getPokemonName();
}

double Trainer::getActivePokemonMaxHP() {
    return activePokemon.getPokemonMaxHP();
}

double Trainer::getActivePokemonHP() {
    return activePokemon.getPokemonHP();
}

double Trainer::getActivePokemonAttack() {
    return activePokemon.getPokemonAttack();
}

double Trainer::getActivePokemonDefence() {
    return activePokemon.getPokemonDefence();
}

double Trainer::getActivePokemonSpeed() {
    return activePokemon.getPokemonSpeed();
}

double Trainer::getActivePokemonMax() {
    return activePokemon.getPokemonMax();
}

Pokemon Trainer::getActivePokemon() {
    return activePokemon;
}

// for testing purposes
void Trainer::viewPokemon() {
    for (int i = 0; i < trainerPokemon.size(); i++) {
        cout << "Name: " << trainerPokemon[i].getPokemonName() << " ";
        cout << "HP: " << trainerPokemon[i].getPokemonHP() << " ";
        cout << "Attack: " << trainerPokemon[i].getPokemonAttack() << " ";
        cout << "Defence: " << trainerPokemon[i].getPokemonDefence() << " ";
        cout << "Speed: " << trainerPokemon[i].getPokemonSpeed() << " ";
        cout << "Max: " << trainerPokemon[i].getPokemonMax() << " ";
        cout << "Level: " << trainerPokemon[i].getPokemonLevel() << ", ";
        cout << "Type: ";
        vector<string> t = trainerPokemon[i].getPokemonType();

        for (int j = 0; j < t.size(); j++) {
            if (j == t.size() - 1) {
                cout << t[j];
            }

            else {
                cout << t[j] << " ";
            }
        }
        cout << endl;
    }
}

void Trainer::viewActivePokemon() {
    string bold = "\e[1m";
    string reset = "\e[0m\e[39m\e[49m";
    cout << bold << "Name: " << activePokemon.getPokemonName() << reset << ", ";
    cout << "HP: " << activePokemon.getPokemonHP() << "/" << activePokemon.getPokemonMaxHP() << ", ";
    cout << "Attack: " << activePokemon.getPokemonAttack() << ", ";
    cout << "Defence " << activePokemon.getPokemonDefence() << ", ";
    cout << "Speed: " << activePokemon.getPokemonSpeed() << ", ";
    cout << "Max: " << activePokemon.getPokemonMax() << ", ";
    cout << "Level: " << activePokemon.getPokemonLevel() << ", ";
    cout << "Type: ";
    vector<string> tempType = activePokemon.getPokemonType();
    for (int i = 0; i < tempType.size(); i++) {
        if (i == tempType.size() - 1) {
            cout << tempType[i];
        }
        else {
            cout << tempType[i] << ", ";
        }
    }
    cout << endl;
}