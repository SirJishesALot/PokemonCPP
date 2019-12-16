#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "Player.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Location.h"

using namespace std;
// g++ -o pokemonGame -std=c++11 Player.cpp Pokemon.cpp Trainer.cpp Location.cpp pokemonDriver.cpp

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

void displayInstructions() {
    string red = "\e[31m";
    string magenta = "\e[35m";
    string green = "\e[32m";
    string cyan = "\e[96m";
    string yellow = "\e[33m";
    string gray = "\e[37m";
    string underline = "\e[4m";
    string reset = "\e[0m\e[39m\e[49m";

    cout << "The aim of the game is to explore the world around you and catch as many Pokémon as you can." << endl;
    cout << underline << "There are two ways to win the game:"  << reset << endl;
    cout << "   1. Capture Pokémon of 8 different types." << endl;
    cout << "   2. Defeat 6 Gym Leaders." << endl << endl;
    cout << "You begin the game with a starter Pokémon which is made your Active Pokémon by default." << endl;
    cout << "At any point in time you can have at most 6 Pokémon in your Party." << endl;
    cout << "You will only be able to switch between these Pokémon during battle, so choose your Party wisely." << endl;
    cout << "Any other Pokémon you may have are stored in your Pokédex." << endl;
    cout << "You can change your party at Pokémon Centres." << endl << endl;
    cout << "You start the game with 10 Pokéballs." << endl;
    cout << "Defeating a Gym Leader grants you 60 points, 5 Pokéballs, and a badge." << endl;
    cout << "If you choose to fight a Gym Leader, you cannot run away during the battle." << endl;
    cout << "Capturing a Wild Pokémon uses up a Pokéball and grants you 10 points." << endl;
    cout << "You must fully defeat a Pokémon if you want to capture it." << endl;
    cout << "You automatically capture the first two Wild Pokémon that you encounter." << endl << endl;
    cout << "Gym Leaders can be found at Pokémon Gyms." << endl;
    cout << "You can heal all your Pokémon at Pokémon Centres." << endl << endl;
    cout << underline << "Mini Map Key:" << reset << endl;
    cout << "   " << yellow << "'G'" << reset << " --> Undefeated Pokémon Gym." << endl;
    cout << "   " << gray << "'G'" << reset << " --> Defeated Pokémon Gym." << endl;
    cout << "   " << magenta << "'C'" << reset << " --> Pokémon Centre." << endl;
    cout << "   '@' --> Player's current location." << endl;
    cout << "   " << green << "'*'" << reset << " --> Land tile." << endl;
    cout << "   " << cyan << "'~'" << reset << " --> Water tile." << endl;
    cout << "The Mini Map only shows you a portion of the Map, so make sure to explore as much as you can." << endl;
    cout << endl << underline << "Special commands:" << reset << endl;
    cout << "   'Rest' --> Increases the HP of all the Pokémon in your Party by 1 and causes you to lose a Pokéball." << endl;
    cout << "   'Try your luck' --> If there are any Wild Pokémon within the confines of the Mini Map, you have a 50% chance of capturing it." << endl;
    cout << "   'Show map' --> Shows the entire map and reveals the locations of all the Wild Pokémon. Uses up 5 Pokéballs." << endl << endl;
    cout << "Be sure to look out for random events that happen throughout the game." << endl;
    cout << underline << "Press the number beside the option to choose that option." << reset << endl;
    cout << endl << "Good luck and have fun!" << endl;
}

