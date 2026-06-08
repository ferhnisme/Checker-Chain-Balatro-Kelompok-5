#pragma once
#include <vector>
#include "Hand.h"

class HandGenerator{
public:
    HandGenerator();
    Hand generateHand();
    void resetDeck();

private:
    struct Card {
        int value;
        int suit;
    };

    std::vector<Card> deck;
    size_t nextCardIndex;

    void initializeDeck();
};