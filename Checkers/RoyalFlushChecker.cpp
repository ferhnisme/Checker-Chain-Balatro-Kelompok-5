<<<<<<< Updated upstream
=======
#include <iostream>
#include "RoyalFlushChecker.h"

bool isRoyalFlush(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    if (!hand.isAllSameSuit() || !hand.isConsecutive()) return false;
    
    // Royal flush: 10, J, Q, K, A (10,11,12,13,14)
    std::vector<int> sorted = hand.cardValues;
    std::sort(sorted.begin(), sorted.end());
    return sorted[0] == 10 && sorted[4] == 14;
}

HandRank RoyalFlushChecker::check(const Hand& hand){
    if (isRoyalFlush(hand)){
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
