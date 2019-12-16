#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "Player.h"

using namespace std;

static vector<string> split(string input, char delimeter) {
    string holder;
    vector<string> output;
    
    loop:
    if (input.length() == 0) {
        return output;
    }
    
    if (input[0] == delimeter) {
        
        for (int i = 1; i < input.length(); i++) {
            holder += input[i];
        }
        
        input = holder;
    }
    
    holder = "";
    int size = input.length();
    
    if (input[size - 1] == delimeter) {
        
        for (int i = 0; i < size - 1; i++) {
            holder += input[i];
        }
        
        input = holder;
    }
    
    holder = "";
    
    if (input[0] == delimeter || input[input.length() - 1] == delimeter) {
        goto loop;
    }
    
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != delimeter) {
            holder += input[i];
        }
        
        else {
            
            if (holder == "") {
                continue;
            }
            
            else {
                output.push_back(holder);
                holder = "";
            }
        }
    }
    
    output.push_back(holder);
    return output;
}

// constructors
Player::Player() {
    setPlayerName("");
    pokeBalls = 10;
    wildEncounter = 0;
    escapeAttempt = 0;
    points = 0;
}

// setters
void Player::setPlayerName(string n) {
    name = n;
}

void Player::setx_Cor(int x) {
    xCor = x;
}

void Player::sety_Cor(int y) {
    yCor = y;
}

void Player::setActivePokemon(Pokemon p) {
    activePokemon = p;
}

void Player::incrementWildEncounter() {
    wildEncounter++;
}

void Player::incrementEscapeAttempt() {
    escapeAttempt++;
}

void Player::decrementActivePokemonHP(double sub) {
    activePokemon.decrementPokemonHP(sub);
}

void Player::healPokemonPartyCentre() {
    for (int i = 0; i < partyPokemon.size(); i++) {
        partyPokemon[i].setPokemonHP(partyPokemon[i].getPokemonMaxHP());
        partyPokemon[i] = partyPokemon[i];
    }
    updatePartyPokemon();
    activePokemon.setPokemonHP(activePokemon.getPokemonMaxHP());
    updateActivePokemon();
}

bool Player::switchActivePokemon() {
    cout << endl << "Choose a Pokémon from your party to make your Active Pokémon." << endl;
    vector<char> numbers;
    for (int i = 0; i < partyPokemon.size(); i++) {
        cout << "   " << i + 1 << ". " << partyPokemon[i].getPokemonName() << ", ";
        cout << "HP: " << partyPokemon[i].getPokemonHP() << "/" << partyPokemon[i].getPokemonMaxHP() << ", ";
        cout << "Attack: " << partyPokemon[i].getPokemonAttack() << ", ";
        cout << "Defence: " << partyPokemon[i].getPokemonDefence() << ", ";
        cout << "Speed: " << partyPokemon[i].getPokemonSpeed() << ", ";
        cout << "Max: " << partyPokemon[i].getPokemonMax() << ", ";
        cout << "Level: " << partyPokemon[i].getPokemonLevel() << endl;
        numbers.push_back('0' + (i + 1));
    }

    // string choice;
    // getline(cin, choice);

    system("stty raw");
    char choice = getchar();
    system("stty cooked");

    // int x = atoi(choice.c_str()), counter = 0;
    int counter = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (choice == numbers[i]) {
            counter++;
        }
    }

    if (counter == 0) {
        return false;
    }

    else {
        Pokemon p = partyPokemon[(choice - '0') - 1];
        if (p.getPokemonHP() <= 0) {
            cout << "Your active Pokémon must be able to fight." << endl;
            return false;
        }
        else {
            for (int i = 0; i < pokemonTotal.size(); i++) {
                if (activePokemon.getPokemonName() == pokemonTotal[i].getPokemonName() && activePokemon.getRandomID() == pokemonTotal[i].getRandomID()) {
                    pokemonTotal[i] = activePokemon;
                }
            }
            setActivePokemon(p);
            return true;
        }
    }
}

