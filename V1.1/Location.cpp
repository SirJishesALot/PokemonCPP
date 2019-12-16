#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "Location.h"
#include "Pokemon.h"
#include "Trainer.h"

using namespace std;

static int split(string input, char delimeter, string words[], int len) {
    string holder;
    int x = 0;
    
    loop:
    if (input.length() == 0) {
        return 0;
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
                words[x] = holder;
                holder = "";
                x++;
            }
        }
    }
    
    words[x] = holder;
    
    if (x > len) {
        return -1;
    }
    
    else {
        return x + 1;
    }
}

// constructors
Location::Location() {
    readPokemon("./pokemon.txt");
    readMap("./mapPoke.txt");
    loadWildPokemon();
    loadTrainerPokemon();
    convertMap();
    loadTrainerLocations();
    scatterWildPokemon();
}

Location::Location(string pokemonFile, string mapFile) {
    readPokemon(pokemonFile);
    readMap(mapFile);
    loadWildPokemon();
    loadTrainerPokemon();
    convertMap();
    loadTrainerLocations();
    scatterWildPokemon();
}

// getters
int Location::getWildPokemonIndex() {
    return wildPokemonIndex;
}

string Location::getWildPokemonName() {
    return wildPokemon[wildPokemonIndex].getPokemonName();
}

Pokemon Location::getWildPokemon() {
    return wildPokemon[wildPokemonIndex];
}

int Location::getTrainerIndexAt(int x, int y) {
    int z;
    for (int i = 0; i < 15; i++) {
        if (trainers[i].getx_Cor() == x && trainers[i].gety_Cor() == y) {
            z = i;
        }
    }
    return z;
}

bool Location::getTrainerStateAt(int index) {
    return trainers[index].getState();
}

// setters
void Location::wildPokemonLevelUp() {
    wildPokemon[wildPokemonIndex].incrementPokemonLevel();
}

void Location::setWildPokemonMaxHP() {
    wildPokemon[wildPokemonIndex].setPokemonHP(wildPokemon[wildPokemonIndex].getPokemonMaxHP());
}

// random functions
bool Location::fleeWildPokemon(bool mode) {
    wildPokemon[wildPokemonIndex].incrementEscapeAttempt();
    double a = wildPokemon[wildPokemonIndex].getPokemonSpeed();
    double b = (player.getActivePokemonSpeed() / 4.0);
    double c = wildPokemon[wildPokemonIndex].getEscapeAttempt();
    double f = ((a * 32) / b) + (30 * c);
    string star = "*";
    star += 13;
    vector<int> xPos;
    vector<int> yPos;

    for(int i = 0; i < 25; i++) {
        for (int j = 0; j < 16; j++) {
            if (map[i][j] == "*" || map[i][j] == star) {
                xPos.push_back(i);
                yPos.push_back(j);
            }
        }
    }

    for (int i = 0; i < xPos.size(); i++) {
        for (int j = 0; j < wildPokemon.size(); j++) {
            if (xPos[i] == wildPokemon[j].getx_Cor() && yPos[i] == wildPokemon[j].gety_Cor()) {
                xPos.erase(xPos.begin() + i);
                yPos.erase(yPos.begin() + i);
                i--; // might be a problem here
            }
        }
    }
    int random = rand() % xPos.size();

    if (mode) {
        wildPokemon[wildPokemonIndex].setx_Cor_y_Cor(xPos[random], yPos[random]);
        return true;
    }
    else {
        if (f > 255) {
            wildPokemon[wildPokemonIndex].setx_Cor_y_Cor(xPos[random], yPos[random]);
            return true;
        }

        else {
            int random = rand() % 256;
            if (random <= f) {
                wildPokemon[wildPokemonIndex].setx_Cor_y_Cor(xPos[random], yPos[random]);
                return true;
            }

            else {
                return false;
            }
        }
    }
}

void Location::teleportPlayer() {
    int distance = 100000;
    vector<int> xPos;
    vector<int> yPos;
    string C = "C";
    C += 13;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 16; j++) {
            if (map[i][j] == "C" || map[i][j] == C) {
                xPos.push_back(i);
                yPos.push_back(j);
            }
        }
    }

    int x = player.getx_Cor();
    int y = player.gety_Cor();
    int xNew, yNew;

    for (int i = 0; i < xPos.size(); i++) {
        int a = (x - xPos[i]);
        int b = (y - yPos[i]);
        int a2 = pow(a, 2);
        int b2 = pow(b, 2);

        if ((a2 + b2) < distance) {
            distance = a2 + b2;
            xNew = xPos[i];
            yNew = yPos[i];
        }
    }
    player.setx_Cor(xNew);
    player.sety_Cor(yNew);
}

