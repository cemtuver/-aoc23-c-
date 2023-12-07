#include <iostream>
#include <string>

const int HAND_SIZE = 5;
const int CARD_COUNT = 15;
const int KIND_COUNT = 5;
const int KIND_FIVE = 4;
const int KIND_FOUR = 3;
const int KIND_THREE = 2;
const int KIND_TWO = 1;

class Hand {
    public:
        int bid = 0;
        std::string cardsString;
        bool jokersEnabled;
        int numberOfJokers;
        int cards[HAND_SIZE]; 
        std::vector<int> kinds[KIND_COUNT];

        Hand(const std::string& cardsString, int bid): Hand(cardsString, bid, false) {
        };

        Hand(const std::string& cardsString, int bid, bool jokersEnabled) {
            this->bid = bid;
            this->cardsString = cardsString;
            this->jokersEnabled = jokersEnabled;
            this->numberOfJokers = 0;
            this->fillCards(cardsString);
            this->fillKinds();
        };

        void print() {
            std::cout << this->cardsString << " bid:" << this->bid << std::endl;

            for (int i = 0; i < KIND_COUNT; i++) {
                std::cout << i + 1 << ": ";
                
                for (int card : this->kinds[i]) {
                    std::cout << card << " ";
                }

                std::cout << std::endl;
            }
        }

    private:
        void fillCards(const std::string& cardsString) {
            for (int i = 0; i < cardsString.length(); i++) {
                int cardInt;
                char card = cardsString[i];

                if (card == 'A') {
                    cardInt = 14;
                } else if (card == 'K') {
                    cardInt = 13;
                } else if (card == 'Q') {
                    cardInt = 12;
                } else if (card == 'J') {
                    if (this->jokersEnabled) {
                        cardInt = 1;
                    } else {
                        cardInt = 11;
                    }

                    this->numberOfJokers++;
                } else if (card == 'T') {
                    cardInt = 10;
                } else {
                    cardInt = card - '0';
                }

                cards[i] = cardInt;
            }
        };

        void fillKinds() {
            int numberOfCards[CARD_COUNT];

            for (int i = 0; i < CARD_COUNT; i++) {
                numberOfCards[i] = 0;
            }

            for (int i = 0; i < HAND_SIZE; i++) {
                numberOfCards[cards[i]] += 1;
            }

            for (int i = CARD_COUNT - 1; i >= 0; i--) {
                if (this->jokersEnabled && i == 1) {
                    continue;
                }

                if (numberOfCards[i] > 1) {
                    kinds[numberOfCards[i] - 1].push_back(i);
                }
            }
        }
};