void displayTopPlayers() {
    ifstream file;
    file.open("resultsPokemon.txt");
    string line;
    vector<double> points;
    vector<string> users;
    int n = 0;

    while(getline(file, line)) {
        if (n == 0) {
            n++;
            continue;
        }

        else {
            vector<string> temp = split(line, '\t');
            if (temp[1] == "Lost") {
                continue;
            }

            users.push_back(temp[0]);
            points.push_back(atof(temp[2].c_str()));
        }
    }

    // sorting algorithm
    bool sorted = false;
    while (!sorted) {
        int counter = 0;
        for (int i = 0; i < users.size() - 1; i++) {
            if (points[i] < points[i + 1]) {
                double tempPoint = points[i + 1];
                points[i + 1] = points[i];
                points[i] = tempPoint;

                string tempUser = users[i + 1];
                users[i + 1] = users[i];
                users[i] = tempUser;
                counter++;
            }
        }
        if (counter == 0) {
            sorted = true;
        }
    }

    cout << "The top 5 players who have won are: " << endl;
    int x;
    if (users.size() < 5) {
        x = users.size();
    }
    else {
        x = 5;
    }

    for (int i = 0; i < x; i++) {
        if (users[i].length() > 8) {
            cout << "   " << i + 1 << ". " << users[i] << "\t" << "Points: " << points[i] << endl;
        }
        else {
            cout << "   " << i + 1 << ". " << users[i] << "\t\t" << "Points: " << points[i] << endl;
        }
    }
}

void displayMainChoice() {
    cout << "Please choose from the following options:" << endl;
    cout << "   1. Travel" << endl;
    cout << "   2. Rest" << endl;
    cout << "   3. Try your luck" << endl;
    cout << "   4. Show map" << endl;
    cout << "   5. Quit the game" << endl;
}

void displayDirection() {
    cout << endl;
    cout << "   'w' to go north" << endl;
    cout << "   's' to go south" << endl;
    cout << "   'a' to go west" << endl;
    cout << "   'd' to go east" << endl;
}

