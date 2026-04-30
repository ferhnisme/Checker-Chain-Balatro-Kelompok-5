<<<<<<< Updated upstream
=======
#include <iostream>
#include "StraightChecker.h"

bool isStraight(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    return hand.isConsecutive();
}

HandRank StraightChecker::check(const Hand& hand){
    if (isStraight(hand)){
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
