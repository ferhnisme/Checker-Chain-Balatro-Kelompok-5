#include <iostream>
#include "StraightFlushChecker.h"

bool isStraightFlush(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    return hand.isAllSameSuit() && hand.isConsecutive();
}

HandRank StraightFlushChecker::check(const Hand& hand){
    if (isStraightFlush(hand)){
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
