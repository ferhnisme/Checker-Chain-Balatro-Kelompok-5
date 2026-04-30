#include <iostream>
#include <cstdlib>
#include <ctime>
#include "HandGenerator.h"

Hand HandGenerator::generateHand(){
    std::cout << "Generating cards for player...\n";
    Hand hand;
    
    // Seed random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // Clear existing values and generate 5 random cards
    hand.cardValues.clear();
    hand.suits.clear();
    
    // Nilai kartu: 2-14 (2-10, J=11, Q=12, K=13, A=14)
    // Suit: 0=Spade, 1=Heart, 2=Diamond, 3=Club
    for (int i = 0; i < 5; i++) {
        hand.cardValues.push_back(2 + (std::rand() % 13)); // 2-14
        hand.suits.push_back(std::rand() % 4); // 0-3
    }
    
    std::cout << "Generated hand with values: ";
    for (int v : hand.cardValues) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    
    return hand;
}