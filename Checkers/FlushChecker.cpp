<<<<<<< Updated upstream
=======
#include <iostream>
#include "FlushChecker.h"

bool isFlush(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    return hand.isAllSameSuit();
}

HandRank FlushChecker::check(const Hand& hand){
    if (isFlush(hand)){
        std::cout << "Detected FLUSH\n";
        return HandRank::FLUSH;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
