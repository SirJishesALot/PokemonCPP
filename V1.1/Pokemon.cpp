#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "Pokemon.h"

using namespace std;

// constructors
Pokemon::Pokemon() {
    setPokemonName("");
    setPokemonMaxHP(0);
    setPokemonAttack(0);
    setPokemonDefence(0);
    setPokemonSpeed(0);
    setPokemonMax(0);
    level = 1;
    escapeAttempt = 0;
    randomID = rand() % 100;
}

Pokemon::Pokemon(string n, double h, double a, double d, double s, double m, vector<string> t) {
    setPokemonName(n);
    setPokemonMaxHP(h);
    setPokemonAttack(a);
    setPokemonDefence(d);
    setPokemonSpeed(s);
    setPokemonMax(m);
    setPokemonType(t);
    level = 1;
    escapeAttempt = 0;
    randomID = rand() % 100;
}

// setters
void Pokemon::setPokemonName(string n) {
    name = n;
}

void Pokemon::setPokemonHP(double h) {
    hitPoints = h;
}

void Pokemon::setPokemonMaxHP(double h) {
    maxHP = h;
    hitPoints = maxHP;
}

void Pokemon::setPokemonAttack(double a) {
    attack = a;
}

void Pokemon::setPokemonDefence(double d) {
    defence = d;
}

void Pokemon::setPokemonSpeed(double s) {
    speed = s;
}

void Pokemon::setPokemonMax(double m) {
    maxAttackDefence = m;
}

void Pokemon::setPokemonType(vector<string> t) {
    type = t;
}

void Pokemon::pokemonLevelUp() {
    level++;
}

void Pokemon::setx_Cor_y_Cor(int x, int y) {
    xCor = x;
    yCor = y;
}

void Pokemon::incrementPokemonHP() {
    hitPoints++;
}

void Pokemon::incrementEscapeAttempt() {
    escapeAttempt++;
}

void Pokemon::decrementPokemonHP(double sub) {
    hitPoints -= sub;
}

void Pokemon::incrementPokemonLevel() {
    string underline = "\e[4m";
    string reset = "\e[0m\e[39m\e[49m";
    level++;
    double n, m;

    n = getPokemonMaxHP() * 1.02;
    if (n > (getPokemonMaxHP() + 0.5) && n < (getPokemonMaxHP() + 1)) {
        m = ceil(n);
    }
    else {
        m = floor(n);
    }
    setPokemonMaxHP(m);
    setPokemonHP(getPokemonMaxHP());

    if (getPokemonAttack() < getPokemonMax()) {
        n = getPokemonAttack() * 1.02;
        if (n > (getPokemonAttack() + 0.5) && n < (getPokemonAttack() + 1)) {
            m = ceil(n);
        }
        else {
            m = floor(n);
        }
        setPokemonAttack(m);
    }
    if (getPokemonDefence() < getPokemonMax()) {
        n = getPokemonDefence() * 1.02;
        if (n > (getPokemonDefence() + 0.5) && n < (getPokemonDefence() + 1)) {
            m = ceil(n);
        }
        else {
            m = floor(n);
        }
        setPokemonDefence(m);
    }
    
    n = getPokemonSpeed() * 1.02;
    if (n > (getPokemonSpeed() + 0.5) && n < (getPokemonSpeed() + 1)) {
        m = ceil(n);
    }
    else {
        m = floor(n);
    }
    setPokemonSpeed(m);
    cout << endl << underline << getPokemonName() << " has leveled up!" << reset << endl;
}

// getters
string Pokemon::getPokemonName() {
    return name;
}

double Pokemon::getPokemonHP() {
    return hitPoints;
}

double Pokemon::getPokemonMaxHP() {
    return maxHP;
}

double Pokemon::getPokemonAttack() {
    return attack;
}

double Pokemon::getPokemonDefence() {
    return defence;
}

double Pokemon::getPokemonSpeed() {
    return speed;
}

double Pokemon::getPokemonMax() {
    return maxAttackDefence;
}

vector<string> Pokemon::getPokemonType() {
    return type;
}

int Pokemon::getPokemonTypeSize() {
    return type.size();
}

int Pokemon::getx_Cor() {
    return xCor;
}

int Pokemon::gety_Cor() {
    return yCor;
}

int Pokemon::getEscapeAttempt() {
    return escapeAttempt;
}

int Pokemon::getPokemonLevel() {
    return level;
}

int Pokemon::getRandomID() {
    return randomID;
}