int main() {
    string underline = "\e[4m";
    string reset = "\e[0m\e[39m\e[49m";
    string bold = "\e[1m";
    system("clear");
    srand(time(0));
    Location myLocation;
    
    string playerName;
    cout << "Welcome to Pokémon!" << endl;
    cout << "Would you like to read the instructions?" << endl;

    bool instructions = true;
    while (instructions) {
        cout << "Press 'y' for yes, or 'n' for no." << endl;
        system("stty raw");
        char choiceInstructions = getchar();
        system("stty cooked");

        if (choiceInstructions == 'Y' || choiceInstructions == 'y') {
            cout << endl;
            displayInstructions();
            instructions = false;
        }
        else if (choiceInstructions == 'N' || choiceInstructions == 'n') {
            instructions = false;
        }
        else {
            cout << "Invalid input." << endl << endl;
        }
    }

    bool first = true;
    while (first) {
        cout << endl << "Please state your name: " << endl;
        getline(cin, playerName);
        if (playerName.length() > 14) {
            cout << "Your player's name cannot exceed 14 characters." << endl;
        }
        else {
            first = false;
        }
    }
    bool pokemonInitial = false;
    myLocation.player.setPlayerName(playerName);
    cout << endl << "Welcome, " << playerName << "! Before you can begin your Pokémon adventure, you must choose a starting Pokémon, courtesy of the Professor." << endl;

    while (!pokemonInitial) {
        cout << "Please choose from the following Pokémon: " << endl;
        cout << "   1. Bulbasaur." << endl;
        cout << "   2. Charmander." << endl;
        cout << "   3. Squirtle." << endl;
        cout << "   4. Pikachu." << endl;
        system("stty raw");
        char pokemonChoice = getchar();
        system("stty cooked");

        if (pokemonChoice == '1') {
            Pokemon p = myLocation.getPokemon("Bulbasaur");
            myLocation.player.addPokemon(p);
            myLocation.player.setActivePokemon(p);
            cout << "You have chosen Bulbasaur as your starting Pokémon." << endl;
            myLocation.setPlayerLocation(12, 6);
            pokemonInitial = true;
        }

        else if (pokemonChoice == '2') {
            Pokemon p = myLocation.getPokemon("Charmander");
            myLocation.player.addPokemon(p);
            myLocation.player.setActivePokemon(p);
            cout << "You have chosen Charmander as your starting Pokémon." << endl;
            myLocation.setPlayerLocation(12, 7);
            pokemonInitial = true;
        }

        else if (pokemonChoice == '3') {
            Pokemon p = myLocation.getPokemon("Squirtle");
            myLocation.player.addPokemon(p);
            myLocation.player.setActivePokemon(p);
            cout << "You have chosen Squirtle as your starting Pokémon." << endl;
            myLocation.setPlayerLocation(12, 8);
            pokemonInitial = true;
        }

        else if (pokemonChoice == '4') {
            Pokemon p = myLocation.getPokemon("Pikachu");
            myLocation.player.addPokemon(p);
            myLocation.player.setActivePokemon(p);
            cout << "You have chosen Pikachu as your starting Pokémon." << endl;
            myLocation.setPlayerLocation(12, 9);
            pokemonInitial = true;
        }

        else {
            cout << "Invalid input." << endl << endl;
        }
    }

    bool run = true;
    while (run) {
        bool allFaint = false;
        bool runFromWild = false;

        start:
        myLocation.update();
        char locationValue = myLocation.checkPlayerLocation();

        if (locationValue == 'C') {
            if (allFaint) {
                cout << "All the Pokémon in your Party have fainted. You have been taken to the nearest Pokémon Centre." << endl << endl;
            }
            else if (runFromWild) {
                cout << "You have managed to escape." << endl << endl;
            }
            bool pokemonCentre = true;
            while (pokemonCentre) {
                myLocation.player.healPokemonPartyCentre();
                cout << "Welcome to the Pokémon Centre. All Pokémon in your Party have been healed. Do you want to change the members of your Party? (y/n): " << endl;

                system("stty raw");
                char choice = getchar();
                system("stty cooked");

                if (choice == 'y') {
                    cout << endl << underline << "Please enter the number of the Pokémon separated by a space." << reset << endl;
                    bool switchPartyValue = myLocation.player.switchPartyPokemon();

                    if (switchPartyValue) {
                        cout << endl << "Your Party has been edited successfully." << endl << endl;
                        cout << "Your Party now looks like this: " << endl;
                        myLocation.player.viewPartyPokemon();
                        cout << endl;
                        pokemonCentre = false;
                    }

                    else {
                        cout << "Invalid input." << endl;
                        continue;
                    }
                }

                else if (choice == 'n') {
                    pokemonCentre = false;
                }

                else {
                    cout << "Invalid input." << endl << endl;
                    continue;
                }
            }
        }

        else if (locationValue == 'G') {
            bool pokemonGym = true;
            while (pokemonGym) {
                int gymLeaderIndex = myLocation.getTrainerIndexAt(myLocation.player.getx_Cor(), myLocation.player.gety_Cor());
                bool trainerState = myLocation.getTrainerStateAt(gymLeaderIndex);
                if(!trainerState) {
                    cout << underline << "You have already defeated this Gym's leader." << reset << endl;
                    pokemonGym = false;
                }

                else {
                    cout << underline << "You arrive at the Gym and the leader is present. They want to fight." << reset << endl;
                    myLocation.trainers[gymLeaderIndex].setActivePokemon();

                    bool trainerFight = true;
                    while (trainerFight) {
                        cout << endl;
                        cout << "They have " << bold << myLocation.trainers[gymLeaderIndex].getTotalPokemonSize() << reset << " Pokémon in their Party." << endl;
                        cout << "Their active Pokémon is: " << endl;
                        myLocation.trainers[gymLeaderIndex].viewActivePokemon();
                        myLocation.showActiveStats();
                        cout << "What would you like to do?" << endl;
                        cout << "   1. Fight" << endl;
                        cout << "   2. Switch active Pokémon" << endl;

                        system("stty raw");
                        char choice = getchar();
                        system("stty cooked");

                        if (choice == '1') {
                            int fightValue = myLocation.fightTrainer(gymLeaderIndex);

                            if (fightValue == 1) {
                                cout << underline << "You have defeated " << myLocation.trainers[gymLeaderIndex].getActivePokemonName() << reset << endl;
                                myLocation.player.incrementActivePokemonLevel();
                                myLocation.transferPokemon(myLocation.trainers[gymLeaderIndex].getActivePokemon());
                                bool updateValue = myLocation.trainers[gymLeaderIndex].updateActivePokemon();

                                if(!updateValue) {
                                    cout << underline << "You have defeated the Gym leader. They present you with their badge." << reset << endl;
                                    myLocation.defeatTrainer(gymLeaderIndex);
                                    myLocation.showMiniMap();
                                    trainerFight = false;
                                }
                            }

                            else if (fightValue == 2) {
                                cout << underline << "Your active Pokémon has fainted." << reset << endl;
                                myLocation.trainers[gymLeaderIndex].incrementActivePokemonLevel();
                                bool partyValue = myLocation.player.checkPartyPokemonHP();

                                if (partyValue) {
                                    allFaint = true;
                                    myLocation.teleportPlayer();
                                    goto start;

                                    trainerFight = false;
                                }

                                else {
                                    bool switchValue = myLocation.player.switchActivePokemon();
                                    while (!switchValue) {
                                        cout << "Invalid input." << endl;
                                        switchValue = myLocation.player.switchActivePokemon();
                                    }
                                }
                            }
                        }

                        else if (choice == '2') {
                            bool switchValue = myLocation.player.switchActivePokemon();
                            if (switchValue) {
                                cout << "Your active Pokémon is now: " << bold << myLocation.player.getActivePokemonName() << endl;
                            }

                            else {
                                cout << "Invalid input." << endl << endl;
                                continue;
                            }
                        }

                        else {
                            cout << "Invalid input." << endl << endl;
                            continue;
                        }
                    }
                }
            }
        }

        bool nearWildPokemon = myLocation.checkWildPokemon();
        while (nearWildPokemon) {
            cout << underline << "You have encountered: " << myLocation.getWildPokemonName() << reset << endl << endl;
            myLocation.viewWildPokemonStats();
            myLocation.showActiveStats();

            if (myLocation.player.getWildEncounter() < 2) {
                if (myLocation.player.getPokeBalls() > 0) {
                    cout << underline << myLocation.getWildPokemonName() << " has joined your collection." << reset << endl << endl;
                    myLocation.player.incrementPoints(10);
                    myLocation.player.decrementPokeballs(1);
                    myLocation.transferPokemon(myLocation.getWildPokemon());
                    myLocation.removeWildPokemon(myLocation.getWildPokemonIndex());
                    myLocation.player.incrementWildEncounter();
                    nearWildPokemon = false;
                }
                else {
                    cout << "You have run out of Pokéballs and cannot capture this Pokémon." << endl;
                    myLocation.fleeWildPokemon(true);
                    cout << myLocation.getWildPokemonName() << " ran away." << endl;
                    nearWildPokemon = false;
                }
            }

            else {
                cout << "What would you like to do?" << endl;
                cout << "   1. Fight" << endl;
                cout << "   2. Switch active Pokémon" << endl;
                cout << "   3. Run" << endl;

                system("stty raw");
                char choice = getchar();
                system("stty cooked");

                if (choice == '1') {
                    int random = rand() % 10;
                    if (random > 5) {
                        cout << myLocation.getWildPokemonName() << " wants to flee." << endl;

                        bool fleeWildPokemon = myLocation.fleeWildPokemon(false);

                        if (fleeWildPokemon) {
                            cout << underline << myLocation.getWildPokemonName() << " has escaped." << reset << endl;
                            nearWildPokemon = false;
                        }

                        else {
                            cout << underline << myLocation.getWildPokemonName() << " tried to flee, but failed. They have now joined your collection." << reset << endl;
                            myLocation.player.incrementPoints(10);
                            myLocation.player.decrementPokeballs(1);
                            myLocation.transferPokemon(myLocation.getWildPokemon());
                            myLocation.removeWildPokemon(myLocation.getWildPokemonIndex());
                            myLocation.showMiniMap();
                            nearWildPokemon = false;
                        }
                    }

                    else {
                        myLocation.fightWildPokemon();
                        int fightValue = myLocation.checkFightWildPokemon();

                        if (fightValue == 2) {
                            if (myLocation.player.getPokeBalls() > 0) {
                                cout << underline << "You have defeated " << myLocation.getWildPokemonName() << "." << reset << endl << endl;
                                cout << "Would you like to capture it?" << endl;
                                bool capture = false;
                                while (!capture) {
                                    cout << "Choose from the following options:" << endl;
                                    cout << "   1. Yes" << endl;
                                    cout << "   2. No" << endl;

                                    system("stty raw");
                                    char captureChoice = getchar();
                                    system("stty cooked");

                                    if (captureChoice == '1') {
                                        myLocation.transferPokemon(myLocation.getWildPokemon());
                                        cout << underline << myLocation.getWildPokemonName() << " has now been added to your collection." << reset << endl;
                                        myLocation.removeWildPokemon(myLocation.getWildPokemonIndex());
                                        myLocation.player.incrementPoints(10);
                                        myLocation.player.decrementPokeballs(1);
                                        capture = true;
                                    }
                                    else if (captureChoice == '2') {
                                        myLocation.fleeWildPokemon(true);
                                        myLocation.setWildPokemonMaxHP();
                                        cout << underline << myLocation.getWildPokemonName() << " ran away." << reset << endl;
                                        capture = true;
                                    }
                                    else {
                                        cout << "Invalid input." << endl << endl;
                                    }
                                }
                                myLocation.player.incrementActivePokemonLevel();
                                myLocation.showMiniMap();
                                nearWildPokemon = false;
                            }
                            else {
                                cout << "You have defeated " << myLocation.getWildPokemonName() << " but you have run out of Pokéballs." << endl;
                                myLocation.fleeWildPokemon(true);
                                myLocation.setWildPokemonMaxHP();
                                cout << underline << myLocation.getWildPokemonName() << " ran away." << reset << endl;
                                nearWildPokemon = false;
                            }
                        }

                        else if (fightValue == 1) {
                            cout << underline << "Your active Pokémon has fainted." << reset << endl;
                            myLocation.wildPokemonLevelUp();
                            bool partyValue = myLocation.player.checkPartyPokemonHP();

                            if (partyValue) {
                                allFaint = true;
                                myLocation.teleportPlayer();
                                goto start;
                                nearWildPokemon = false;
                            }

                            else {
                                bool switchValue = myLocation.player.switchActivePokemon();
                                while (!switchValue) {
                                    cout << "Invalid input." << endl;
                                    switchValue = myLocation.player.switchActivePokemon();
                                }
                            }
                        }
                    }
                }

                else if (choice == '2') {
                    bool switchValue = myLocation.player.switchActivePokemon();
                    if (switchValue) {
                        cout << "Your active Pokémon is now " << bold << myLocation.player.getActivePokemonName() << reset << endl;
                    }

                    else {
                        cout << "Invalid input." << endl;
                        continue;
                    }
                }

                else if (choice == '3') {
                    bool runValue = myLocation.runWildPokemon();
                    if (runValue) {
                        myLocation.teleportPlayer();
                        nearWildPokemon = false;
                        runFromWild = true;
                        goto start;
                    }

                    else {
                        cout << underline << "Your escape attempt failed." << reset << endl;
                    }
                }

                else {
                    cout << "Invalid input." << endl << endl;
                    continue;
                }
            }
        }
        start2:
        displayMainChoice();
        system("stty raw");
        char choiceMain = getchar();
        system("stty cooked");

        if (choiceMain == '1') {

            bool travel = true;
            while (travel) {
                displayDirection();
                system("stty raw");
                char choiceD = getchar();
                system("stty cooked"); 

                if (choiceD == 'w' || choiceD == 'W') {
                    int travelValue = myLocation.updatePlayerLocation('w');
                    if (travelValue == 0) {
                        cout << "You cannot go out of the map." << endl;
                        continue;
                    }
                    else if (travelValue == 2) {
                        cout << "You cannot go in water." << endl;
                        continue;
                    }
                    else {
                        travel = false;
                    }
                }

                else if (choiceD == 's' || choiceD == 'S') {
                    int travelValue = myLocation.updatePlayerLocation('s');
                    if (travelValue == 0) {
                        cout << "You cannot go out of the map." << endl;
                        continue;
                    }
                    else if (travelValue == 2) {
                        cout << "You cannot go in water." << endl;
                        continue;
                    }
                    else {
                        travel = false;
                    }
                }

                else if (choiceD == 'a' || choiceD == 'A') {
                    int travelValue = myLocation.updatePlayerLocation('a');
                    if (travelValue == 0) {
                        cout << "You cannot go out of the map." << endl;
                        continue;
                    }
                    else if (travelValue == 2) {
                        cout << "You cannot go in water." << endl;
                        continue;
                    }
                    else {
                        travel = false;
                    }
                }

                else if (choiceD == 'd' || choiceD == 'D') {
                    int travelValue = myLocation.updatePlayerLocation('d');
                    if (travelValue == 0) {
                        cout << "You cannot go out of the map." << endl;
                        continue;
                    }
                    else if (travelValue == 2) {
                        cout << "You cannot go in water." << endl;
                        continue;
                    }
                    else {
                        travel = false;
                    }
                }

                else {
                    cout << "Invalid input." << endl << endl;
                    continue;
                }
            }
        }

        else if (choiceMain == '2') {
            myLocation.player.rest();
            cout << endl << "HP for all Pokémon in Party increased by 1." << endl;
            cout << "Number of Pokéballs decreased by 1." << endl;
            goto start2;
        }

        else if (choiceMain == '3') {
            if (myLocation.player.getPokeBalls() == 0) {
                cout << "You have run out of Pokéballs. You can no longer try your luck." << endl;
                goto start2;
            }
            else {
                bool luckValue = myLocation.tryYourLuck();
                if (!luckValue) {
                    cout << "There are no wild Pokémon around you." << endl;
                    myLocation.player.decrementPokeballs(1);
                    cout << "You have lost 1 Pokéball." << endl;
                }

                else {
                    int random = rand() % 2;
                    if (random == 1) {
                        cout << "You found " << myLocation.getWildPokemonName() << endl;
                        cout << myLocation.getWildPokemonName() << " has joined your Pokémon collection." << endl;
                        myLocation.transferPokemon(myLocation.getWildPokemon());
                        myLocation.removeWildPokemon(myLocation.getWildPokemonIndex());
                    }

                    else {
                        myLocation.fleeWildPokemon(true);
                        cout << "There was a " << myLocation.getWildPokemonName() << " near you, but you failed to catch it. It ran away." << endl;
                    }
                }
                goto start2;
            }
        }

        else if (choiceMain == '4') {
            if (myLocation.player.getPokeBalls() < 5) {
                cout << endl << underline <<  "You don't have enough Pokéballs to see the map." << reset << endl;
                goto start2;
            }
            else {
                myLocation.player.decrementPokeballs(5);
                cout << endl << "Here is the entire map:" << endl;
                myLocation.viewMap();
                cout << endl << underline << "Press any key to continue." << reset << endl;
                system("stty raw");
                char buffer = getchar();
                system("stty cooked");
                continue;
            }
        }

        else if (choiceMain == '5') {
            ofstream file("resultsPokemon.txt", ios_base::app);
            if (playerName.length() >= 8) {
                file << myLocation.player.getPlayerName() << "\t" << "Lost" << "\t\t" << myLocation.player.getPlayerPoints() << endl;
            }
            else {
                file << myLocation.player.getPlayerName() << "\t\t" << "Lost" << "\t\t" << myLocation.player.getPlayerPoints() << endl;
            }
            file.close();
            cout << "Goodbye." << endl;
            run = false;
            continue;
        }

        else {
            cout << "Invalid input." << endl << endl;
            goto start2;
        }

        bool win = myLocation.checkWin();
        if (win) {
            cout << endl;
            cout << bold <<  "You have won the game!" << reset << endl;
            cout << "Player name: " << myLocation.player.getPlayerName() << endl;
            cout << "Points: " << myLocation.player.getPoints() << endl;
            ofstream file("resultsPokemon.txt", ios_base::app);
            if (playerName.length() >= 8) {
                file << myLocation.player.getPlayerName() << "\t" << "Won" << "\t\t" << myLocation.player.getPlayerPoints() << endl;
            }
            else {
                file << myLocation.player.getPlayerName() << "\t\t" << "Won" << "\t\t" << myLocation.player.getPlayerPoints() << endl;
            }
            file.close();
            run = false;
        }
        cout << endl;
    }
    displayTopPlayers();
    cout << endl << "Created by Jishnu Raychaudhuri" << endl;
    cout << "Version: 1.1.0" << endl;
    return 0;
}