bool Player::switchPartyPokemon() {
    vector<int> numbers;
    cout << "Choose at most 6 Pokémon that you would like to to put in your party." << endl;
    cout << "The first Pokémon you choose will be made your active Pokémon." << endl;
    for (int i = 0; i < pokemonTotal.size(); i++) {
        cout << "   " << i + 1 << ". " << pokemonTotal[i].getPokemonName() << ", ";
        cout << "HP: " << pokemonTotal[i].getPokemonHP() << "/" << pokemonTotal[i].getPokemonMaxHP() << ", ";
        cout << "Attack: " << pokemonTotal[i].getPokemonAttack() << ", ";
        cout << "Defence: " << pokemonTotal[i].getPokemonDefence() << ", ";
        cout << "Speed: " << pokemonTotal[i].getPokemonSpeed() << ", ";
        cout << "Max: " << pokemonTotal[i].getPokemonMax() << ", ";
        cout << "Level: " << pokemonTotal[i].getPokemonLevel() << endl;
        numbers.push_back(i + 1);
    }
    string choice;
    getline(cin, choice);
    int counter = 0;

    vector<string> inputs = split(choice, ' ');
    if (inputs.size() > 6) {
        return false;
    }
    else if (inputs.size() > numbers.size()) {
        return false;
    }

    for (int i = 0; i < inputs.size(); i++) {
        int y = atoi(inputs[i].c_str());
        counter = 0;
        for (int j = 0; j < numbers.size(); j++) {
            if (y == numbers[j]) {
                counter++;
            }
        }
    }

    if (counter == 0) {
        return false;
    }

    counter = 0;
    for (int i = 0; i < inputs.size(); i++) {
        counter = 0;
        for (int j = 0; j < inputs.size(); j++) {
            if (inputs[i] == inputs[j]) {
                counter++;
            }
        }
        if (counter > 1) {
            cout << "You cannot choose the same Pokémon twice." << endl;
            return false;
        }
        else if (counter == 0) {
            return false;
        }
    }

    int z = partyPokemon.size();
    // clearing the current party
    for (int i = 0; i < z; i++) {
        partyPokemon.pop_back();
    }
    // adding the chosen pokemon to the party
    for (int i = 0; i < inputs.size(); i++) {
        int a = atoi(inputs[i].c_str());
        partyPokemon.push_back(pokemonTotal[a - 1]);
    }

    if (partyPokemon[0].getPokemonHP() <= 0) {
        cout << "Your active Pokémon must be able to fight." << endl;
        return false;
    }
    else {
        activePokemon = partyPokemon[0];
        return true;
    }
}

void Player::decrementPokeballs(int n) {
    pokeBalls -= n;
}

void Player::addBadge(string badge) {
    badges.push_back(badge);
}

void Player::incrementPokeballs(int n) {
    pokeBalls += n;
}

void Player::incrementPoints(int n) {
    points += n;
}

void Player::incrementActivePokemonLevel() {
    activePokemon.incrementPokemonLevel();
    updateActivePokemon();
}

bool Player::incrementSelectPokemonLevel() {
    cout << "Choose one of your Pokémon to feast on the Poffins and level up." << endl;
    vector<char> numbers;
    for (int i = 0; i < partyPokemon.size(); i++) {
        cout << "   " << i + 1 << ". " << partyPokemon[i].getPokemonName() << ", ";
        cout << "HP: " << partyPokemon[i].getPokemonHP() << "/" << partyPokemon[i].getPokemonMaxHP() << ", ";
        cout << "Attack: " << partyPokemon[i].getPokemonAttack() << ", ";
        cout << "Defence: " << partyPokemon[i].getPokemonDefence() << ", ";
        cout << "Speed: " << partyPokemon[i].getPokemonSpeed() << ", ";
        cout << "Max: " << partyPokemon[i].getPokemonMax() << ", ";
        cout << "Level: " << partyPokemon[i].getPokemonLevel() << endl;
        numbers.push_back('0' + (i + 1));
    }

    system("stty raw");
    char choice = getchar();
    system("stty cooked");

    // if (choice.length() == 0 || choice.length() > 1) {
    //     return false;
    // }

    // int x = atoi(choice.c_str()), counter = 0;
    int counter = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (choice == numbers[i]) {
            counter++;
        }
    }

    if (counter == 0) {
        return false;
    }
    else {
        if (partyPokemon[(choice - '0') - 1].getPokemonName() == activePokemon.getPokemonName() && partyPokemon[(choice - '0') - 1].getRandomID() == activePokemon.getRandomID()) {
            incrementActivePokemonLevel();
            updateActivePokemon();
        }
        else {
            partyPokemon[(choice - '0') - 1].incrementPokemonLevel();
        }
        return true;
    }
}

void Player::removePartyPokemon(int index) {
    string underline = "\e[4m";
    string reset = "\e[0m\e[39m\e[49m";
    cout << underline<< "Oh no! After years of legendary battles, " << partyPokemon[index].getPokemonName() << " has died of old age. Thank you for your companionship, dear friend." << reset << endl;
    int x;
    for (int i = 0; i < pokemonTotal.size(); i++) {
        if (partyPokemon[index].getPokemonName() == pokemonTotal[i].getPokemonName() && partyPokemon[index].getRandomID() == pokemonTotal[i].getRandomID()) {
            x = i;
        }
    }
    pokemonTotal.erase(pokemonTotal.begin() + x);

    if (activePokemon.getPokemonName() == partyPokemon[index].getPokemonName() && activePokemon.getRandomID() == partyPokemon[index].getRandomID()) {
        partyPokemon.erase(partyPokemon.begin() + index);
        int random3 = rand() % partyPokemon.size();
        activePokemon = partyPokemon[random3];
        cout << "Your active Pokémon is now " << activePokemon.getPokemonName() << endl;
    }
    else {
        partyPokemon.erase(partyPokemon.begin() + index);
    }
}

