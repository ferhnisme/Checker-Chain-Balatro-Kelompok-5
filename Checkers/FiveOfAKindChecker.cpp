<<<<<<< Updated upstream
=======
#include <iostream>
#include "FiveOfAKindChecker.h"

bool isFiveOfAKind(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    for (int count : counts) {
        if (count == 5) return true;
    }
    return false;
}

HandRank FiveOfAKindChecker::check(const Hand& hand){
    if (isFiveOfAKind(hand)){
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
