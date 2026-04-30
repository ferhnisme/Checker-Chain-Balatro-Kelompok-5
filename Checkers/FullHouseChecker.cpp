<<<<<<< Updated upstream
=======
#include <iostream>
#include "FullHouseChecker.h"

bool isFullHouse(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    bool hasThree = false;
    bool hasTwo = false;
    for (int count : counts) {
        if (count == 3) hasThree = true;
        if (count == 2) hasTwo = true;
    }
    return hasThree && hasTwo;
}

HandRank FullHouseChecker::check(const Hand& hand){
    if (isFullHouse(hand)){
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