// Called in the constructor
void Location::readPokemon(string fileName) {
    ifstream file;
    file.open(fileName);

    if (file.fail()) {
        cout << "The entered file for the Pokemon is invalid." << endl;
    }

    else {
        string line;
        int x = 0;

        while(getline(file, line)) {
            if (x == 0) {
                x++;
                continue;
            }

            else {
                string words[9];
                int value = split(line, ',', words, 9);
                vector<string> t;
                for (int i = 0; i < words[7].size(); i++) {
                    string temp = words[7];
                    if (temp[i] == 13 || temp[i] == 0) {
                        words[7].erase(words[7].begin() + i);
                    }
                }
                t.push_back(words[7]);

                if (value == 9) {
                    for (int i = 0; i < words[8].size(); i++) {
                        string temp = words[8];
                        if (temp[i] == 13 || temp[i] == 0) {
                            words[8].erase(words[8].begin() + i);
                        }
                    }
                    t.push_back(words[8]);
                }

                Pokemon p(words[1], atof(words[2].c_str()), atof(words[3].c_str()), atof(words[4].c_str()), atof(words[5].c_str()), atof(words[6].c_str()), t);

                allPokemon.push_back(p);
                x++;
            }
        }
    }
}

void Location::readMap(string fileName) {
    ifstream file;
    file.open(fileName);

    if (file.fail()) {
        cout << "The entered file for the map is invalid." << endl;
    }

    else {
        string line;
        int i = 0;

        while (getline(file, line)) {
            string words[16];
            split(line, ',', words, 16);

            for (int j = 0; j < 16; j++) {
                map[i][j] = words[j];
            }

            i++;
        }
    }
}

void Location::loadWildPokemon() {
    vector<int> previousPokemon;
    
    for (int i = 0; i < 20; i++) {
        int counter = 0;
        int random = rand() % allPokemon.size();
        for (int j = 0; j < previousPokemon.size(); j++) {
            if (random == previousPokemon[j]) {
                counter++;
            }
        }

        if (counter > 0) {
            i--;
            continue;
        }

        else {
            wildPokemon.push_back(allPokemon[random]);
            previousPokemon.push_back(random);
        }
    }
}

void Location::loadTrainerPokemon() {

    for (int i = 0; i < 15; i++) {
        int number = 0;

        while (number == 0) {
            number = rand() % 7;
        }

        vector<Pokemon> p;

        for (int j = 0; j < number; j++) {
            int random = rand() % allPokemon.size();
            p.push_back(allPokemon[random]);
        }

        trainers[i].setTrainerPokemon(p);
    }
}

void Location::convertMap() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 16; j++) {
            string p = "p";
            string w = "w";
            string G = "G";
            string C = "C";
            p += 13;
            w += 13;
            G += 13;
            C += 13;
            if (map[i][j] == "p" || map[i][j] == p) {
                map[i][j] = "*";
            }

            else if (map[i][j] == "w" || map[i][j] == w) {
                map[i][j] = "~";
            }

            else if (map[i][j] == G) {
                map[i][j] = "G";
            }

            else if (map[i][j] == C) {
                map[i][j] = "C";
            }
        }
    }
}

void Location::loadTrainerLocations() {
    vector<int> gymX;
    vector<int> gymY;

    for (int i = 0; i < 25; i++) {
        for(int j = 0; j < 16; j++) {
            string G = "G";
            G += 13;
            if (map[i][j] == "G" || map[i][j] == G) {
                gymX.push_back(i);
                gymY.push_back(j);
            }
        }
    }

    for (int i = 0; i < 15; i++) {
        trainers[i].setx_Cor_y_Cor(gymX[i], gymY[i]);
    }
}