// getters
double Player::getPlayerPoints() {
    return points;
}

string Player::getPlayerName() {
    return name;
}

int Player::getx_Cor() {
    return xCor;
}

int Player::gety_Cor() {
    return yCor;
}

int Player::getPokemonTotalSize() {
    return pokemonTotal.size();
}

int Player::getPokemonPartySize() {
    return partyPokemon.size();
}

string Player::getActivePokemonName() {
    return activePokemon.getPokemonName();
}

double Player::getActivePokemonMaxHP() {
    return activePokemon.getPokemonMaxHP();
}

double Player::getActivePokemonHP() {
    return activePokemon.getPokemonHP();
}

double Player::getActivePokemonAttack() {
    return activePokemon.getPokemonAttack();
}

double Player::getActivePokemonDefence() {
    return activePokemon.getPokemonDefence();
}

double Player::getActivePokemonSpeed() {
    return activePokemon.getPokemonSpeed();
}

double Player::getActivePokemonMax() {
    return activePokemon.getPokemonMax();
}

int Player::getPokeBalls() {
    return pokeBalls;
}

int Player::getWildEncounter() {
    return wildEncounter;
}

int Player::getEscapeAttempt() {
    return escapeAttempt;
}

int Player::getBadgesSize() {
    return badges.size();
}

double Player::getPoints() {
    return points;
}

vector<string> Player::getBadges() {
    return badges;
}

int Player::getDiffTypes() {
    vector<string> tempTypes;
    for (int i = 0; i < pokemonTotal.size(); i++) {
        vector<string> temp = pokemonTotal[i].getPokemonType();
        for (int j = 0; j < temp.size(); j++) {
            tempTypes.push_back(temp[j]);
        }
    }

    for (int i = 0; i < tempTypes.size(); i++) {
        int counter = 0, x;
        for (int j = 0; j < tempTypes.size(); j++) {
            if (tempTypes[i] == tempTypes[j]) {
                counter++;
                x = j;
            }
        }

        if (counter > 1) {
            i--;
            tempTypes.erase(tempTypes.begin() + x);
        }
    }
    return tempTypes.size();
}

vector<string> Player::getActivePokemonType() {
    return activePokemon.getPokemonType();
}

int Player::getActivePokemonLevel() {
    return activePokemon.getPokemonLevel();
}

// other
void Player::addPokemon(Pokemon p) {
    pokemonTotal.push_back(p);

    if (partyPokemon.size() < 6) {
        partyPokemon.push_back(p);
    }
}

void Player::rest() {
    pokeBalls--;

    for (int i = 0; i < partyPokemon.size(); i++) {
        if (partyPokemon[i].getPokemonHP() < partyPokemon[i].getPokemonMaxHP()) {
            partyPokemon[i].incrementPokemonHP();
        }
    }
}

void Player::viewPartyPokemon() {
    for (int i = 0; i < partyPokemon.size(); i++) {
        cout << "   " << i + 1 << ". " << partyPokemon[i].getPokemonName() << ", ";
        cout << "HP: " << partyPokemon[i].getPokemonHP() << "/" << partyPokemon[i].getPokemonMaxHP() << ", ";
        cout << "Attack: " << partyPokemon[i].getPokemonAttack() << ", ";
        cout << "Defence: " << partyPokemon[i].getPokemonDefence() << ", ";
        cout << "Speed: " << partyPokemon[i].getPokemonSpeed() << ", ";
        cout << "Max: " << partyPokemon[i].getPokemonMax() << endl;
    }
}

bool Player::checkPartyPokemonHP() {
    int counter = 0;
    for (int i = 0; i < partyPokemon.size(); i++) {
        if (partyPokemon[i].getPokemonHP() <= 0) {
            counter++;
        }
    }

    if (counter == partyPokemon.size()) {
        return true;
    }

    else {
        return false;
    }
}

// called after each turn
void Player::updateActivePokemon() {
    for (int i = 0; i < partyPokemon.size(); i++) {
        if (activePokemon.getPokemonName() == partyPokemon[i].getPokemonName() && activePokemon.getRandomID() == partyPokemon[i].getRandomID()) {
            partyPokemon[i] = activePokemon;
            break;
        }
    }

    for (int i = 0; i < pokemonTotal.size(); i++) {
        if (activePokemon.getPokemonName() == pokemonTotal[i].getPokemonName() && activePokemon.getRandomID() == pokemonTotal[i].getRandomID()) {
            pokemonTotal[i] = activePokemon;
            break;
        }
    }
}

void Player::updatePartyPokemon() {
    for (int i = 0; i < partyPokemon.size(); i++) {
        for (int j = 0; j < pokemonTotal.size(); j++) {
            if (partyPokemon[i].getPokemonName() == pokemonTotal[j].getPokemonName() && partyPokemon[i].getRandomID() == pokemonTotal[j].getRandomID()) {
                pokemonTotal[j] = partyPokemon[i];
            }
        }
    }
}