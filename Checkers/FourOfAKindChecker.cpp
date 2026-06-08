#include <iostream>
#include "FourOfAKindChecker.h"

bool isFourOfAKind(const Hand& hand){
    if (hand.cardValues.size() < 4) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    for (int count : counts) {
        if (count == 4) return true;
    }
    return false;
}

HandRank FourOfAKindChecker::check(const Hand& hand){
    if (isFourOfAKind(hand)){
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}