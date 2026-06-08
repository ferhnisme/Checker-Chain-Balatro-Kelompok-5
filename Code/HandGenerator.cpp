#include <iostream>
#include <random>
#include "HandGenerator.h"

HandGenerator::HandGenerator(){
    nextCardIndex = 0;
    initializeDeck();
}

void HandGenerator::initializeDeck(){
    deck.clear();
    deck.reserve(52);

    for (int suit = 0; suit < 4; ++suit) {
        for (int value = 2; value <= 14; ++value) {
            deck.push_back(Card{value, suit});
        }
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);
}

void HandGenerator::resetDeck(){
    initializeDeck();
    nextCardIndex = 0;
}

Hand HandGenerator::generateHand(){
    const int handSize = 8;
    std::cout << "Generating cards for player...\n";
    if (deck.size() - nextCardIndex < handSize) {
        std::cout << "Not enough cards left in deck for a full hand.\n";
        return Hand();
    }

    Hand hand;
    hand.cardValues.clear();
    hand.suits.clear();
    hand.cardValues.reserve(handSize);
    hand.suits.reserve(handSize);

    for (int i = 0; i < handSize; ++i) {
        const Card& card = deck[nextCardIndex++];
        hand.cardValues.push_back(card.value);
        hand.suits.push_back(card.suit);
    }

    std::cout << "Generated hand with values: ";
    for (int v : hand.cardValues) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    return hand;
}