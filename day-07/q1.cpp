#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "Hand.cpp"

using namespace std;
bool beats(const Hand& hand, const Hand& other);
int calculateScore(const Hand& hand);

int main() {
    Perf perf;
    int result = 0;
    vector<Hand> hands;

    for (string line : input::readLines("input.txt")) {
        vector<string> parts = input::split(line, " ");
        hands.push_back(Hand(parts.at(0), stoi(parts.at(1))));
    }

    sort(hands.begin(), hands.end(), [](const Hand& left, const Hand& right) {
        return beats(left, right);
    });

    int rank = hands.size();
    for (Hand hand : hands) {
        result += rank * hand.bid;
        rank--;
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}

bool beats(const Hand& hand, const Hand& other) {
    int score = calculateScore(hand);
    int otherScore = calculateScore(other);

    if (score == otherScore) {
        for (int i = 0; i < HAND_SIZE; i++) {
            if (hand.cards[i] == other.cards[i]) {
                continue;
            }

            return hand.cards[i] > other.cards[i];
        }
    }

    return score > otherScore;
}

int calculateScore(const Hand& hand) {
    const vector<int>* kinds = hand.kinds;

    if (kinds[KIND_FIVE].size() == 1) return 7;
    if (kinds[KIND_FOUR].size() == 1) return 6;
    if (kinds[KIND_THREE].size() == 1 && kinds[KIND_TWO].size() == 1) return 5;
    if (kinds[KIND_THREE].size() == 1) return 4;
    if (kinds[KIND_TWO].size() == 2) return 3;
    if (kinds[KIND_TWO].size() == 1) return 2;

    return 1;
}
