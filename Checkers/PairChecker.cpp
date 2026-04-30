#include <iostream>
#include "PairChecker.h"

bool isPair(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    for (int count : counts) {
        if (count == 2) return true;
    }
    return false;
}

HandRank PairChecker::check(const Hand& hand){
    if (isPair(hand)){
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}