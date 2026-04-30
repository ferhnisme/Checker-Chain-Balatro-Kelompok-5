<<<<<<< Updated upstream
=======
#include <iostream>
#include "TwoPairChecker.h"

bool isTwoPair(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    int pairCount = 0;
    for (int count : counts) {
        if (count == 2) pairCount++;
    }
    return pairCount == 2;
}

HandRank TwoPairChecker::check(const Hand& hand){
    if (isTwoPair(hand)){
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
