#include <iostream>
#include <vector>
#include "../lib/Input.hpp"

using namespace std;

struct gameSet { int red; int green; int blue; };
gameSet parseGameSet(const string& setString);

int main() {
    int result = 0;

    for (string line : input::readLines("input.txt")) {
        int maxRed = 0, maxGreen = 0, maxBlue = 0;
        line.erase(0, 5);
        vector<string> gameStrings = input::split(line, ": ");
        vector<string> setStrings = input::split(gameStrings.at(1), "; ");
        
        for (string setString : setStrings) {
            gameSet gameSet = parseGameSet(setString);

            if (gameSet.red > maxRed) {
                maxRed = gameSet.red;
            }

            if (gameSet.green > maxGreen) {
                maxGreen = gameSet.green;
            }

            if (gameSet.blue > maxBlue) {
                maxBlue = gameSet.blue;
            }
        }

        result += maxRed * maxGreen * maxBlue;
    }

    cout << result << endl;

    return 0;
}

gameSet parseGameSet(const string& setString) {
    gameSet gameSet;
    gameSet.red = 0;
    gameSet.green = 0;
    gameSet.blue = 0; 
    vector<string> cubes = input::split(setString, ", ");

    for (string cube : cubes) {
        vector<string> tokens = input::split(cube, " ");
        int count = stoi(tokens.at(0));
        string color = tokens.at(1);

        if (color == "red") {
            gameSet.red = count;
        } else if (color == "green") {
            gameSet.green = count;
        } else if (color == "blue") {
            gameSet.blue = count;
        }
    }

    return gameSet;
}