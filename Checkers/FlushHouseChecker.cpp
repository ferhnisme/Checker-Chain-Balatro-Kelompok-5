<<<<<<< Updated upstream
=======
#include <iostream>
#include "FlushHouseChecker.h"

bool isFlushHouse(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    // Flush House: Flush (sama suit) + Full House (3+2)
    if (!hand.isAllSameSuit()) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    bool hasThree = false;
    bool hasTwo = false;
    for (int count : counts) {
        if (count == 3) hasThree = true;
        if (count == 2) hasTwo = true;
    }
    return hasThree && hasTwo;
}

HandRank FlushHouseChecker::check(const Hand& hand){
    if (isFlushHouse(hand)){
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