void Location::scatterWildPokemon() {
    vector<int> pokemonX;
    vector<int> pokemonY;
    vector<int> randomValue = {-1};

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 16; j++) {
            string star = "*";
            star += 13;

            if (map[i][j] == "*" || map[i][j] == star) {
                pokemonX.push_back(i);
                pokemonY.push_back(j);
            }
        }
    }

    for (int i = 0; i < pokemonX.size(); i++) {
        bool yStart = pokemonY[i] == 6 || pokemonY[i] == 7 || pokemonY[i] == 8 || pokemonY[i] == 9;
        if (pokemonX[i] == 12 && yStart) {
            pokemonX.erase(pokemonX.begin() + i);
            pokemonY.erase(pokemonY.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < wildPokemon.size(); i++) {
        int random = rand() % pokemonX.size();
        int counter = 0;
        for (int j = 0; j < randomValue.size(); j++) {
            if (random == randomValue[j]) {
                counter++;
            }
        }

        if (counter > 0) {
            i--;
            continue;
        }

        else {
            randomValue.push_back(random);
        }

        wildPokemon[i].setx_Cor_y_Cor(pokemonX[random], pokemonY[random]);
    }
}

// Do this after asking the user for a choice
void Location::setPlayerLocation(int x, int y) {
    player.setx_Cor(x);
    player.sety_Cor(y);
}

// According to the user
int Location::updatePlayerLocation(char m) {
    int x = player.getx_Cor();
    int y = player.gety_Cor();

    switch(m) {
        case 'w': x--; break;
        case 's': x++; break;
        case 'a': y--; break;
        case 'd': y++; break;
    }
    string tilde = "~";
    tilde += 13;

    if (x < 0 || x >= 25 || y < 0 || y >= 16) {
        return 0;
    }

    else if (map[x][y] == "~" || map[x][y] == tilde) {
        return 2;
    }

    else {
        player.setx_Cor(x);
        player.sety_Cor(y);
        return 1;
    }
}

Pokemon Location::getPokemon(string pokemonName) {
    Pokemon p;
    for (int i = 0; i < allPokemon.size(); i++) {
        if (pokemonName == allPokemon[i].getPokemonName()) {
            p = allPokemon[i];
        }
    }

    return p;
}

void Location::fightWildPokemon() {
    string red = "\e[31m";
    string green = "\e[32m";
    string cyan = "\e[96m";
    string reset = "\e[0m\e[39m\e[49m";

    double activeSpeed = player.getActivePokemonSpeed();
    double wildSpeed = wildPokemon[wildPokemonIndex].getPokemonSpeed();

    if ( activeSpeed >= wildSpeed) {
        cout << "You attack first." << endl;
        int randAA = rand() % (int(player.getActivePokemonAttack()) + 1);
        int randDW = rand() % (int(wildPokemon[wildPokemonIndex].getPokemonDefence()) + 1);

        if (randAA > randDW) {
            double sub = randAA - randDW;
            wildPokemon[wildPokemonIndex].decrementPokemonHP(sub);
            cout << "You did " << green << sub << reset << " damage to " << wildPokemon[wildPokemonIndex].getPokemonName() << endl;
        }

        else {
            cout << "Your attack had " << cyan << "no effect" << reset << " on " << wildPokemon[wildPokemonIndex].getPokemonName() << endl;
        }

        if (wildPokemon[wildPokemonIndex].getPokemonHP() <= 0) {
            return;
        }

        cout << wildPokemon[wildPokemonIndex].getPokemonName() << " now attacks." << endl;
        int randAW = rand() % (int(wildPokemon[wildPokemonIndex].getPokemonAttack()) + 1);
        int randDA = rand() % (int(player.getActivePokemonDefence()) + 1);

        if (randAW > randDA) {
            double sub = randAW - randDA;
            player.decrementActivePokemonHP(sub);
            cout << wildPokemon[wildPokemonIndex].getPokemonName() << " did " << red << sub << reset << " damage to " << player.getActivePokemonName() << endl;
        }

        else {
            cout << wildPokemon[wildPokemonIndex].getPokemonName() << "'s attack had " << cyan << "no effect" << reset << "." << endl;
        }
        player.updateActivePokemon();
    }

    else {
        cout << wildPokemon[wildPokemonIndex].getPokemonName() << " attacks first." << endl;
        int randAW = rand() % (int(wildPokemon[wildPokemonIndex].getPokemonAttack()) + 1);
        int randDA = rand() % (int(player.getActivePokemonDefence()) + 1);

        if (randAW > randDA) {
            double sub = randAW - randDA;
            player.decrementActivePokemonHP(sub);
            cout << wildPokemon[wildPokemonIndex].getPokemonName() << " did " << red << sub << reset << " damage to " << player.getActivePokemonName() << endl;
        }

        else {
            cout << wildPokemon[wildPokemonIndex].getPokemonName() << "'s attack had " << cyan << "no effect" << reset << "." << endl;
        }
        player.updateActivePokemon();

        if (player.getActivePokemonHP() <= 0) {
            return;
        }

        cout << "Your turn to attack now." << endl;
        int randAA = rand() % (int(player.getActivePokemonAttack()) + 1);
        int randDW = rand() % (int(wildPokemon[wildPokemonIndex].getPokemonDefence()) + 1);

        if (randAA > randDW) {
            double sub = randAA - randDW;
            wildPokemon[wildPokemonIndex].decrementPokemonHP(sub);
            cout << "You did " << green << sub << reset << " damage to " << wildPokemon[wildPokemonIndex].getPokemonName() << endl;
        }

        else {
            cout << "Your attack had " << cyan << "no effect" << reset << " on " << wildPokemon[wildPokemonIndex].getPokemonName() << endl;
        }
    }
}

bool Location::runWildPokemon() {
    player.incrementEscapeAttempt();
    if (player.getActivePokemonSpeed() > wildPokemon[wildPokemonIndex].getPokemonSpeed()) {
        return true;
    }

    else {
        double a = player.getActivePokemonSpeed();
        double b = (wildPokemon[wildPokemonIndex].getPokemonSpeed() / 4.0);
        double c = player.getEscapeAttempt();
        double f = ((a * 32) / b) * (30 * c);

        if (f > 255) {
            return true;
        }

        else {
            int random = rand() % 256;
            if (f > random) {
                return true;
            }

            else {
                return false;
            }
        }
    }
}

void Location::removeWildPokemon(int index) {
    wildPokemon.erase(wildPokemon.begin() + index);
}

void Location::viewWildPokemonStats() {
    string bold = "\e[1m";
    string reset = "\e[0m\e[39m\e[49m";
    cout << bold << "Name: " << wildPokemon[wildPokemonIndex].getPokemonName() << reset << ", ";
    cout << "HP: " << wildPokemon[wildPokemonIndex].getPokemonHP() << "/" << wildPokemon[wildPokemonIndex].getPokemonMaxHP() << ", ";
    cout << "Attack: " << wildPokemon[wildPokemonIndex].getPokemonAttack() << ", ";
    cout << "Defence: " << wildPokemon[wildPokemonIndex].getPokemonDefence() << ", ";
    cout << "Speed: " << wildPokemon[wildPokemonIndex].getPokemonSpeed() << ", ";
    cout << "Max: " << wildPokemon[wildPokemonIndex].getPokemonMax() << ", ";
    cout << "Level: " << wildPokemon[wildPokemonIndex].getPokemonLevel() << ", ";
    cout << "Type: ";
    vector<string> tempType = wildPokemon[wildPokemonIndex].getPokemonType();
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

bool Location::tryYourLuck() {
    int x = player.getx_Cor();
    int y = player.gety_Cor();
    int counter = 0;

    for (int i = x - 3; i <= x + 3; i++) {
        for (int j = y - 3; j <= y + 3; j++) {
            if (i < 0 || i >= 25 || j < 0 || j >= 16) {
                continue;
            }

            else {
                for (int k = 0; k < wildPokemon.size(); k++) {
                    int x1 = wildPokemon[k].getx_Cor();
                    int y1 = wildPokemon[k].gety_Cor();

                    if (i == x1 && j == y1) {
                        wildPokemonIndex = k;
                        counter++;
                    }
                }
            }
        }
    }

    if (counter > 0) {
        return true;
    }

    else {
        return false;
    }
}

int Location::fightTrainer(int index) {
    string red = "\e[31m";
    string green = "\e[32m";
    string cyan = "\e[96m";
    string reset = "\e[0m\e[39m\e[49m";

    double playerSpeed = player.getActivePokemonSpeed();
    double trainerSpeed = trainers[index].getActivePokemonSpeed();

    if (playerSpeed >= trainerSpeed) {
        cout << "You attack first." << endl;
        int randPA = rand() % int(player.getActivePokemonAttack() + 1);
        int randTD = rand() % int(trainers[index].getActivePokemonDefence() + 1);

        if (randPA > randTD) {
            double sub = randPA - randTD;
            trainers[index].decrementActivePokemonHP(sub);
            cout << "You did " << green << sub << reset << " damage to " << trainers[index].getActivePokemonName() << endl;
        }

        else {
            cout << "Your attack had " << cyan << "no effect" << reset <<  " on " << trainers[index].getActivePokemonName() << endl;
        }

        if (trainers[index].getActivePokemonHP() <= 0) {
            return 1;
        }

        cout << trainers[index].getActivePokemonName() << " now attacks." << endl;
        int randTA = rand() % int(trainers[index].getActivePokemonAttack() + 1);
        int randPD = rand() % int(player.getActivePokemonDefence() + 1);

        if (randTA > randPD) {
            double sub = randTA - randPD;
            player.decrementActivePokemonHP(sub);
            cout << trainers[index].getActivePokemonName() << " did " << red << sub << reset << " damage to " << player.getActivePokemonName() << endl;
        }

        else {
            cout << trainers[index].getActivePokemonName() << "'s attack had " << cyan << "no effect" << reset << "." << endl;
        }
        player.updateActivePokemon();

        if (player.getActivePokemonHP() <= 0) {
            return 2;
        }
    }

    else {
        cout << trainers[index].getActivePokemonName() << " attacks first." << endl;
        int randTA = rand() % int(trainers[index].getActivePokemonAttack() + 1);
        int randPD = rand() % int(player.getActivePokemonDefence() + 1);

        if (randTA > randPD) {
            double sub = randTA - randPD;
            player.decrementActivePokemonHP(sub);
            cout << trainers[index].getActivePokemonName() << " did " << red << sub << reset << " damage to " << player.getActivePokemonName() << endl;
        }

        else {
            cout << trainers[index].getActivePokemonName() << "'s attack had " << cyan << "no effect" << reset << "." << endl;
        }
        player.updateActivePokemon();

        if (player.getActivePokemonHP() <= 0) {
            return 2;
        }

        cout << "Your turn to attack now." << endl;
        int randPA = rand() % int(player.getActivePokemonAttack() + 1);
        int randTD = rand() % int(trainers[index].getActivePokemonDefence() + 1);

        if (randPA > randTD) {
            double sub = randPA - randTD;
            trainers[index].decrementActivePokemonHP(sub);
            cout << "You did " << green << sub << reset << " damage to " << trainers[index].getActivePokemonName() << endl;
        }

        else {
            cout << "Your attack had " << cyan << "no effect" << reset <<  " on " << trainers[index].getActivePokemonName() << endl;
        }

        if (trainers[index].getActivePokemonHP() <= 0) {
            return 1;
        }
    }
    return 0;
}

void Location::defeatTrainer(int index) {
    player.addBadge(trainers[index].getBadge());
    trainers[index].setState(false);
    player.incrementPokeballs(5);
    player.incrementPoints(60);
}

// After every turn
void Location::update() {
    system("clear");
    updateWildPokemonLocation();
    showMiniMap();
    findTreasure();
    randomDeath();
    showActiveStats();
}

void Location::updateWildPokemonLocation() {
    // cout << "In wild pokemon update" << endl;
    int z = 0;

    for (int i = 0; i < wildPokemon.size(); i++) {
        int random = rand() % 4;
        int x = wildPokemon[i].getx_Cor();
        int y = wildPokemon[i].gety_Cor();
        int counter = 0;
        if(z > 15) {
            // cout << wildPokemon[i].getPokemonName() << " can't be updated at this moment" << endl;
            z = 0;
            continue;
        }

        switch(random) {
            case 0: x++; break;
            case 1: x--; break;
            case 2: y++; break;
            case 3: y--; break;
        }
        string G = "G";
        G += 13;
        string C = "C";
        C += 13;
        string tilde = "~";
        tilde += 13;

        if (x < 0 || x >= 25 || y < 0 || y >= 16) {
            i--; z++; continue;
        }

        else if (map[x][y] == "G" || map[x][y] == "C" || map[x][y] == "~" || map[x][y] == G || map[x][y] == C || map[x][y] == tilde) {
            i--; z++; continue;
        }

        for (int j = 0; j < wildPokemon.size(); j++) {
            if (i != j) {
                int x1 = wildPokemon[j].getx_Cor();
                int y1 = wildPokemon[j].gety_Cor();

                if (x == x1 && y == y1) {
                    counter++;
                }
            }
        }

        if (counter > 0) {
            i--; z++; continue;
        }

        else {
            wildPokemon[i].setx_Cor_y_Cor(x, y);
            z = 0;
            // cout << "Wild Pokemon " << wildPokemon[i].getPokemonName() << " has been updated index: " << i << endl;
        }
    }
    // cout << "At the end" << endl;
}

void Location::showMiniMap() {
    int x = player.getx_Cor();
    int y = player.gety_Cor();
    cout << "Mini Map: " << endl;

    string red = "\e[31m";
    string magenta = "\e[35m";
    string green = "\e[32m";
    string cyan = "\e[96m";
    string yellow = "\e[33m";
    string gray = "\e[37m";
    string reset = "\e[0m\e[39m\e[49m";

    string G = "G"; G += 13;
    string C = "C"; C += 13;
    string tilde = "~"; tilde += 13;
    string star = "*"; star += 13;

    for (int i = x - 3; i <= x + 3; i ++) {
        for (int j = y - 3; j <= y + 3; j++) {
            if (i < 0 || i >= 25 || j < 0 || j >= 16) {
                if (j == y + 3) {
                    cout << red << "#" << reset;
                }

                else {
                    cout << red << "#  " << reset;
                }
            }

            else if (j == y + 3) {
                if (map[i][j] == "*" || map[i][j] == star) {
                    cout << green << map[i][j] << reset;
                }
                else if (map[i][j] == "~" || map[i][j] == tilde) {
                    cout << cyan << map[i][j] << reset;
                }
                else if (map[i][j] == "C" || map[i][j] == C) {
                    cout << magenta << map[i][j] << reset;
                }
                else if (map[i][j] == "G" || map[i][j] == G) {
                    if (trainers[getTrainerIndexAt(i, j)].getState()) {
                        cout << yellow << map[i][j] << reset;
                    }
                    else {
                        cout << gray << map[i][j] << reset;
                    }
                }
            }

            else if (i == x && j == y) {
                cout << "@  ";
            }

            else {
                if (map[i][j] == "*" || map[i][j] == star) {
                    cout << green << map[i][j] << "  " << reset;
                }
                else if (map[i][j] == "~" || map[i][j] == tilde) {
                    cout << cyan << map[i][j] << "  " << reset;
                }
                else if (map[i][j] == "C" || map[i][j] == C) {
                    cout << magenta << map[i][j] << "  " << reset;
                }
                else if (map[i][j] == "G" || map[i][j] == G) {
                    if (trainers[getTrainerIndexAt(i, j)].getState()) {
                        cout << yellow << map[i][j] << "  " << reset;
                    }
                    else {
                        cout << gray << map[i][j] << "  " << reset;
                    }
                }
            }
        }
        cout << endl;
    }
}

char Location::checkPlayerLocation() {
    int x = player.getx_Cor();
    int y = player.gety_Cor();
    string place = map[x][y];
    string C = "C";
    C += 13;
    string G = "G";
    G += 13;

    if (place == "C" || place == C) {
        return 'C';
    }

    else if (place == "G" || place == G) {
        return 'G';
    }

    else {
        return 'O';
    }
}

void Location::showActiveStats() {
    string bold = "\e[1m";
    string reset = "\e[0m\e[39m\e[49m";
    cout << endl;
    cout << bold << "Active Pokémon: " << player.getActivePokemonName() << reset << ", ";
    cout << "HP: " << player.getActivePokemonHP() << "/" << player.getActivePokemonMaxHP() <<  ", ";
    cout << "Attack: " << player.getActivePokemonAttack() << ", ";
    cout << "Defence: " << player.getActivePokemonDefence() << ", ";
    cout << "Speed: " << player.getActivePokemonSpeed() << ", ";
    cout << "Max: " << player.getActivePokemonMax() << ", ";
    cout << "Level: " << player.getActivePokemonLevel() << ", ";
    cout << "Type: ";
    vector<string> tempType = player.getActivePokemonType();
    for (int i = 0; i < tempType.size(); i++) {
        if (i == tempType.size() - 1) {
            cout << tempType[i];
        }
        else {
            cout << tempType[i] << ", ";
        }
    }
    cout << endl;

    cout << "Pokéballs: " << player.getPokeBalls() << ", ";
    cout << "Points: " << player.getPoints() << ", ";
    cout << "Badges: ";
    vector<string> tempBadges = player.getBadges();
    for (int i = 0; i < tempBadges.size(); i++) {
        if (i == tempBadges.size() - 1) {
            cout << tempBadges[i];
        }

        else {
            cout << tempBadges[i] << ", ";
        }
    }
    cout << endl << endl;
}

bool Location::checkWildPokemon() {
    int x = player.getx_Cor();
    int y = player.gety_Cor();
    int counter = 0;

    for (int i = x - 2; i <= x + 2; i++) {
        for (int j = y - 2; j <= y + 2; j++) {
            if (i < 0 || i >= 25 || j < 0 || j >= 16) {
                continue;
            }

            else {
                for (int k = 0; k < wildPokemon.size(); k++) {
                    int x1 = wildPokemon[k].getx_Cor();
                    int y1 = wildPokemon[k].gety_Cor();

                    if (i == x1 && j == y1) {
                        wildPokemonIndex = k;
                        counter++;
                    }
                }
            }
        }
    }

    if (counter > 0) {
        return true;
    }

    else {
        return false;
    }
}

bool Location::checkWin() {
    if (player.getBadgesSize() == 6) {
        cout << "You have acquired 6 badges." << endl;
        return true;
    }

    else if (player.getDiffTypes() >= 8) {
        cout << "You have acquired Pokémon of 8 different types." << endl;
        return true;
    }

    else {
        return false;
    }
}

bool Location::findTreasure() {
    string underline = "\e[4m";
    string reset = "\e[0m\e[39m\e[49m";

    int random1 = (rand() % 100) + 1;
    if (random1 < 26) {
        int random2 = rand() % 2;

        if (random2 == 0) {
            cout << underline << "Great news! You have found a hidden stash of Pokéballs. Your Pokéballs have been increased by 2." << reset << endl << endl;
            player.incrementPokeballs(2);
            return true;
        }
        else {
            cout << underline << "Great news! You have found a stash of Poffins. Your Pokémon are delighted." << reset << endl;
            bool levelUp = player.incrementSelectPokemonLevel();
            while(!levelUp) {
                cout << "Invalid input." << endl;
                levelUp = player.incrementSelectPokemonLevel();
            }
            return true;
        }
    }

    else {
        return false;
    }
}

bool Location::randomDeath() {
    if (player.getPokemonPartySize() < 2) {
        return false;
    }

    else {
        int random1 = rand() % 10;
        if (random1 < 1) {
            int random2 = rand() % player.getPokemonPartySize();
            player.removePartyPokemon(random2);
            return true;
        }
        else {
            return false;
        }
    }
}

// under the hood
int Location::checkFightWildPokemon() {
    if (player.getActivePokemonHP() <= 0) {
        return 1;
    }

    else if (wildPokemon[wildPokemonIndex].getPokemonHP() <= 0) {
        return 2;
    }

    else {
        return 0;
    }
}

void Location::transferPokemon(Pokemon p) {
    // Pokemon p = getWildPokemon();
    double maxHP = p.getPokemonMaxHP();
    p.setPokemonHP(maxHP);
    player.addPokemon(p);
    // removeWildPokemon(wildPokemonIndex);
}

// for testing purposes
void Location::viewAllPokemon() {
    for (int i = 0; i < allPokemon.size(); i++) {
        cout << "Name: " << allPokemon[i].getPokemonName() << " ";
        cout << "HP: " << allPokemon[i].getPokemonHP() << " ";
        cout << "Attack: " << allPokemon[i].getPokemonAttack() << " ";
        cout << "Defence: " << allPokemon[i].getPokemonDefence() << " ";
        cout << "Speed: " << allPokemon[i].getPokemonSpeed() << " ";
        cout << "Max: " << allPokemon[i].getPokemonMax() << " ";
        cout << "Type: ";
        vector<string> t = allPokemon[i].getPokemonType();

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

void Location::viewMap() {
    int x = player.getx_Cor();
    int y = player.gety_Cor();

    string red = "\e[31m";
    string magenta = "\e[35m";
    string green = "\e[32m";
    string cyan = "\e[96m";
    string yellow = "\e[33m";
    string gray = "\e[37m";
    string blink = "\e[5m";
    string reset = "\e[0m\e[39m\e[49m";

    string G = "G"; G += 13;
    string C = "C"; C += 13;
    string tilde = "~"; tilde += 13;
    string star = "*"; star += 13;

    for (int i = 0; i < 25; i ++) {
        for (int j = 0; j < 16; j++) {
            if (j == 15) {
                int counter = 0;
                for (int k = 0; k < wildPokemon.size(); k++) {
                    if (i == wildPokemon[k].getx_Cor() && j == wildPokemon[k].gety_Cor()) {
                        counter++;
                        break;
                    }
                }
                if (counter > 0) {
                    cout << blink << "?" << reset;
                }
                else if (i == x && j == y) {
                    cout << "@";
                }
                else if (map[i][j] == "*" || map[i][j] == star) {
                    cout << green << map[i][j] << reset;
                }
                else if (map[i][j] == "~" || map[i][j] == tilde) {
                    cout << cyan << map[i][j] << reset;
                }
                else if (map[i][j] == "C" || map[i][j] == C) {
                    cout << magenta << map[i][j] << reset;
                }
                else if (map[i][j] == "G" || map[i][j] == G) {
                    if (trainers[getTrainerIndexAt(i, j)].getState()) {
                        cout << yellow << map[i][j] << reset;
                    }
                    else {
                        cout << gray << map[i][j] << reset;
                    }
                }
            }
            else {
                int counter = 0;
                for (int k = 0; k < wildPokemon.size(); k++) {
                    if (i == wildPokemon[k].getx_Cor() && j == wildPokemon[k].gety_Cor()) {
                        counter++;
                        break;
                    }
                }
                if (counter > 0) {
                    cout << blink << "?" << reset << "  ";
                }
                else if (i == x && j == y) {
                    cout << "@" << "  ";
                }
                else if (map[i][j] == "*" || map[i][j] == star) {
                    cout << green << map[i][j] << "  " << reset;
                }
                else if (map[i][j] == "~" || map[i][j] == tilde) {
                    cout << cyan << map[i][j] << "  " << reset;
                }
                else if (map[i][j] == "C" || map[i][j] == C) {
                    cout << magenta << map[i][j] << "  " << reset;
                }
                else if (map[i][j] == "G" || map[i][j] == G) {
                    if (trainers[getTrainerIndexAt(i, j)].getState()) {
                        cout << yellow << map[i][j] << "  " << reset;
                    }
                    else {
                        cout << gray << map[i][j] << "  " << reset;
                    }
                }
            }

            // else {
            //     cout << map[i][j] << " ";
            // }
        }
        cout << endl;
    }
}

void Location::viewWildPokemon() {
    for (int i = 0; i < wildPokemon.size(); i++) {
        cout << "Name: " << wildPokemon[i].getPokemonName() << " ";
        cout << "HP: " << wildPokemon[i].getPokemonHP() << " ";
        cout << "Attack: " << wildPokemon[i].getPokemonAttack() << " ";
        cout << "Defence: " << wildPokemon[i].getPokemonDefence() << " ";
        cout << "Speed: " << wildPokemon[i].getPokemonSpeed() << " ";
        cout << "Max: " << wildPokemon[i].getPokemonMax() << " ";
        cout << "Type: ";
        vector<string> t = wildPokemon[i].getPokemonType();

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

void Location::viewTrainerPokemon() {
    for (int i = 0; i < 15; i++) {
        cout << "Trainer " << i + 1 << " suite: " << endl;
        trainers[i].viewPokemon();
        cout << endl << endl;
    }
}

void Location::viewTrainerLocations() {
    for (int i = 0; i < 15; i++) {
        cout << "Trainer " << i + 1 << " Location: ";
        cout << "(" << trainers[i].getx_Cor() << "," << trainers[i].gety_Cor() << ")" << endl;
    }
}

void Location::viewWildPokemonLocations() {
    for (int i = 0; i < wildPokemon.size(); i++) {
        cout << "Name: " << wildPokemon[i].getPokemonName() << " ";
        cout << "Location: " << "(" << wildPokemon[i].getx_Cor() << "," << wildPokemon[i].gety_Cor() << ")" << endl;
    }
}

void Location::viewPlayerLocation() {
    cout << "Player Location: (" << player.getx_Cor() << "," << player.gety_Cor() << ")" << endl;
}